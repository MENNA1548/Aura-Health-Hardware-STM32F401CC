#include "Std_type.h"

#include "MSPI_Interface.h"
#include "MSPI_Private.h"



void MSPI_voidMasterInit(void)
{


    /* Disable SPI */
    SPI1->CR1 &= ~(1<<SPI_SPE);



    /*
       Master Mode
       MSTR = 1
    */
    SPI1->CR1 |= (1<<SPI_MSTR);



    /*
       SPI Mode 0

       CPOL = 0
       CPHA = 0
    */
    SPI1->CR1 &= ~(1<<SPI_CPOL);
    SPI1->CR1 &= ~(1<<SPI_CPHA);



    /*
       Baud Rate

       Fpclk / 8

       BR2 BR1 BR0 = 010
    */

    SPI1->CR1 &= ~(1<<SPI_BR0);
    SPI1->CR1 |=  (1<<SPI_BR1);
    SPI1->CR1 &= ~(1<<SPI_BR2);



    /*
       Software Slave Management

       SSM = 1
       SSI = 1
    */

    SPI1->CR1 |= (1<<SPI_SSM);
    SPI1->CR1 |= (1<<SPI_SSI);



    /*
       MSB First
    */

    SPI1->CR1 &= ~(1<<SPI_LSBFIRST);



    /*
       8 bit data
    */

    SPI1->CR1 &= ~(1<<SPI_DFF);



    /*
       Full Duplex
    */

    SPI1->CR1 &= ~(1<<SPI_BIDIMODE);



    /*
       Enable SPI
    */

    SPI1->CR1 |= (1<<SPI_SPE);


}




u8 MSPI_u8Transcieve(u8 Copy_u8Data)
{


    /*
       Wait TX buffer empty
    */

    while(!(SPI1->SR & (1<<SPI_TXE)));



    /*
       Send Data
    */

    SPI1->DR = Copy_u8Data;



    /*
       Wait RX buffer not empty
    */

    while(!(SPI1->SR & (1<<SPI_RXNE)));



    /*
       Read received data
    */

    return (u8)SPI1->DR;


}
