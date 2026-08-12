
/*
 * main.c
 *
 * Heart Rate Monitor
 * ------------------
 * TFT + 7 Segment + Buzzer + Alarm LED + LED Matrix
 *
 * STM32F401CC
 *
 * Heart Sensor : PA0  -> ADC Channel 0
 * Buzzer      : PA1
 * TFT CS      : PA4
 * TFT SCK     : PA5
 * TFT MOSI    : PA7
 * TFT DC      : PA2
 * TFT RST     : PA3
 * Start Button: PA8
 * Alarm LED   : PA12
 *
 * Step counter is currently SIMULATED.
 * Steps start from 0.
 * Battery starts from 100%.
 */


#include "Std_type.h"

#include "MRCC_Interface.h"
#include "MGPIO_Interface.h"
#include "MSTK_Interface.h"
#include "MSPI_Interface.h"
#include "MADC_Interface.h"

#include "HST7789_Interface.h"
#include "HLEDMATRIX_Interface.h"
#include "SevenSeg_Interface.h"


/*========================================================
 * CONFIGURATION
 *========================================================*/

#define HEART_SENSOR_CH       0

#define START_BUTTON_PORT     PORTA
#define START_BUTTON_PIN      PIN8

#define BUZZER_PORT           PORTA
#define BUZZER_PIN            PIN1

#define ALARM_LED_PORT        PORTA
#define ALARM_LED_PIN         PIN12


#define HEART_RATE_LOW        50
#define HEART_RATE_HIGH       90


/*========================================================
 * GLOBAL VARIABLES
 *========================================================*/

u16 HeartRateLowLimit  = HEART_RATE_LOW;
u16 HeartRateHighLimit = HEART_RATE_HIGH;

u8 AlarmEnabled = 1;


/*========================================================
 * SIMULATED VARIABLES
 *========================================================*/

/*
 * Steps start from ZERO.
 */
u32 StepCount = 0;

/*
 * Battery starts from 100%.
 */
u8 BatteryLevel = 100;

u8 WiFiConnected = 1;

u32 StepHistory[100];

u8 StepLogIndex = 0;


/*========================================================
 * HEART RATE VARIABLES
 *========================================================*/

u16 HeartRateLog[100];

u8 LogIndex = 0;

u16 CurrentHeartRate = 0;

u16 LastNormalHeartRate = 0;

u8 Measuring = 0;


/*========================================================
 * SCREEN STATE
 *========================================================*/

typedef enum
{
    SCREEN_START,
    SCREEN_DASHBOARD

} ScreenState_t;


ScreenState_t CurrentScreen = SCREEN_START;


/*========================================================
 * DRAW HEART
 *========================================================*/

void DrawHeart(void)
{
    HST7789_voidFillRectangle(
            65,
            30,
            15,
            15,
            TFT_RED);


    HST7789_voidFillRectangle(
            90,
            30,
            15,
            15,
            TFT_RED);


    HST7789_voidFillRectangle(
            55,
            45,
            60,
            15,
            TFT_RED);


    HST7789_voidFillRectangle(
            65,
            60,
            40,
            15,
            TFT_RED);


    HST7789_voidFillRectangle(
            75,
            75,
            20,
            15,
            TFT_RED);
}


/*========================================================
 * START SCREEN
 *========================================================*/

void ShowStartScreen(void)
{
    HST7789_voidFillScreen(TFT_BLACK);


    DrawHeart();


    HST7789_voidDrawString(
            45,
            110,
            "HEARTBEAT",
            TFT_RED,
            TFT_BLACK);


    HST7789_voidDrawString(
            40,
            150,
            "PRESS START",
            TFT_WHITE,
            TFT_BLACK);
}


/*========================================================
 * DASHBOARD
 *========================================================*/

void ShowDashboard(void)
{
    HST7789_voidFillScreen(TFT_BLACK);


    /*====================================================
     * TITLE
     *====================================================*/

    HST7789_voidDrawString(
            10,
            5,
            "DASHBOARD",
            TFT_CYAN,
            TFT_BLACK);


    /*====================================================
     * HEART RATE
     *====================================================*/

    HST7789_voidDrawString(
            10,
            40,
            "HR:",
            TFT_WHITE,
            TFT_BLACK);


    HST7789_voidDrawNumber(
            50,
            40,
            CurrentHeartRate,
            TFT_GREEN,
            TFT_BLACK);


    HST7789_voidDrawString(
            110,
            40,
            "BPM",
            TFT_WHITE,
            TFT_BLACK);


    /*====================================================
     * STEPS
     *====================================================*/

    HST7789_voidDrawString(
            10,
            80,
            "STEPS:",
            TFT_WHITE,
            TFT_BLACK);


    HST7789_voidDrawNumber(
            80,
            80,
            (s32)StepCount,
            TFT_YELLOW,
            TFT_BLACK);


    /*====================================================
     * BATTERY
     *====================================================*/

    HST7789_voidDrawString(
            10,
            120,
            "BATTERY:",
            TFT_WHITE,
            TFT_BLACK);


    HST7789_voidDrawNumber(
            100,
            120,
            BatteryLevel,
            TFT_CYAN,
            TFT_BLACK);


    HST7789_voidDrawString(
            140,
            120,
            "%",
            TFT_CYAN,
            TFT_BLACK);


    /*====================================================
     * WIFI
     *====================================================*/

    HST7789_voidDrawString(
            10,
            160,
            "WIFI:",
            TFT_WHITE,
            TFT_BLACK);


    if(WiFiConnected)
    {
        HST7789_voidDrawString(
                70,
                160,
                "CONNECTED",
                TFT_GREEN,
                TFT_BLACK);
    }
    else
    {
        HST7789_voidDrawString(
                70,
                160,
                "DISCONNECTED",
                TFT_RED,
                TFT_BLACK);
    }


    /*====================================================
     * STATUS
     *====================================================*/

    HST7789_voidDrawString(
            10,
            200,
            "STATUS:",
            TFT_WHITE,
            TFT_BLACK);


    if(CurrentHeartRate < HeartRateLowLimit)
    {
        HST7789_voidDrawString(
                90,
                200,
                "LOW HR",
                TFT_RED,
                TFT_BLACK);
    }
    else if(CurrentHeartRate > HeartRateHighLimit)
    {
        HST7789_voidDrawString(
                90,
                200,
                "HIGH HR",
                TFT_RED,
                TFT_BLACK);
    }
    else
    {
        HST7789_voidDrawString(
                90,
                200,
                "NORMAL",
                TFT_GREEN,
                TFT_BLACK);
    }
}


/*========================================================
 * UPDATE STEP DISPLAY
 *========================================================*/

void UpdateStepDisplay(void)
{
    /*
     * Clear old step number.
     *
     * Large enough for numbers such as:
     * 0
     * 10
     * 100
     * 1000
     * etc.
     */

    HST7789_voidFillRectangle(
            80,
            80,
            100,
            15,
            TFT_BLACK);


    HST7789_voidDrawNumber(
            80,
            80,
            (s32)StepCount,
            TFT_YELLOW,
            TFT_BLACK);
}


/*========================================================
 * UPDATE BATTERY DISPLAY
 *========================================================*/

void UpdateBatteryDisplay(void)
{
    /*
     * Clear old battery value.
     */

    HST7789_voidFillRectangle(
            100,
            120,
            40,
            15,
            TFT_BLACK);


    HST7789_voidDrawNumber(
            100,
            120,
            BatteryLevel,
            TFT_CYAN,
            TFT_BLACK);


    /*
     * The % sign remains at x = 140.
     */
}


/*========================================================
 * UPDATE WIFI DISPLAY
 *========================================================*/

void UpdateWiFiDisplay(void)
{
    /*
     * Clear old WiFi status.
     */

    HST7789_voidFillRectangle(
            70,
            160,
            150,
            15,
            TFT_BLACK);


    if(WiFiConnected)
    {
        HST7789_voidDrawString(
                70,
                160,
                "CONNECTED",
                TFT_GREEN,
                TFT_BLACK);
    }
    else
    {
        HST7789_voidDrawString(
                70,
                160,
                "DISCONNECTED",
                TFT_RED,
                TFT_BLACK);
    }
}


/*========================================================
 * UPDATE HEART RATE DISPLAY
 *========================================================*/

void UpdateHeartRateDisplay(void)
{
    /*
     * Clear old HR.
     */

    HST7789_voidFillRectangle(
            50,
            40,
            55,
            15,
            TFT_BLACK);


    /*
     * Draw new HR.
     */

    HST7789_voidDrawNumber(
            50,
            40,
            CurrentHeartRate,
            TFT_GREEN,
            TFT_BLACK);
}


/*========================================================
 * UPDATE STATUS DISPLAY
 *========================================================*/

void UpdateStatusDisplay(void)
{
    /*
     * Clear old status.
     */

    HST7789_voidFillRectangle(
            90,
            200,
            120,
            15,
            TFT_BLACK);


    if(CurrentHeartRate < HeartRateLowLimit)
    {
        HST7789_voidDrawString(
                90,
                200,
                "LOW HR",
                TFT_RED,
                TFT_BLACK);
    }
    else if(CurrentHeartRate > HeartRateHighLimit)
    {
        HST7789_voidDrawString(
                90,
                200,
                "HIGH HR",
                TFT_RED,
                TFT_BLACK);
    }
    else
    {
        HST7789_voidDrawString(
                90,
                200,
                "NORMAL",
                TFT_GREEN,
                TFT_BLACK);
    }
}


/*========================================================
 * LED MATRIX HEART
 *========================================================*/

void DisplayHeartOnMatrix(void)
{
    u8 heartFrame[8] =
    {
        0b00011000,
        0b00111100,
        0b01111110,
        0b11111111,
        0b11111111,
        0b01111110,
        0b00111100,
        0b00011000
    };


    HLEDMATRIX_voidDisplay(heartFrame);
}


/*========================================================
 * SIMULATE STEP COUNTER
 *========================================================*/

void SimulateStepCounter(void)
{
    static u8 stepTimer = 0;


    stepTimer++;


    /*
     * Every 20 main-loop cycles:
     *
     * 0 -> 1 -> 2 -> 3 -> ...
     */

    if(stepTimer >= 20)
    {
        stepTimer = 0;


        /*
         * Increment step count.
         */

        StepCount++;


        /*
         * Store step history.
         */

        StepHistory[StepLogIndex] =
                StepCount;


        StepLogIndex++;


        if(StepLogIndex >= 100)
        {
            StepLogIndex = 0;
        }
    }
}


/*========================================================
 * SIMULATE BATTERY
 *========================================================*/

void SimulateBattery(void)
{
    static u16 counter = 0;


    counter++;


    /*
     * Battery decreases by 1%.
     *
     * Starts:
     *
     * 100%
     * 99%
     * 98%
     * 97%
     * ...
     */

    if(counter >= 500)
    {
        counter = 0;


        if(BatteryLevel > 0)
        {
            BatteryLevel--;
        }
    }
}


/*========================================================
 * SIMULATE WIFI
 *========================================================*/

void SimulateWiFi(void)
{
    static u16 counter = 0;


    counter++;


    /*
     * Change WiFi state every 1000 cycles.
     */

    if(counter >= 1000)
    {
        counter = 0;


        WiFiConnected = !WiFiConnected;
    }
}


/*========================================================
 * MAIN
 *========================================================*/

int main(void)
{
    u16 ADCValue;


    /*====================================================
     * RCC
     *====================================================*/

    MRCC_voidInit();


    /*
     * GPIOA
     */

    MRCC_voidEnablePeipheralClock(
            AHB1_BUS,
            AHB1_GPIOA);


    /*
     * GPIOB
     *
     * Used by the 7-segment driver.
     */

    MRCC_voidEnablePeipheralClock(
            AHB1_BUS,
            AHB1_GPIOB);


    /*
     * SPI1
     */

    MRCC_voidEnablePeipheralClock(
            APB2_BUS,
            APB2_SPI1);


    /*
     * ADC1
     */

    MRCC_voidEnablePeipheralClock(
            APB2_BUS,
            APB2_ADC1);


    /*====================================================
     * TFT CONTROL PINS
     *
     * CS  = PA4
     * DC  = PA2
     * RST = PA3
     *====================================================*/

    MGPIO_voidSetMode(
            PORTA,
            PIN4,
            OUTPUT);


    MGPIO_voidSetOutputConfig(
            PORTA,
            PIN4,
            PUSH_PULL,
            VERY_HIGH_SPEED);


    MGPIO_voidSetMode(
            PORTA,
            PIN2,
            OUTPUT);


    MGPIO_voidSetOutputConfig(
            PORTA,
            PIN2,
            PUSH_PULL,
            VERY_HIGH_SPEED);


    MGPIO_voidSetMode(
            PORTA,
            PIN3,
            OUTPUT);


    MGPIO_voidSetOutputConfig(
            PORTA,
            PIN3,
            PUSH_PULL,
            VERY_HIGH_SPEED);


    /*
     * CS HIGH initially.
     */

    MGPIO_voidSetPinValue(
            PORTA,
            PIN4,
            HIGH);


    /*====================================================
     * SPI1 PINS
     *
     * SCK  = PA5
     * MOSI = PA7
     *====================================================*/

    MGPIO_voidSetMode(
            PORTA,
            PIN5,
            ALTFUNC);


    MGPIO_voidSetAlternateFunction(
            PORTA,
            PIN5,
            5);


    MGPIO_voidSetMode(
            PORTA,
            PIN7,
            ALTFUNC);


    MGPIO_voidSetAlternateFunction(
            PORTA,
            PIN7,
            5);


    /*====================================================
     * HEART SENSOR
     *
     * PA0 = ADC CHANNEL 0
     *====================================================*/

    MGPIO_voidSetMode(
            PORTA,
            PIN0,
            ANALOG);


    /*====================================================
     * BUZZER
     *
     * PA1
     *====================================================*/

    MGPIO_voidSetMode(
            BUZZER_PORT,
            BUZZER_PIN,
            OUTPUT);


    MGPIO_voidSetOutputConfig(
            BUZZER_PORT,
            BUZZER_PIN,
            PUSH_PULL,
            VERY_HIGH_SPEED);


    /*
     * Buzzer OFF initially.
     */

    MGPIO_voidSetPinValue(
            BUZZER_PORT,
            BUZZER_PIN,
            LOW);


    /*====================================================
     * ALARM LED
     *
     * PA12
     *====================================================*/

    MGPIO_voidSetMode(
            ALARM_LED_PORT,
            ALARM_LED_PIN,
            OUTPUT);


    MGPIO_voidSetOutputConfig(
            ALARM_LED_PORT,
            ALARM_LED_PIN,
            PUSH_PULL,
            VERY_HIGH_SPEED);


    /*
     * Alarm LED OFF initially.
     */

    MGPIO_voidSetPinValue(
            ALARM_LED_PORT,
            ALARM_LED_PIN,
            LOW);


    /*====================================================
     * START BUTTON
     *
     * PA8
     *
     * Button:
     *
     * PA8 ---- Button ---- GND
     *
     * Internal pull-up enabled.
     *
     * Released = HIGH
     * Pressed  = LOW
     *====================================================*/

    MGPIO_voidSetMode(
            START_BUTTON_PORT,
            START_BUTTON_PIN,
            INPUT);


    MGPIO_voidSetInputConfig(
            START_BUTTON_PORT,
            START_BUTTON_PIN,
            PULL_UP);


    /*====================================================
     * DRIVER INITIALIZATION
     *====================================================*/

    MSTK_voidInit();


    MSPI_voidMasterInit();


    MADC_voidInit();


    HST7789_voidInit();


    SevenSeg_voidInit();


    /*
     * Do NOT call SevenSeg_voidInit()
     * again.
     */


    /*====================================================
     * INITIAL VALUES
     *====================================================*/

    /*
     * Steps start from ZERO.
     */

    StepCount = 0;


    /*
     * Battery starts from 100%.
     */

    BatteryLevel = 100;


    /*
     * Initial HR = 0.
     */

    CurrentHeartRate = 0;


    /*
     * No measurement initially.
     */

    Measuring = 0;


    /*====================================================
     * START SCREEN
     *====================================================*/

    ShowStartScreen();


    CurrentScreen = SCREEN_START;


    /*====================================================
     * MAIN LOOP
     *====================================================*/

    while(1)
    {

        /*================================================
         * BUTTON CONTROL
         *================================================*/

        if(MGPIO_GetPinValue(
                START_BUTTON_PORT,
                START_BUTTON_PIN) == LOW)
        {

            /*
             * Debounce.
             */

            MSTK_voidSetBusyWait(20000);


            /*
             * Check button again.
             */

            if(MGPIO_GetPinValue(
                    START_BUTTON_PORT,
                    START_BUTTON_PIN) == LOW)
            {

                /*
                 * Wait until button is released.
                 */

                while(MGPIO_GetPinValue(
                        START_BUTTON_PORT,
                        START_BUTTON_PIN) == LOW)
                {
                }


                /*========================================
                 * START MEASUREMENT
                 *========================================*/

                if(CurrentScreen == SCREEN_START)
                {

                    Measuring = 1;


                    CurrentScreen =
                            SCREEN_DASHBOARD;


                    /*
                     * Show dashboard.
                     *
                     * StepCount is still 0.
                     * BatteryLevel is still 100.
                     */

                    ShowDashboard();
                }


                /*========================================
                 * STOP MEASUREMENT
                 *========================================*/

                else
                {

                    Measuring = 0;


                    /*
                     * Buzzer OFF.
                     */

                    MGPIO_voidSetPinValue(
                            BUZZER_PORT,
                            BUZZER_PIN,
                            LOW);


                    /*
                     * Alarm LED OFF.
                     */

                    MGPIO_voidSetPinValue(
                            ALARM_LED_PORT,
                            ALARM_LED_PIN,
                            LOW);


                    /*
                     * Return to start screen.
                     */

                    CurrentScreen =
                            SCREEN_START;


                    ShowStartScreen();


                    /*
                     * Display last normal HR
                     * on 7-segment.
                     */

                    SevenSeg_voidDisplayNumber(
                            (u8)LastNormalHeartRate);
                }
            }
        }


        /*================================================
         * MEASUREMENT
         *================================================*/

        if(Measuring == 1 &&
           CurrentScreen == SCREEN_DASHBOARD)
        {

            /*============================================
             * LED MATRIX
             *============================================*/

            DisplayHeartOnMatrix();


            /*============================================
             * HEART SENSOR
             *============================================*/

            ADCValue =
                MADC_u16GetChannelReading(
                        HEART_SENSOR_CH);


            /*
             * IMPORTANT:
             *
             * This is NOT a real BPM algorithm.
             *
             * It simply converts ADC value
             * into a number from 0 to 100.
             */

            CurrentHeartRate =
                    (ADCValue * 100) / 4095;


            /*============================================
             * 7-SEGMENT
             *============================================*/

            SevenSeg_voidDisplayNumber(
                    (u8)CurrentHeartRate);


            /*============================================
             * HEART RATE LOG
             *============================================*/

            HeartRateLog[LogIndex] =
                    CurrentHeartRate;


            LogIndex++;


            if(LogIndex >= 100)
            {
                LogIndex = 0;
            }


            /*============================================
             * LAST NORMAL HEART RATE
             *============================================*/

            if(CurrentHeartRate >= HeartRateLowLimit &&
               CurrentHeartRate <= HeartRateHighLimit)
            {

                LastNormalHeartRate =
                        CurrentHeartRate;
            }


            /*============================================
             * ALARM
             *============================================*/

            if(AlarmEnabled &&
               (CurrentHeartRate < HeartRateLowLimit ||
                CurrentHeartRate > HeartRateHighLimit))
            {

                /*
                 * Buzzer ON.
                 */

                MGPIO_voidSetPinValue(
                        BUZZER_PORT,
                        BUZZER_PIN,
                        HIGH);


                /*
                 * Alarm LED ON.
                 */

                MGPIO_voidSetPinValue(
                        ALARM_LED_PORT,
                        ALARM_LED_PIN,
                        HIGH);
            }
            else
            {

                /*
                 * Buzzer OFF.
                 */

                MGPIO_voidSetPinValue(
                        BUZZER_PORT,
                        BUZZER_PIN,
                        LOW);


                /*
                 * Alarm LED OFF.
                 */

                MGPIO_voidSetPinValue(
                        ALARM_LED_PORT,
                        ALARM_LED_PIN,
                        LOW);
            }


            /*============================================
             * UPDATE HEART RATE
             *============================================*/

            UpdateHeartRateDisplay();


            /*============================================
             * UPDATE STATUS
             *============================================*/

            UpdateStatusDisplay();


            /*============================================
             * UPDATE STEPS
             *============================================*/

            UpdateStepDisplay();


            /*============================================
             * UPDATE BATTERY
             *============================================*/

            UpdateBatteryDisplay();


            /*============================================
             * UPDATE WIFI
             *============================================*/

            UpdateWiFiDisplay();


            /*============================================
             * SIMULATED STEP COUNTER
             *
             * Starts:
             *
             * 0
             * 1
             * 2
             * 3
             * ...
             *============================================*/

            SimulateStepCounter();


            /*============================================
             * SIMULATED BATTERY
             *
             * Starts:
             *
             * 100%
             * 99%
             * 98%
             * ...
             *============================================*/

            SimulateBattery();


            /*============================================
             * SIMULATED WIFI
             *============================================*/

            SimulateWiFi();


            /*============================================
             * DELAY
             *============================================*/

            MSTK_voidSetBusyWait(50000);
        }
    }
}

