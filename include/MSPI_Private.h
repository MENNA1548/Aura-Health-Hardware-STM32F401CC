#ifndef MSPI_PRIVATE_H_
#define MSPI_PRIVATE_H_

#include "Std_type.h"


#define SPI1_BASE_ADDRESS   0x40013000UL


typedef struct
{

    volatile u32 CR1;
    volatile u32 CR2;
    volatile u32 SR;
    volatile u32 DR;
    volatile u32 CRCPR;
    volatile u32 RXCRCR;
    volatile u32 TXCRCR;
    volatile u32 I2SCFGR;
    volatile u32 I2SPR;

}SPI_t;



#define SPI1 ((volatile SPI_t*)SPI1_BASE_ADDRESS)



/* CR1 Bits */

#define SPI_CPHA        0
#define SPI_CPOL        1
#define SPI_MSTR        2

#define SPI_BR0         3
#define SPI_BR1         4
#define SPI_BR2         5

#define SPI_SPE         6

#define SPI_LSBFIRST    7

#define SPI_SSI         8
#define SPI_SSM         9

#define SPI_RXONLY      10

#define SPI_DFF         11

#define SPI_BIDIOE      14
#define SPI_BIDIMODE    15



/* Status Register Bits */

#define SPI_RXNE        0
#define SPI_TXE         1
#define SPI_BSY         7



#endif
