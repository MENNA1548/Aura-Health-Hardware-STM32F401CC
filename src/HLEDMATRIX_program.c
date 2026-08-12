/*
 * HLEDMATRIX_program.c
 *
 * Created on: Mar 7, 2025
 * Author: mohamed.hagag
 */

#include "Std_type.h"

#include "MGPIO_Interface.h"
#include "MSTK_Interface.h"

#include "HLEDMATRIX_Interface.h"

static void HLEDMATRIX_voidSetRowValue(u8 Copy_u8RowValue);
static void HLEDMATRIX_voidDeactivateAllColumns(void);

/*==============================================================*/

void HLEDMATRIX_voidInit(void)
{
    /* Rows : PA0 -> PA7 */
    for(u8 i = 0; i < 8; i++)
    {
        MGPIO_voidSetMode(PORTA, (Pins_t)i, OUTPUT);
        MGPIO_voidSetOutputConfig(PORTA, (Pins_t)i, PUSH_PULL, LOW_SPEED);
    }

    /* Columns : PB0 PB1 PB2 PB6 PB7 PB8 PB9 PB10 */
    Pins_t ColPins[8] =
    {
        PIN0,
        PIN1,
        PIN2,
        PIN6,
        PIN7,
        PIN8,
        PIN9,
        PIN10
    };

    for(u8 i = 0; i < 8; i++)
    {
        MGPIO_voidSetMode(PORTB, ColPins[i], OUTPUT);
        MGPIO_voidSetOutputConfig(PORTB, ColPins[i], PUSH_PULL, LOW_SPEED);
    }

    HLEDMATRIX_voidDeactivateAllColumns();
}

/*==============================================================*/

static void HLEDMATRIX_voidSetRowValue(u8 Copy_u8RowValue)
{
    for(u8 i = 0; i < 8; i++)
    {
        if((Copy_u8RowValue >> i) & 0x01)
        {
            MGPIO_voidSetPinValue(PORTA, (Pins_t)i, HIGH);
        }
        else
        {
            MGPIO_voidSetPinValue(PORTA, (Pins_t)i, LOW);
        }
    }
}

/*==============================================================*/

static void HLEDMATRIX_voidDeactivateAllColumns(void)
{
    Pins_t ColPins[8] =
    {
        PIN0,
        PIN1,
        PIN2,
        PIN6,
        PIN7,
        PIN8,
        PIN9,
        PIN10
    };

    for(u8 i = 0; i < 8; i++)
    {
        MGPIO_voidSetPinValue(PORTB, ColPins[i], HIGH);
    }
}

/*==============================================================*/

void HLEDMATRIX_voidDisplay(u8 *Copy_Pu8Arr)
{
    Pins_t ColPins[8] =
    {
        PIN0,
        PIN1,
        PIN2,
        PIN6,
        PIN7,
        PIN8,
        PIN9,
        PIN10
    };

    for(u8 Col = 0; Col < 8; Col++)
    {
        /* Disable all columns */
        HLEDMATRIX_voidDeactivateAllColumns();

        /* Output row data */
        HLEDMATRIX_voidSetRowValue(Copy_Pu8Arr[Col]);

        /* Enable one column */
        MGPIO_voidSetPinValue(PORTB, ColPins[Col], LOW);

        /* Delay */
        MSTK_voidSetBusyWait(5000);
    }
}
