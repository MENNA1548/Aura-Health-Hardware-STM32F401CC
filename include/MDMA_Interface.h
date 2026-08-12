/*
 * MDMA_Interface.h
 *
 * Created on: Jul 29, 2026
 */

#ifndef MDMA_INTERFACE_H_
#define MDMA_INTERFACE_H_

#include "Std_type.h"

/************************************************
 * DMA Numbers
 ***********************************************/

typedef enum
{
    DMA1 = 0,
    DMA2

}DMA_t;


/************************************************
 * Streams
 ***********************************************/

typedef enum
{
    STREAM0 = 0,
    STREAM1,
    STREAM2,
    STREAM3,
    STREAM4,
    STREAM5,
    STREAM6,
    STREAM7

}DMA_Stream_t;


/************************************************
 * Channels
 ***********************************************/

typedef enum
{
    CHANNEL0 = 0,
    CHANNEL1,
    CHANNEL2,
    CHANNEL3,
    CHANNEL4,
    CHANNEL5,
    CHANNEL6,
    CHANNEL7

}DMA_Channel_t;


/************************************************
 * Direction
 ***********************************************/

typedef enum
{
    PERIPHERAL_TO_MEMORY = 0,
    MEMORY_TO_PERIPHERAL,
    MEMORY_TO_MEMORY

}DMA_Direction_t;


/************************************************
 * Data Size
 ***********************************************/

typedef enum
{
    DMA_BYTE = 0,
    DMA_HALF_WORD,
    DMA_WORD

}DMA_DataSize_t;


/************************************************
 * Increment
 ***********************************************/

typedef enum
{
    DMA_FIXED = 0,
    DMA_INCREMENT

}DMA_IncMode_t;


/************************************************
 * Priority
 ***********************************************/

typedef enum
{
    DMA_LOW = 0,
    DMA_MEDIUM,
    DMA_HIGH,
    DMA_VERY_HIGH

}DMA_Priority_t;


/************************************************
 * APIs
 ***********************************************/

void MDMA_voidInit(DMA_t Copy_DMA,
                   DMA_Stream_t Copy_Stream,
                   DMA_Channel_t Copy_Channel);

void MDMA_voidSetDirection(DMA_t Copy_DMA,
                           DMA_Stream_t Copy_Stream,
                           DMA_Direction_t Copy_Direction);

void MDMA_voidSetPeripheralAddress(DMA_t Copy_DMA,
                                   DMA_Stream_t Copy_Stream,
                                   u32 Address);

void MDMA_voidSetMemoryAddress(DMA_t Copy_DMA,
                               DMA_Stream_t Copy_Stream,
                               u32 Address);

void MDMA_voidSetNumberOfData(DMA_t Copy_DMA,
                              DMA_Stream_t Copy_Stream,
                              u16 Copy_Size);

void MDMA_voidEnablePeripheralIncrement(DMA_t Copy_DMA,
                                        DMA_Stream_t Copy_Stream,
                                        DMA_IncMode_t Mode);

void MDMA_voidEnableMemoryIncrement(DMA_t Copy_DMA,
                                    DMA_Stream_t Copy_Stream,
                                    DMA_IncMode_t Mode);

void MDMA_voidSetMemorySize(DMA_t Copy_DMA,
                            DMA_Stream_t Copy_Stream,
                            DMA_DataSize_t Size);

void MDMA_voidSetPeripheralSize(DMA_t Copy_DMA,
                                DMA_Stream_t Copy_Stream,
                                DMA_DataSize_t Size);

void MDMA_voidSetPriority(DMA_t Copy_DMA,
                          DMA_Stream_t Copy_Stream,
                          DMA_Priority_t Priority);

void MDMA_voidEnable(DMA_t Copy_DMA,
                     DMA_Stream_t Copy_Stream);

void MDMA_voidDisable(DMA_t Copy_DMA,
                      DMA_Stream_t Copy_Stream);

#endif
