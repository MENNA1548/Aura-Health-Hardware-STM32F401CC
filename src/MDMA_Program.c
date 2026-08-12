#include "Std_type.h"


#include "MDMA_Interface.h"
#include "MDMA_Private.h"

static volatile DMA_RegDef_t* DMAx;

static void MDMA_SelectDMA(DMA_t Copy_DMA)
{
    if(Copy_DMA==DMA1)
        DMAx=DMA1_REG;
    else
        DMAx=DMA2_REG;
}

/************************************************/

void MDMA_voidInit(DMA_t Copy_DMA,
                   DMA_Stream_t Copy_Stream,
                   DMA_Channel_t Copy_Channel)
{
    MDMA_SelectDMA(Copy_DMA);

    CLR_BIT(DMAx->STREAM[Copy_Stream].CR,0);

    while(GET_BIT(DMAx->STREAM[Copy_Stream].CR,0));

    DMAx->STREAM[Copy_Stream].CR &= ~(7<<25);
    DMAx->STREAM[Copy_Stream].CR |= (Copy_Channel<<25);
}

/************************************************/

void MDMA_voidSetDirection(DMA_t Copy_DMA,
                           DMA_Stream_t Copy_Stream,
                           DMA_Direction_t Copy_Direction)
{
    MDMA_SelectDMA(Copy_DMA);

    DMAx->STREAM[Copy_Stream].CR &= ~(3<<6);
    DMAx->STREAM[Copy_Stream].CR |= (Copy_Direction<<6);
}

/************************************************/

void MDMA_voidSetPeripheralAddress(DMA_t Copy_DMA,
                                   DMA_Stream_t Copy_Stream,
                                   u32 Address)
{
    MDMA_SelectDMA(Copy_DMA);

    DMAx->STREAM[Copy_Stream].PAR=Address;
}

/************************************************/

void MDMA_voidSetMemoryAddress(DMA_t Copy_DMA,
                               DMA_Stream_t Copy_Stream,
                               u32 Address)
{
    MDMA_SelectDMA(Copy_DMA);

    DMAx->STREAM[Copy_Stream].M0AR=Address;
}

/************************************************/

void MDMA_voidSetNumberOfData(DMA_t Copy_DMA,
                              DMA_Stream_t Copy_Stream,
                              u16 Copy_Size)
{
    MDMA_SelectDMA(Copy_DMA);

    DMAx->STREAM[Copy_Stream].NDTR=Copy_Size;
}

/************************************************/

void MDMA_voidEnablePeripheralIncrement(DMA_t Copy_DMA,
                                        DMA_Stream_t Copy_Stream,
                                        DMA_IncMode_t Mode)
{
    MDMA_SelectDMA(Copy_DMA);

    if(Mode==DMA_INCREMENT)
        SET_BIT(DMAx->STREAM[Copy_Stream].CR,9);
    else
        CLR_BIT(DMAx->STREAM[Copy_Stream].CR,9);
}

/************************************************/

void MDMA_voidEnableMemoryIncrement(DMA_t Copy_DMA,
                                    DMA_Stream_t Copy_Stream,
                                    DMA_IncMode_t Mode)
{
    MDMA_SelectDMA(Copy_DMA);

    if(Mode==DMA_INCREMENT)
        SET_BIT(DMAx->STREAM[Copy_Stream].CR,10);
    else
        CLR_BIT(DMAx->STREAM[Copy_Stream].CR,10);
}

/************************************************/

void MDMA_voidSetMemorySize(DMA_t Copy_DMA,
                            DMA_Stream_t Copy_Stream,
                            DMA_DataSize_t Size)
{
    MDMA_SelectDMA(Copy_DMA);

    DMAx->STREAM[Copy_Stream].CR &= ~(3<<13);
    DMAx->STREAM[Copy_Stream].CR |= (Size<<13);
}

/************************************************/

void MDMA_voidSetPeripheralSize(DMA_t Copy_DMA,
                                DMA_Stream_t Copy_Stream,
                                DMA_DataSize_t Size)
{
    MDMA_SelectDMA(Copy_DMA);

    DMAx->STREAM[Copy_Stream].CR &= ~(3<<11);
    DMAx->STREAM[Copy_Stream].CR |= (Size<<11);
}

/************************************************/

void MDMA_voidSetPriority(DMA_t Copy_DMA,
                          DMA_Stream_t Copy_Stream,
                          DMA_Priority_t Priority)
{
    MDMA_SelectDMA(Copy_DMA);

    DMAx->STREAM[Copy_Stream].CR &= ~(3<<16);
    DMAx->STREAM[Copy_Stream].CR |= (Priority<<16);
}

/************************************************/

void MDMA_voidEnable(DMA_t Copy_DMA,
                     DMA_Stream_t Copy_Stream)
{
    MDMA_SelectDMA(Copy_DMA);

    SET_BIT(DMAx->STREAM[Copy_Stream].CR,0);
}

/************************************************/

void MDMA_voidDisable(DMA_t Copy_DMA,
                      DMA_Stream_t Copy_Stream)
{
    MDMA_SelectDMA(Copy_DMA);

    CLR_BIT(DMAx->STREAM[Copy_Stream].CR,0);

    while(GET_BIT(DMAx->STREAM[Copy_Stream].CR,0));
}
