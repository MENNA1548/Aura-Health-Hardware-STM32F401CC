#ifndef MI2C_PRIVATE_H
#define MI2C_PRIVATE_H


/********************************************************/
/* I2C Registers                                        */
/********************************************************/

/* I2C1 base address */

#define MI2C1_BASE_ADDRESS       0x40005400UL


/********************************************************/
/* Register Structure                                   */
/********************************************************/

typedef struct
{
    volatile u32 CR1;
    volatile u32 CR2;
    volatile u32 OAR1;
    volatile u32 OAR2;
    volatile u32 DR;
    volatile u32 SR1;
    volatile u32 SR2;
    volatile u32 CCR;
    volatile u32 TRISE;
    volatile u32 FLTR;

} MI2C_Registers_t;


#define MI2C1    ((MI2C_Registers_t *)MI2C1_BASE_ADDRESS)


/********************************************************/
/* RCC                                                  */
/********************************************************/

#define RCC_BASE_ADDRESS         0x40023800UL

#define RCC_AHB1ENR_OFFSET       0x30
#define RCC_APB1ENR_OFFSET       0x40

#define RCC_AHB1ENR              (*(volatile u32 *)(RCC_BASE_ADDRESS + RCC_AHB1ENR_OFFSET))
#define RCC_APB1ENR              (*(volatile u32 *)(RCC_BASE_ADDRESS + RCC_APB1ENR_OFFSET))


/********************************************************/
/* GPIOB                                                */
/********************************************************/

#define GPIOB_BASE_ADDRESS       0x40020400UL

#define GPIOB_MODER              (*(volatile u32 *)(GPIOB_BASE_ADDRESS + 0x00))
#define GPIOB_OTYPER             (*(volatile u32 *)(GPIOB_BASE_ADDRESS + 0x04))
#define GPIOB_PUPDR              (*(volatile u32 *)(GPIOB_BASE_ADDRESS + 0x0C))
#define GPIOB_AFRL               (*(volatile u32 *)(GPIOB_BASE_ADDRESS + 0x20))


/********************************************************/
/* I2C CR1 bits                                         */
/********************************************************/

#define MI2C_CR1_PE              (1U << 0)
#define MI2C_CR1_START           (1U << 8)
#define MI2C_CR1_STOP            (1U << 9)
#define MI2C_CR1_ACK             (1U << 10)


/********************************************************/
/* I2C SR1 bits                                         */
/********************************************************/

#define MI2C_SR1_SB              (1U << 0)
#define MI2C_SR1_ADDR            (1U << 1)
#define MI2C_SR1_BTF             (1U << 2)
#define MI2C_SR1_RXNE            (1U << 6)
#define MI2C_SR1_TXE             (1U << 7)


/********************************************************/
/* I2C SR2 bits                                         */
/********************************************************/

#define MI2C_SR2_BUSY            (1U << 1)


#endif
