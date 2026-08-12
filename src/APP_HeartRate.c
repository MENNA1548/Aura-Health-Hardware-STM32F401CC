#include "Std_type.h"

#include "MSTK_Interface.h"

#include "HHEARTBEAT_Interface.h"

#include "HST7789_Interface.h"

#include "HBUZZER_Interface.h"

#define MAX_HEART_RATE    120
#define MIN_HEART_RATE     50

#define HISTORY_SIZE       60

static u8 HeartHistory[HISTORY_SIZE];
static u8 Index = 0;

void APP_HeartRate_voidInit(void)
{
    HHEARTBEAT_voidInit();

    HBUZZER_voidInit();

    HST7789_voidInit();

    HST7789_voidFillScreen(TFT_BLACK);
}

void APP_HeartRate_voidRun(void)
{
    u8 BPM;

    while(1)
    {
        /* Read Heart Rate */
        BPM = HHEARTBEAT_u8GetBPM();

        /* Store History */
        HeartHistory[Index] = BPM;

        Index++;

        if(Index >= HISTORY_SIZE)
        {
            Index = 0;
        }

        /* Clear Screen */
        HST7789_voidFillScreen(TFT_BLACK);

        /* Title */
        HST7789_voidDrawString(
                20,
                20,
                "HEART RATE",
                TFT_WHITE,
                TFT_BLACK);

        /* BPM Value */
        HST7789_voidDrawNumber(
                50,
                60,
                BPM,
                TFT_GREEN,
                TFT_BLACK);

        /* BPM Text */
        HST7789_voidDrawString(
                90,
                60,
                "BPM",
                TFT_WHITE,
                TFT_BLACK);

        /* Status */

        if(BPM > MAX_HEART_RATE)
        {
            HBUZZER_voidOn();

            HST7789_voidDrawString(
                    20,
                    110,
                    "STATUS: HIGH",
                    TFT_RED,
                    TFT_BLACK);
        }
        else if(BPM < MIN_HEART_RATE)
        {
            HBUZZER_voidOn();

            HST7789_voidDrawString(
                    20,
                    110,
                    "STATUS: LOW",
                    TFT_RED,
                    TFT_BLACK);
        }
        else
        {
            HBUZZER_voidOff();

            HST7789_voidDrawString(
                    20,
                    110,
                    "STATUS: NORMAL",
                    TFT_GREEN,
                    TFT_BLACK);
        }

        /* Delay */
        MSTK_voidSetBusyWait(1000000);
    }
}
