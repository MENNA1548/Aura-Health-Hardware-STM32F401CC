/*
 * HSEVENSEG_program.c
 *
 *  Created on: 6 Aug 2026
 *      Author: DELL
 */
#include "Std_type.h"
#include "MGPIO_interface.h"
#include "MSTK_interface.h"
#include "HSEVENSEG_interface.h"

static const u8 Numbers[10] =
{
    0x3F, //0
    0x06, //1
    0x5B, //2
    0x4F, //3
    0x66, //4
    0x6D, //5
    0x7D, //6
    0x07, //7
    0x7F, //8
    0x6F  //9
};

void HSEVENSEG_voidInit(void)
{
    /* Segments PA0 -> PA7 */
    for(u8 i = 0; i < 8; i++)
    {
        MGPIO_voidSetMode(PORTA, i, OUTPUT);
        MGPIO_voidSetOutputConfig(PORTA, i, PUSH_PULL, LOW_SPEED);
    }

    /* Two digits only */
    MGPIO_voidSetMode(PORTB, PIN0, OUTPUT);
    MGPIO_voidSetOutputConfig(PORTB, PIN0, PUSH_PULL, LOW_SPEED);

    MGPIO_voidSetMode(PORTB, PIN1, OUTPUT);
    MGPIO_voidSetOutputConfig(PORTB, PIN1, PUSH_PULL, LOW_SPEED);
}

void HSEVENSEG_voidDisplayNumber(u8 Number)
{
    if(Number > 99)
        Number = 99;

    u8 Tens = Number / 10;
    u8 Ones = Number % 10;

    /* Display Tens */
    for(u8 i = 0; i < 8; i++)
    {
        MGPIO_voidSetPinValue(PORTA, i, (Numbers[Tens] >> i) & 1);
    }

    MGPIO_voidSetPinValue(PORTB, PIN0, LOW);
    MSTK_voidSetBusyWait(1600);
    MGPIO_voidSetPinValue(PORTB, PIN0, HIGH);

    /* Display Ones */
    for(u8 i = 0; i < 8; i++)
    {
        MGPIO_voidSetPinValue(PORTA, i, (Numbers[Ones] >> i) & 1);
    }

    MGPIO_voidSetPinValue(PORTB, PIN1, LOW);
    MSTK_voidSetBusyWait(1600);
    MGPIO_voidSetPinValue(PORTB, PIN1, HIGH);
}
