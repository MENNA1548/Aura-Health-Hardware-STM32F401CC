#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#include "Std_type.h"

/*=========================================================
 *              IRQ NUMBER TYPE
 *========================================================*/

typedef enum
{
    WWDG_IRQn = 0,
    EXTI16_PVD_IRQn,
    EXTI21_TAMP_STAMP_IRQn,
    EXTI22_RTC_WKUP_IRQn,
    FLASH_IRQn,
    RCC_IRQn,
    EXTI0_IRQn,
    EXTI1_IRQn,
    EXTI2_IRQn,
    EXTI3_IRQn,
    EXTI4_IRQn,
    DMA1_Stream0_IRQn,
    DMA1_Stream1_IRQn,
    DMA1_Stream2_IRQn,
    DMA1_Stream3_IRQn,
    DMA1_Stream4_IRQn,
    DMA1_Stream5_IRQn,
    DMA1_Stream6_IRQn,

    ADC_IRQn = 18,

    EXTI9_5_IRQn = 23,

    TIM1_BRK_TIM9_IRQn,
    TIM1_UP_TIM10_IRQn,
    TIM1_TRG_COM_TIM11_IRQn,
    TIM1_CC_IRQn,
    TIM2_IRQn,
    TIM3_IRQn,
    TIM4_IRQn,
    I2C1_EV_IRQn,
    I2C1_ER_IRQn,
    I2C2_EV_IRQn,
    I2C2_ER_IRQn,
    SPI1_IRQn,
    SPI2_IRQn,
    USART1_IRQn,
    USART2_IRQn,

    EXTI15_10_IRQn = 40,
    EXTI17_RTC_Alarm_IRQn,
    EXTI18_OTG_FS_WKUP_IRQn,

    DMA1_Stream7_IRQn = 47,

    SDIO_IRQn = 49,
    TIM5_IRQn,
    SPI3_IRQn,

    DMA2_Stream0_IRQn = 56,
    DMA2_Stream1_IRQn,
    DMA2_Stream2_IRQn,
    DMA2_Stream3_IRQn,
    DMA2_Stream4_IRQn,

    OTG_FS_IRQn = 67,
    DMA2_Stream5_IRQn,
    DMA2_Stream6_IRQn,
    DMA2_Stream7_IRQn,

    USART6_IRQn,
    I2C3_EV_IRQn,
    I2C3_ER_IRQn,

    FPU_IRQn = 81,

    SPI4_IRQn = 84

} IRQn_t;


/*=========================================================
 *              Priority Grouping Macros
 *========================================================*/

#define NVIC_GROUP_4_SUB_0    0x05FA0300UL
#define NVIC_GROUP_3_SUB_1    0x05FA0400UL
#define NVIC_GROUP_2_SUB_2    0x05FA0500UL
#define NVIC_GROUP_1_SUB_3    0x05FA0600UL
#define NVIC_GROUP_0_SUB_4    0x05FA0700UL


/*=========================================================
 *              Function Prototypes
 *========================================================*/

/* Set Priority Grouping */
void NVIC_SetPriorityGrouping(u32 priority_grouping);

/* Enable Interrupt */
void NVIC_EnableIRQ(IRQn_t IRQn);

/* Disable Interrupt */
void NVIC_DisableIRQ(IRQn_t IRQn);

/* Get Pending Status */
u32 NVIC_GetPendingIRQ(IRQn_t IRQn);

/* Set Pending */
void NVIC_SetPendingIRQ(IRQn_t IRQn);

/* Clear Pending */
void NVIC_ClearPendingIRQ(IRQn_t IRQn);

/* Get Active Status */
u32 NVIC_GetActive(IRQn_t IRQn);

/* Set Interrupt Priority */
void NVIC_SetPriority(IRQn_t IRQn, u32 priority);

/* Get Interrupt Priority */
u32 NVIC_GetPriority(IRQn_t IRQn);

/* System Reset */
void NVIC_SystemReset(void);
void NVIC_GenerateSoftwareInterrupt(IRQn_t IRQn);
#endif /* NVIC_INTERFACE_H_ */
