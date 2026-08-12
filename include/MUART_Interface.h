/**************************************************************
 * File Name : MUART_Interface.h
 * Author    : Menna
 * Layer     : MCAL
 **************************************************************/

#ifndef MUART_INTERFACE_H_
#define MUART_INTERFACE_H_

#include "Std_type.h"

/**************************************************************
                        USART IDs
**************************************************************/

typedef enum
{
    USART1_ID = 0,
    USART2_ID,
    USART6_ID

}UART_t;

/**************************************************************
                      Word Length
**************************************************************/

typedef enum
{
    UART_8BIT = 0,
    UART_9BIT

}UART_WordLength_t;

/**************************************************************
                         Parity
**************************************************************/

typedef enum
{
    UART_PARITY_NONE = 0,
    UART_PARITY_EVEN,
    UART_PARITY_ODD

}UART_Parity_t;

/**************************************************************
                        Stop Bits
**************************************************************/

typedef enum
{
    UART_STOP_1 = 0,
    UART_STOP_HALF,
    UART_STOP_2,
    UART_STOP_ONE_HALF

}UART_StopBits_t;

/**************************************************************
                           APIs
**************************************************************/

void MUART_voidInit(UART_t Copy_UART);

void MUART_voidTransmitChar(UART_t Copy_UART,u8 Copy_Data);

void MUART_voidTransmitString(UART_t Copy_UART,const u8 *Copy_String);

u8 MUART_u8ReceiveChar(UART_t Copy_UART);

void MUART_voidReceiveString(UART_t Copy_UART,u8 *Copy_Buffer);

#endif
