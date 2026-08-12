/*
 * MRCC_program.c
 *
 *  Created on: Feb 7, 2025
 *      Author: mohamed.hagag
 */
#include "Std_type.h"
#include "MRCC_private.h"
#include "MRCC_config.h"
#include "MRCC_interface.h"

void MRCC_voidInit(void)
{
#if(SYSTEM_CLOCK==HSI_CLOCK)
	//HSI ON
	RCC->CR |=(1<<HSION);
	//Set_Bit(RCC->CR,HSION);
	//wait till HSI ready
	while(!GET_BIT(RCC->CR,HSIRDY));
	//while(Get_Bit(RCC->CR,HSIRDY)==0);
	//Switch to HSI-
	RCC->CFGR &=~(SW_MUSK<<SW0);
	RCC->CFGR |=(HSI_Oscillator<<SW0);


#elif(SYSTEM_CLOCK==HSE_CLOCK)
#if(HSE_OSC==MECHANICAL_CLOCK)
	RCC->CR &=~(1<<HSEBYP);
#elif(HSE_OSC==RC_CLOCK)
	RCC->CR |=(1<<HSEBYP);
#endif

	//HSE ON
	RCC->CR |=(1<<HSEON);
	//Set_Bit(RCC->CR,HSEON);
	//wait till HSE ready
	while(!Get_Bit(RCC->CR,HSERDY));
	//while(Get_Bit(RCC->CR,HSERDY)==0);
	//Switch to HSE
	RCC->CFGR &=~(SW_MUSK<<SW0);
	RCC->CFGR |=(HSE_Oscillator<<SW0);
	//disable HSI CLOCK
	RCC->CR &=~(1<<HSION);


#endif
}

void MRCC_voidEnablePeipheralClock(System_Bus Copy_uddtBus,u8 Copy_u8Peripheral)
{
	switch (Copy_uddtBus) {
	case AHB1_BUS:
		RCC->AHB1ENR |=(1<<Copy_u8Peripheral);
		break;
	case AHB2_BUS:
		RCC->AHB2ENR |=(1<<Copy_u8Peripheral);
		break;
	case APB1_BUS:
		RCC->APB1ENR |=(1<<Copy_u8Peripheral);
		break;
	case APB2_BUS:
		RCC->APB2ENR |=(1<<Copy_u8Peripheral);
		break;
	default:
		break;
	}

}
void MRCC_voidDisablePeipheralClock(System_Bus Copy_uddtBus,u8 Copy_u8Peripheral)
{
	switch (Copy_uddtBus) {
	case AHB1_BUS:
		RCC->AHB1ENR &=~(1<<Copy_u8Peripheral);
		break;
	case AHB2_BUS:
		RCC->AHB2ENR &=~(1<<Copy_u8Peripheral);
		break;
	case APB1_BUS:
		RCC->APB1ENR &=~(1<<Copy_u8Peripheral);
		break;
	case APB2_BUS:
		RCC->APB2ENR &=~(1<<Copy_u8Peripheral);
		break;
	default:
		break;
	}

}

