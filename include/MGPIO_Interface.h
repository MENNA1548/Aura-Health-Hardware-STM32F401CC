#ifndef MGPIO_INTERFACE_H_
#define MGPIO_INTERFACE_H_

#include "Std_type.h"


/*==============================
      Ports
==============================*/

typedef enum
{
    PORTA = 0,
    PORTB,
    PORTC

}Ports_t;



/*==============================
      Pins
==============================*/

typedef enum
{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9,
    PIN10,
    PIN11,
    PIN12,
    PIN13,
    PIN14,
    PIN15

}Pins_t;



/*==============================
      Values
==============================*/

typedef enum
{

    LOW = 0,
    HIGH

}Value_t;



/*==============================
      Modes
==============================*/

typedef enum
{

    INPUT = 0,
    OUTPUT,
    ALTFUNC,
    ANALOG

}Mode_t;



/*==============================
      Output Type
==============================*/

typedef enum
{

    PUSH_PULL = 0,
    OPEN_DRAIN

}OutputType_t;



/*==============================
      Speed
==============================*/

typedef enum
{

    LOW_SPEED = 0,
    MEDIUM_SPEED,
    HIGH_SPEED,
    VERY_HIGH_SPEED

}Speed_t;

/*==============================*
* Pull Configuration
*==============================*/

typedef enum
{

    NO_PULL = 0,
    PULL_UP,
    PULL_DOWN

}PullType_t;

/*==============================
      APIs
==============================*/


void MGPIO_voidSetMode(
        Ports_t Copy_Port,
        Pins_t Copy_Pin,
        Mode_t Copy_Mode);



void MGPIO_voidSetOutputConfig(
        Ports_t Copy_Port,
        Pins_t Copy_Pin,
        OutputType_t Copy_OutputType,
        Speed_t Copy_Speed);



void MGPIO_voidSetPinValue(
        Ports_t Copy_Port,
        Pins_t Copy_Pin,
        Value_t Copy_Value);



Value_t MGPIO_GetPinValue(
        Ports_t Copy_Port,
        Pins_t Copy_Pin);



void MGPIO_voidSetAlternateFunction(
        Ports_t Copy_Port,
        Pins_t Copy_Pin,
        u8 Copy_AF);

void MGPIO_voidSetInputConfig(
        Ports_t Copy_Port,
        Pins_t Copy_Pin,
        PullType_t Copy_Pull);

#endif
