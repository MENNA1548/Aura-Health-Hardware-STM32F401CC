/**************************************************************
 * File Name : MUART_Config.h
 **************************************************************/

#ifndef MUART_CONFIG_H_
#define MUART_CONFIG_H_

/**************************************************************
                    USART Configuration
**************************************************************/

/*
Clock = 16 MHz

9600    = 0x0683
19200   = 0x0341
38400   = 0x01A1
57600   = 0x0116
115200  = 0x008B
*/

#define UART_BRR            0x0683

#define UART_WORD_LENGTH    UART_8BIT

#define UART_PARITY         UART_PARITY_NONE

#define UART_STOP_BITS      UART_STOP_1

#endif
