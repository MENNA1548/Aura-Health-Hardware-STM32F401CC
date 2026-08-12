//#include <stdint.h>
//#include "Std_type.h"
//#include "../include/MGPIO_interface.h"
//#include "../include/SevenSeg_config.h"
//#include "../include/SevenSeg_interface.h"
///* Common Cathode driver: HIGH = segment ON, LOW = segment OFF */
//
///* Segment order in each pattern row: a b c d e f g */
//static const uint8_t SevenSeg_au8Patterns[10][7] =
//{
//    /*         a  b  c  d  e  f  g */
//    /* 0 */   {1, 1, 1, 1, 1, 1, 0},
//    /* 1 */   {0, 1, 1, 0, 0, 0, 0},
//    /* 2 */   {1, 1, 0, 1, 1, 0, 1},
//    /* 3 */   {1, 1, 1, 1, 0, 0, 1},
//    /* 4 */   {0, 1, 1, 0, 0, 1, 1},
//    /* 5 */   {1, 0, 1, 1, 0, 1, 1},
//    /* 6 */   {1, 0, 1, 1, 1, 1, 1},
//    /* 7 */   {1, 1, 1, 0, 0, 0, 0},
//    /* 8 */   {1, 1, 1, 1, 1, 1, 1},
//    /* 9 */   {1, 1, 1, 1, 0, 1, 1}
//};
//
//static const Pins_t SevenSeg_aePins[7] =
//{
//    SEVENSEG_PIN_A, SEVENSEG_PIN_B, SEVENSEG_PIN_C,
//    SEVENSEG_PIN_D, SEVENSEG_PIN_E, SEVENSEG_PIN_F, SEVENSEG_PIN_G
//};
//
//void SevenSeg_voidInit(void)
//{
//    uint8_t Local_u8Index;
//    for (Local_u8Index = 0; Local_u8Index < 7; Local_u8Index++)
//    {
//        MGPIO_voidSetMode(SEVENSEG_PORT, SevenSeg_aePins[Local_u8Index], OUTPUT);
//        MGPIO_voidSetOutputConfig(SEVENSEG_PORT, SevenSeg_aePins[Local_u8Index], PUSH_PULL, LOW_SPEED);
//    }
//    SevenSeg_voidOff();
//}
//
//void SevenSeg_voidDisplayDigit(uint8_t Copy_Digit)
//{
//    uint8_t Local_u8Index;
//    uint8_t Local_u8SegState;
//
//    if (Copy_Digit > 9)
//    {
//        return; /* invalid digit, ignore */
//    }
//
//    for (Local_u8Index = 0; Local_u8Index < 7; Local_u8Index++)
//    {
//        Local_u8SegState = SevenSeg_au8Patterns[Copy_Digit][Local_u8Index];
//        MGPIO_voidSetPinValue(SEVENSEG_PORT, SevenSeg_aePins[Local_u8Index],
//                               (Local_u8SegState ? HIGH : LOW));
//    }
//}
//
//void SevenSeg_voidOff(void)
//{
//    uint8_t Local_u8Index;
//    for (Local_u8Index = 0; Local_u8Index < 7; Local_u8Index++)
//    {
//        MGPIO_voidSetPinValue(SEVENSEG_PORT, SevenSeg_aePins[Local_u8Index], LOW);
//    }
//}
//
//void SevenSeg_voidAllOn(void)
//{
//    uint8_t Local_u8Index;
//    for (Local_u8Index = 0; Local_u8Index < 7; Local_u8Index++)
//    {
//        MGPIO_voidSetPinValue(SEVENSEG_PORT, SevenSeg_aePins[Local_u8Index], HIGH);
//    }
//}
//
#include <stdint.h>

#include "Std_type.h"

#include "MRCC_Interface.h"
#include "MGPIO_Interface.h"

#include "SevenSeg_config.h"
#include "SevenSeg_interface.h"


/******************************************************
 * COMMON CATHODE
 *
 * HIGH = ON
 * LOW  = OFF
 ******************************************************/


/******************************************************
 * 7-SEGMENT DIGIT PATTERNS
 *
 * Bit meaning:
 *
 * A B C D E F G
 *
 ******************************************************/

static const uint8_t SevenSeg_au8Patterns[10][7] =
{
    /*        A  B  C  D  E  F  G */

    /* 0 */ { 1, 1, 1, 1, 1, 1, 0 },
    /* 1 */ { 0, 1, 1, 0, 0, 0, 0 },
    /* 2 */ { 1, 1, 0, 1, 1, 0, 1 },
    /* 3 */ { 1, 1, 1, 1, 0, 0, 1 },
    /* 4 */ { 0, 1, 1, 0, 0, 1, 1 },
    /* 5 */ { 1, 0, 1, 1, 0, 1, 1 },
    /* 6 */ { 1, 0, 1, 1, 1, 1, 1 },
    /* 7 */ { 1, 1, 1, 0, 0, 0, 0 },
    /* 8 */ { 1, 1, 1, 1, 1, 1, 1 },
    /* 9 */ { 1, 1, 1, 1, 0, 1, 1 }
};


/******************************************************
 * SEGMENT PINS
 ******************************************************/

static const Pins_t SevenSeg1_aePins[7] =
{
    SEVENSEG1_PIN_A,
    SEVENSEG1_PIN_B,
    SEVENSEG1_PIN_C,
    SEVENSEG1_PIN_D,
    SEVENSEG1_PIN_E,
    SEVENSEG1_PIN_F,
    SEVENSEG1_PIN_G
};


static const Pins_t SevenSeg2_aePins[7] =
{
    SEVENSEG2_PIN_A,
    SEVENSEG2_PIN_B,
    SEVENSEG2_PIN_C,
    SEVENSEG2_PIN_D,
    SEVENSEG2_PIN_E,
    SEVENSEG2_PIN_F,
    SEVENSEG2_PIN_G
};


/******************************************************
 * INITIALIZATION
 ******************************************************/

void SevenSeg_voidInit(void)
{
    uint8_t Local_u8Index;


    /**************************************************
     * Enable GPIOB clock
     **************************************************/

    MRCC_voidEnablePeipheralClock(
            AHB1_BUS,
            AHB1_GPIOB);


    /**************************************************
     * Configure 7-Segment 1
     *
     * PB0 -> PB6
     **************************************************/

    for(Local_u8Index = 0;
        Local_u8Index < 7;
        Local_u8Index++)
    {
        MGPIO_voidSetMode(
                SEVENSEG1_PORT,
                SevenSeg1_aePins[Local_u8Index],
                OUTPUT);

        MGPIO_voidSetOutputConfig(
                SEVENSEG1_PORT,
                SevenSeg1_aePins[Local_u8Index],
                PUSH_PULL,
                LOW_SPEED);
    }


    /**************************************************
     * Configure 7-Segment 2
     *
     * PB8 -> PB14
     **************************************************/

    for(Local_u8Index = 0;
        Local_u8Index < 7;
        Local_u8Index++)
    {
        MGPIO_voidSetMode(
                SEVENSEG2_PORT,
                SevenSeg2_aePins[Local_u8Index],
                OUTPUT);

        MGPIO_voidSetOutputConfig(
                SEVENSEG2_PORT,
                SevenSeg2_aePins[Local_u8Index],
                PUSH_PULL,
                LOW_SPEED);
    }


    /**************************************************
     * DP pins
     **************************************************/

    MGPIO_voidSetMode(
            PORTB,
            PIN7,
            OUTPUT);

    MGPIO_voidSetOutputConfig(
            PORTB,
            PIN7,
            PUSH_PULL,
            LOW_SPEED);


    MGPIO_voidSetMode(
            PORTB,
            PIN15,
            OUTPUT);

    MGPIO_voidSetOutputConfig(
            PORTB,
            PIN15,
            PUSH_PULL,
            LOW_SPEED);


    /**************************************************
     * Turn OFF
     **************************************************/

    SevenSeg_voidOff();
}


/******************************************************
 * DISPLAY DIGIT ON 7-SEGMENT 1
 ******************************************************/

void SevenSeg_voidDisplayDigit1(
        uint8_t Copy_Digit)
{
    uint8_t Local_u8Index;


    if(Copy_Digit > 9)
    {
        return;
    }


    for(Local_u8Index = 0;
        Local_u8Index < 7;
        Local_u8Index++)
    {
        if(SevenSeg_au8Patterns
                [Copy_Digit]
                [Local_u8Index])
        {
            MGPIO_voidSetPinValue(
                    SEVENSEG1_PORT,
                    SevenSeg1_aePins[Local_u8Index],
                    HIGH);
        }
        else
        {
            MGPIO_voidSetPinValue(
                    SEVENSEG1_PORT,
                    SevenSeg1_aePins[Local_u8Index],
                    LOW);
        }
    }


    /* DP OFF */

    MGPIO_voidSetPinValue(
            PORTB,
            PIN7,
            LOW);
}


/******************************************************
 * DISPLAY DIGIT ON 7-SEGMENT 2
 ******************************************************/

void SevenSeg_voidDisplayDigit2(
        uint8_t Copy_Digit)
{
    uint8_t Local_u8Index;


    if(Copy_Digit > 9)
    {
        return;
    }


    for(Local_u8Index = 0;
        Local_u8Index < 7;
        Local_u8Index++)
    {
        if(SevenSeg_au8Patterns
                [Copy_Digit]
                [Local_u8Index])
        {
            MGPIO_voidSetPinValue(
                    SEVENSEG2_PORT,
                    SevenSeg2_aePins[Local_u8Index],
                    HIGH);
        }
        else
        {
            MGPIO_voidSetPinValue(
                    SEVENSEG2_PORT,
                    SevenSeg2_aePins[Local_u8Index],
                    LOW);
        }
    }


    /* DP OFF */

    MGPIO_voidSetPinValue(
            PORTB,
            PIN15,
            LOW);
}


/******************************************************
 * DISPLAY NUMBER 00 -> 99
 ******************************************************/

void SevenSeg_voidDisplayNumber(
        uint8_t Copy_Number)
{
    uint8_t Local_u8Tens;
    uint8_t Local_u8Ones;


    if(Copy_Number > 99)
    {
        Copy_Number = 99;
    }


    Local_u8Tens =
        Copy_Number / 10;


    Local_u8Ones =
        Copy_Number % 10;


    /**************************************************
     * First display = TENS
     **************************************************/

    SevenSeg_voidDisplayDigit1(
            Local_u8Tens);


    /**************************************************
     * Second display = ONES
     **************************************************/

    SevenSeg_voidDisplayDigit2(
            Local_u8Ones);
}


/******************************************************
 * TURN BOTH DISPLAYS OFF
 ******************************************************/

void SevenSeg_voidOff(void)
{
    uint8_t Local_u8Index;


    /**************************************************
     * Display 1
     **************************************************/

    for(Local_u8Index = 0;
        Local_u8Index < 7;
        Local_u8Index++)
    {
        MGPIO_voidSetPinValue(
                SEVENSEG1_PORT,
                SevenSeg1_aePins[Local_u8Index],
                LOW);
    }


    MGPIO_voidSetPinValue(
            PORTB,
            PIN7,
            LOW);


    /**************************************************
     * Display 2
     **************************************************/

    for(Local_u8Index = 0;
        Local_u8Index < 7;
        Local_u8Index++)
    {
        MGPIO_voidSetPinValue(
                SEVENSEG2_PORT,
                SevenSeg2_aePins[Local_u8Index],
                LOW);
    }


    MGPIO_voidSetPinValue(
            PORTB,
            PIN15,
            LOW);
}


/******************************************************
 * ALL SEGMENTS ON
 ******************************************************/

void SevenSeg_voidAllOn(void)
{
    uint8_t Local_u8Index;


    /**************************************************
     * Display 1
     **************************************************/

    for(Local_u8Index = 0;
        Local_u8Index < 7;
        Local_u8Index++)
    {
        MGPIO_voidSetPinValue(
                SEVENSEG1_PORT,
                SevenSeg1_aePins[Local_u8Index],
                HIGH);
    }


    /**************************************************
     * Display 2
     **************************************************/

    for(Local_u8Index = 0;
        Local_u8Index < 7;
        Local_u8Index++)
    {
        MGPIO_voidSetPinValue(
                SEVENSEG2_PORT,
                SevenSeg2_aePins[Local_u8Index],
                HIGH);
    }
}
