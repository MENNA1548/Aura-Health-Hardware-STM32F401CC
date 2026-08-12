#include "Std_type.h"

#include "MGPIO_Private.h"
#include "MGPIO_Interface.h"

void MGPIO_voidSetMode(Ports_t Copy_Port,
                       Pins_t Copy_Pin,
                       Mode_t Copy_Mode)
{
	volatile GPIO_t *Local_GPIO = (void *)0;


    switch(Copy_Port)
    {
        case PORTA:
            Local_GPIO = GPIOA;
            break;

        case PORTB:
            Local_GPIO = GPIOB;
            break;

        case PORTC:
            Local_GPIO = GPIOC;
            break;

        default:
            return;
    }


    Local_GPIO->MODER &= ~(0x3UL << (Copy_Pin * 2));

    Local_GPIO->MODER |= ((u32)Copy_Mode << (Copy_Pin * 2));

}

void MGPIO_voidSetInputConfig(
        Ports_t Copy_Port,
        Pins_t Copy_Pin,
        PullType_t Copy_Pull)
{

    volatile GPIO_t *Local_GPIO = (void *)0;


    switch(Copy_Port)
    {

        case PORTA:
            Local_GPIO = GPIOA;
            break;


        case PORTB:
            Local_GPIO = GPIOB;
            break;


        case PORTC:
            Local_GPIO = GPIOC;
            break;

    }



    /* Clear old pull configuration */

    Local_GPIO->PUPDR &= ~(3 << (Copy_Pin * 2));


    switch(Copy_Pull)
    {

        case NO_PULL:

            Local_GPIO->PUPDR |= (0 << (Copy_Pin * 2));

            break;


        case PULL_UP:

            Local_GPIO->PUPDR |= (1 << (Copy_Pin * 2));

            break;


        case PULL_DOWN:

            Local_GPIO->PUPDR |= (2 << (Copy_Pin * 2));

            break;

    }

}

void MGPIO_voidSetOutputConfig(Ports_t Copy_Port,
                               Pins_t Copy_Pin,
                               OutputType_t Copy_OutputType,
                               Speed_t Copy_Speed)
{
	volatile GPIO_t *Local_GPIO = (void *)0;


    switch(Copy_Port)
    {
        case PORTA:
            Local_GPIO = GPIOA;
            break;

        case PORTB:
            Local_GPIO = GPIOB;
            break;

        case PORTC:
            Local_GPIO = GPIOC;
            break;

        default:
            return;
    }


    /* Output Type */

    Local_GPIO->OTYPER &= ~(1UL << Copy_Pin);

    Local_GPIO->OTYPER |=
            ((u32)Copy_OutputType << Copy_Pin);



    /* Output Speed */

    Local_GPIO->OSPEEDR &= ~(0x3UL << (Copy_Pin*2));

    Local_GPIO->OSPEEDR |=
            ((u32)Copy_Speed << (Copy_Pin*2));

}



void MGPIO_voidSetPinValue(Ports_t Copy_Port,
                           Pins_t Copy_Pin,
                           Value_t Copy_Value)
{

	volatile GPIO_t *Local_GPIO = (void *)0;


    switch(Copy_Port)
    {
        case PORTA:
            Local_GPIO = GPIOA;
            break;

        case PORTB:
            Local_GPIO = GPIOB;
            break;

        case PORTC:
            Local_GPIO = GPIOC;
            break;

        default:
            return;
    }



    if(Copy_Value == HIGH)
    {
        Local_GPIO->BSRR =
                (1UL << Copy_Pin);
    }

    else
    {
        Local_GPIO->BSRR =
                (1UL << (Copy_Pin+16));
    }

}




void MGPIO_voidSetAlternateFunction(Ports_t Copy_Port,
                                    Pins_t Copy_Pin,
                                    u8 Copy_AF)
{

	volatile GPIO_t *Local_GPIO = (void *)0;


    switch(Copy_Port)
    {

        case PORTA:
            Local_GPIO=GPIOA;
            break;


        case PORTB:
            Local_GPIO=GPIOB;
            break;


        case PORTC:
            Local_GPIO=GPIOC;
            break;


        default:
            return;
    }



    if(Copy_Pin < 8)
    {

        Local_GPIO->AFRL &=
        ~(0xFUL << (Copy_Pin*4));


        Local_GPIO->AFRL |=
        ((u32)Copy_AF << (Copy_Pin*4));

    }

    else
    {

        Local_GPIO->AFRH &=
        ~(0xFUL << ((Copy_Pin-8)*4));


        Local_GPIO->AFRH |=
        ((u32)Copy_AF << ((Copy_Pin-8)*4));

    }


}
Value_t MGPIO_GetPinValue(
        Ports_t Copy_Port,
        Pins_t Copy_Pin)
{

    volatile GPIO_t *Local_GPIO = (void *)0;


    switch(Copy_Port)
    {

        case PORTA:
            Local_GPIO = GPIOA;
            break;


        case PORTB:
            Local_GPIO = GPIOB;
            break;


        case PORTC:
            Local_GPIO = GPIOC;
            break;


        default:
            return LOW;
    }



    if((Local_GPIO->IDR & (1UL << Copy_Pin)) != 0)
    {
        return HIGH;
    }

    else
    {
        return LOW;
    }

}
