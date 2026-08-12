
#ifndef MPU6050_INTERFACE_H
#define MPU6050_INTERFACE_H

#include "Std_type.h"

/* MPU6050 I2C Address */
#define MPU6050_I2C_ADDRESS    0x68

/* Accelerometer Full Scale */
#define MPU6050_ACCEL_FS_2G    0

/* Initialize MPU6050 */
void MPU6050_voidInit(void);

/* Read WHO_AM_I register */
u8 MPU6050_u8ReadWhoAmI(void);

/* Read one register */
u8 MPU6050_u8ReadRegister(u8 Copy_u8Register);

/* Write one register */
void MPU6050_voidWriteRegister(u8 Copy_u8Register,
                                u8 Copy_u8Data);

/* Read accelerometer raw values */
void MPU6050_voidReadAccel(s16 *Copy_s16AccelX,
                           s16 *Copy_s16AccelY,
                           s16 *Copy_s16AccelZ);

/* Read temperature raw value */
s16 MPU6050_s16ReadTemperature(void);

/* Convert raw acceleration to g */
float MPU6050_f32GetAccelX_g(void);
float MPU6050_f32GetAccelY_g(void);
float MPU6050_f32GetAccelZ_g(void);

#endif

