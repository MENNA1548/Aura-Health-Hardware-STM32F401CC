/**************************************************************
 * File Name : MSYSCFG_Interface.h
 * Author    : Your Name
 * Layer     : MCAL
 **************************************************************/

#ifndef MSYSCFG_INTERFACE_H_
#define MSYSCFG_INTERFACE_H_

#include "Std_type.h"
#include "MGPIO_Interface.h"
#include "MEXTI_Interface.h"

/*=========================================================
                APIs
=========================================================*/

/*
 * Select which GPIO Port is connected to an EXTI Line
 *
 * Example:
 * EXTI_LINE0 -> PORTA
 * EXTI_LINE1 -> PORTB
 * EXTI_LINE2 -> PORTC
 */
void MSYSCFG_voidSetEXTIConfig(EXTI_Line_t Copy_Line, Ports_t Copy_Port);

#endif /* MSYSCFG_INTERFACE_H_ */
