/*
 * MRCC_interface.h
 *
 *  Created on: Feb 7, 2025
 *      Author: mohamed.hagag
 */

#ifndef MRCC_INTERFACE_H_
#define MRCC_INTERFACE_H_

#include"Std_type.h"

/*************AHB1****************/
#define AHB1_GPIOA 0
#define AHB1_GPIOB 1
#define AHB1_GPIOC 2
#define AHB1_DMA1 21
#define AHB1_DMA2 22

/*************APB1****************/
#define APB1_SPI2   14
#define APB1_SPI3   15
#define APB1_USART2 17

/*************APB2****************/
/*************APB2*************/
#define APB2_USART1   4
#define APB2_USART6   5
#define APB2_SPI1    12
#define APB2_SPI4    13
#define APB2_SYSCFG  14
#define APB2_ADC1     8



typedef enum
{
	AHB1_BUS=0,
	AHB2_BUS,
	APB1_BUS,
	APB2_BUS

}System_Bus;


void MRCC_voidInit(void);
void MRCC_voidEnablePeipheralClock(System_Bus Copy_uddtBus,u8 Copy_u8Peripheral);
void MRCC_voidDisablePeipheralClock(System_Bus Copy_uddtBus,u8 Copy_u8Peripheral);


#endif /* MRCC_INTERFACE_H_ */
