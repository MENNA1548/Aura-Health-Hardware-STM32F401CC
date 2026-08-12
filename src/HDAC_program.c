/*
 * HDAC_program.c
 *
 *  Created on: Mar 15, 2025
 *      Author: mohamed.hagag
 */
#include "Std_type.h"

#include "MGPIO_Interface.h"
#include "HDAC_interface.h"



void HDAC_voidInit(void)
{
	u8 i=0;
	for(i=0;i<8;i++)
	{
		MGPIO_voidSetMode(PORTA,i,OUTPUT);
		MGPIO_voidSetOutputConfig(PORTA, i, PUSH_PULL, LOW_SPEED);
	}

}
void HDAC_voidSendSample(const u8 *Copy_u8Ptr,u32 Copy_u32Index)
{
	//0b10100011
	u8 i=0;
	for(i=0;i<8;i++)
		{
		MGPIO_voidSetPinValue(PORTA,
		                      (Pins_t)i,
		                      (Value_t)((Copy_u8Ptr[Copy_u32Index] >> i) & 0x01));
		}

}





