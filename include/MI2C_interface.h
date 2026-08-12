#ifndef MI2C_INTERFACE_H
#define MI2C_INTERFACE_H

#include "Std_type.h"


/********************************************************/
/* I2C Initialization                                   */
/********************************************************/

void MI2C_voidInit(void);


/********************************************************/
/* Master Transmit                                      */
/********************************************************/

/*
 * Send multiple bytes to an I2C slave.
 *
 * Copy_u8Address:
 *     7-bit slave address
 *
 * Copy_pu8Data:
 *     Data buffer
 *
 * Copy_u8Size:
 *     Number of bytes
 */

void MI2C_voidMasterTransmit(
        u8 Copy_u8Address,
        u8 *Copy_pu8Data,
        u8 Copy_u8Size);


/********************************************************/
/* Write Then Read                                      */
/********************************************************/

/*
 * Used by MPU6050:
 *
 * 1. Send register address
 * 2. Read register data
 */

void MI2C_voidWriteRead(
        u8 Copy_u8Address,
        u8 *Copy_pu8WriteData,
        u8 Copy_u8WriteSize,
        u8 *Copy_pu8ReadData,
        u8 Copy_u8ReadSize);


#endif
