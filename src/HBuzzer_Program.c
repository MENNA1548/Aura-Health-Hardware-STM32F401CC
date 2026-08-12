#include "Std_type.h"

#include "MGPIO_Interface.h"

#include "HBUZZER_Interface.h"



void HBUZZER_voidInit(void)
{

    MGPIO_voidSetMode(PORTB,PIN0,OUTPUT);


    MGPIO_voidSetOutputConfig(
            PORTB,
            PIN0,
            PUSH_PULL,
            LOW_SPEED);


    HBUZZER_voidOff();

}



void HBUZZER_voidOn(void)
{
    MGPIO_voidSetPinValue(
            PORTB,
            PIN0,
            HIGH);
}



void HBUZZER_voidOff(void)
{
    MGPIO_voidSetPinValue(
            PORTB,
            PIN0,
            LOW);
}
