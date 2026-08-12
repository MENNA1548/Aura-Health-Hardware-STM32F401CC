/**************************************************************
 * File Name : MUART_Program.c
 * Author    : Menna
 * Layer     : MCAL
 **************************************************************/

#include "Std_type.h"

#include "MUART_Interface.h"
#include "MUART_Private.h"
#include "MUART_Config.h"

/**************************************************************
                    UART Array
**************************************************************/

static volatile USART_t *UART[3] =
{
    USART1,
    USART2,
    USART6
};

/**************************************************************
                    Initialization
**************************************************************/

void MUART_voidInit(UART_t Copy_UART)
{
    /* Disable USART before configuration */
    UART[Copy_UART]->CR1 = 0;
    UART[Copy_UART]->CR2 = 0;
    UART[Copy_UART]->CR3 = 0;

    /* Set Baud Rate */
    UART[Copy_UART]->BRR = UART_BRR;

    /**************** Word Length ****************/

#if (UART_WORD_LENGTH == UART_8BIT)

    UART[Copy_UART]->CR1 &= ~(1 << M);

#elif (UART_WORD_LENGTH == UART_9BIT)

    UART[Copy_UART]->CR1 |= (1 << M);

#endif

    /**************** Parity ****************/

#if (UART_PARITY == UART_PARITY_NONE)

    UART[Copy_UART]->CR1 &= ~(1 << PCE);

#elif (UART_PARITY == UART_PARITY_EVEN)

    UART[Copy_UART]->CR1 |= (1 << PCE);
    UART[Copy_UART]->CR1 &= ~(1 << PS);

#elif (UART_PARITY == UART_PARITY_ODD)

    UART[Copy_UART]->CR1 |= (1 << PCE);
    UART[Copy_UART]->CR1 |= (1 << PS);

#endif

    /**************** Stop Bits ****************/

#if (UART_STOP_BITS == UART_STOP_1)

    UART[Copy_UART]->CR2 &= ~(3 << STOP0);

#elif (UART_STOP_BITS == UART_STOP_HALF)

    UART[Copy_UART]->CR2 &= ~(3 << STOP0);
    UART[Copy_UART]->CR2 |=  (1 << STOP0);

#elif (UART_STOP_BITS == UART_STOP_2)

    UART[Copy_UART]->CR2 &= ~(3 << STOP0);
    UART[Copy_UART]->CR2 |=  (2 << STOP0);

#elif (UART_STOP_BITS == UART_STOP_ONE_HALF)

    UART[Copy_UART]->CR2 &= ~(3 << STOP0);
    UART[Copy_UART]->CR2 |=  (3 << STOP0);

#endif

    /* Enable Transmitter */
    UART[Copy_UART]->CR1 |= (1 << TE);

    /* Enable Receiver */
    UART[Copy_UART]->CR1 |= (1 << RE);

    /* Enable USART */
    UART[Copy_UART]->CR1 |= (1 << UE);
}

/**************************************************************
                Send One Character
**************************************************************/

void MUART_voidTransmitChar(UART_t Copy_UART, u8 Copy_Data)
{
    /* Wait until TX register is empty */
    while(!(UART[Copy_UART]->SR & (1 << TXE)));

    /* Send data */
    UART[Copy_UART]->DR = Copy_Data;

    /* Wait until transmission complete */
    while(!(UART[Copy_UART]->SR & (1 << TC)));
}

/**************************************************************
                Send String
**************************************************************/

void MUART_voidTransmitString(UART_t Copy_UART, const u8 *Copy_String)
{
    while(*Copy_String != '\0')
    {
        MUART_voidTransmitChar(Copy_UART, *Copy_String);
        Copy_String++;
    }
}

/**************************************************************
                Receive One Character
**************************************************************/

u8 MUART_u8ReceiveChar(UART_t Copy_UART)
{
    /* Wait until data is received */
    while(!(UART[Copy_UART]->SR & (1 << RXNE)));

    return (u8)(UART[Copy_UART]->DR);
}

/**************************************************************
                Receive String
**************************************************************/

void MUART_voidReceiveString(UART_t Copy_UART, u8 *Copy_Buffer)
{
    u8 Local_u8Index = 0;
    u8 Local_u8Data;

    while(1)
    {
        Local_u8Data = MUART_u8ReceiveChar(Copy_UART);

        if(Local_u8Data == '\r' || Local_u8Data == '\n')
        {
            break;
        }

        Copy_Buffer[Local_u8Index] = Local_u8Data;
        Local_u8Index++;
    }

    Copy_Buffer[Local_u8Index] = '\0';
}
