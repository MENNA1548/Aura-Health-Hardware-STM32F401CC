#include "Std_type.h"

#include "MI2C_interface.h"
#include "MI2C_private.h"
#include "MI2C_config.h"


/********************************************************/
/* Private Functions                                    */
/********************************************************/

static void MI2C_voidStart(void);

static void MI2C_voidStop(void);

static void MI2C_voidSendAddress(u8 Copy_u8Address);

static void MI2C_voidClearAddressFlag(void);


/********************************************************/
/* I2C Initialization                                   */
/********************************************************/

void MI2C_voidInit(void)
{
    /****************************************************/
    /* Enable GPIOB clock                               */
    /****************************************************/

    RCC_AHB1ENR |= (1U << 1);


    /****************************************************/
    /* Enable I2C1 clock                                */
    /****************************************************/

    RCC_APB1ENR |= (1U << 21);


    /****************************************************/
    /* PB6 -> Alternate Function                        */
    /* PB7 -> Alternate Function                        */
    /****************************************************/

    GPIOB_MODER &= ~(
            (3U << (6 * 2)) |
            (3U << (7 * 2))
    );

    GPIOB_MODER |= (
            (2U << (6 * 2)) |
            (2U << (7 * 2))
    );


    /****************************************************/
    /* Open Drain                                        */
    /****************************************************/

    GPIOB_OTYPER |= (
            (1U << 6) |
            (1U << 7)
    );


    /****************************************************/
    /* Pull-up                                            */
    /****************************************************/

    GPIOB_PUPDR &= ~(
            (3U << (6 * 2)) |
            (3U << (7 * 2))
    );

    GPIOB_PUPDR |= (
            (1U << (6 * 2)) |
            (1U << (7 * 2))
    );


    /****************************************************/
    /* AF4 = I2C1                                        */
    /****************************************************/

    GPIOB_AFRL &= ~(
            (0xFU << (6 * 4)) |
            (0xFU << (7 * 4))
    );

    GPIOB_AFRL |= (
            (4U << (6 * 4)) |
            (4U << (7 * 4))
    );


    /****************************************************/
    /* Disable I2C before configuration                  */
    /****************************************************/

    MI2C1->CR1 = 0;


    /****************************************************/
    /* APB1 clock frequency                             */
    /****************************************************/

    MI2C1->CR2 =
            (MI2C_PCLK1_HZ / 1000000UL);


    /****************************************************/
    /* Standard mode 100 kHz                             */
    /****************************************************/

    MI2C1->CCR =
            (MI2C_PCLK1_HZ /
             (2UL * MI2C_SPEED_HZ));


    /****************************************************/
    /* Maximum rise time                                */
    /****************************************************/

    MI2C1->TRISE =
            (MI2C_PCLK1_HZ / 1000000UL) + 1;


    /****************************************************/
    /* Enable I2C                                       */
    /****************************************************/

    MI2C1->CR1 |= MI2C_CR1_PE;
}


/********************************************************/
/* Start                                                */
/********************************************************/

static void MI2C_voidStart(void)
{
    MI2C1->CR1 |= MI2C_CR1_START;

    while(!(MI2C1->SR1 & MI2C_SR1_SB));
}


/********************************************************/
/* Stop                                                 */
/********************************************************/

static void MI2C_voidStop(void)
{
    MI2C1->CR1 |= MI2C_CR1_STOP;
}


/********************************************************/
/* Send Address                                         */
/********************************************************/

static void MI2C_voidSendAddress(u8 Copy_u8Address)
{
    MI2C1->DR = Copy_u8Address;

    while(!(MI2C1->SR1 & MI2C_SR1_ADDR));

    MI2C_voidClearAddressFlag();
}


/********************************************************/
/* Clear ADDR flag                                      */
/********************************************************/

static void MI2C_voidClearAddressFlag(void)
{
    volatile u32 Dummy;

    Dummy = MI2C1->SR1;
    Dummy = MI2C1->SR2;

    (void)Dummy;
}


/********************************************************/
/* Master Transmit                                      */
/********************************************************/

void MI2C_voidMasterTransmit(
        u8 Copy_u8Address,
        u8 *Copy_pu8Data,
        u8 Copy_u8Size)
{
    u8 Local_u8Counter;


    /****************************************************/
    /* Wait until bus is free                           */
    /****************************************************/

    while(MI2C1->SR2 & MI2C_SR2_BUSY);


    /****************************************************/
    /* START                                            */
    /****************************************************/

    MI2C_voidStart();


    /****************************************************/
    /* Address + Write                                  */
    /****************************************************/

    MI2C_voidSendAddress(
            (Copy_u8Address << 1)
    );


    /****************************************************/
    /* Send data                                        */
    /****************************************************/

    for(Local_u8Counter = 0;
        Local_u8Counter < Copy_u8Size;
        Local_u8Counter++)
    {
        while(!(MI2C1->SR1 & MI2C_SR1_TXE));

        MI2C1->DR =
                Copy_pu8Data[Local_u8Counter];
    }


    /****************************************************/
    /* Wait until transfer complete                     */
    /****************************************************/

    while(!(MI2C1->SR1 & MI2C_SR1_BTF));


    /****************************************************/
    /* STOP                                             */
    /****************************************************/

    MI2C_voidStop();
}


/********************************************************/
/* Write Then Read                                      */
/********************************************************/

void MI2C_voidWriteRead(
        u8 Copy_u8Address,
        u8 *Copy_pu8WriteData,
        u8 Copy_u8WriteSize,
        u8 *Copy_pu8ReadData,
        u8 Copy_u8ReadSize)
{
    u8 Local_u8Counter;


    /****************************************************/
    /* Wait for bus                                     */
    /****************************************************/

    while(MI2C1->SR2 & MI2C_SR2_BUSY);


    /****************************************************/
    /* START                                            */
    /****************************************************/

    MI2C_voidStart();


    /****************************************************/
    /* Send slave address + WRITE                       */
    /****************************************************/

    MI2C_voidSendAddress(
            (Copy_u8Address << 1)
    );


    /****************************************************/
    /* Send register address                            */
    /****************************************************/

    for(Local_u8Counter = 0;
        Local_u8Counter < Copy_u8WriteSize;
        Local_u8Counter++)
    {
        while(!(MI2C1->SR1 & MI2C_SR1_TXE));

        MI2C1->DR =
                Copy_pu8WriteData[Local_u8Counter];
    }


    /****************************************************/
    /* Wait for byte transfer                           */
    /****************************************************/

    while(!(MI2C1->SR1 & MI2C_SR1_BTF));


    /****************************************************/
    /* RESTART                                          */
    /****************************************************/

    MI2C1->CR1 |= MI2C_CR1_START;

    while(!(MI2C1->SR1 & MI2C_SR1_SB));


    /****************************************************/
    /* Address + READ                                   */
    /****************************************************/

    MI2C1->DR =
            (Copy_u8Address << 1) | 1;


    while(!(MI2C1->SR1 & MI2C_SR1_ADDR));


    /*
     * For the MPU6050 reads used here,
     * we normally read one byte.
     */

    if(Copy_u8ReadSize == 1)
    {
        /*
         * Clear ACK.
         */

        MI2C1->CR1 &= ~MI2C_CR1_ACK;

        MI2C_voidClearAddressFlag();

        /*
         * STOP.
         */

        MI2C_voidStop();

        /*
         * Wait for received byte.
         */

        while(!(MI2C1->SR1 & MI2C_SR1_RXNE));

        Copy_pu8ReadData[0] =
                (u8)MI2C1->DR;

        /*
         * Re-enable ACK.
         */

        MI2C1->CR1 |= MI2C_CR1_ACK;
    }

    else
    {
        /*
         * General multiple-byte read.
         */

        MI2C1->CR1 |= MI2C_CR1_ACK;

        MI2C_voidClearAddressFlag();

        for(Local_u8Counter = 0;
            Local_u8Counter < Copy_u8ReadSize;
            Local_u8Counter++)
        {
            if(Local_u8Counter ==
                    Copy_u8ReadSize - 1)
            {
                /*
                 * Last byte
                 */

                MI2C1->CR1 &= ~MI2C_CR1_ACK;

                MI2C_voidStop();
            }

            while(!(MI2C1->SR1 & MI2C_SR1_RXNE));

            Copy_pu8ReadData[Local_u8Counter] =
                    (u8)MI2C1->DR;
        }

        MI2C1->CR1 |= MI2C_CR1_ACK;
    }
}
