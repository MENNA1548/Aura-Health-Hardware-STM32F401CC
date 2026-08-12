#ifndef MI2C_CONFIG_H
#define MI2C_CONFIG_H


/*
 * I2C1 pins
 *
 * PB6 -> SCL
 * PB7 -> SDA
 */

#define MI2C_SCL_PIN       6
#define MI2C_SDA_PIN       7


/*
 * I2C speed
 *
 * Standard Mode = 100 kHz
 */

#define MI2C_SPEED_HZ      100000


/*
 * IMPORTANT:
 *
 * Set this to the actual APB1
 * clock frequency of your STM32.
 *
 * If your STM32 is running with
 * APB1 = 16 MHz, keep:
 */

#define MI2C_PCLK1_HZ      16000000UL


#endif
