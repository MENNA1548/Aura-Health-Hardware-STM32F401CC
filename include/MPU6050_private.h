
#ifndef MPU6050_PRIVATE_H
#define MPU6050_PRIVATE_H


/********************************************************/
/* MPU6050 Registers                                    */
/********************************************************/

#define MPU6050_SMPLRT_DIV       0x19
#define MPU6050_CONFIG           0x1A
#define MPU6050_GYRO_CONFIG      0x1B
#define MPU6050_ACCEL_CONFIG     0x1C
#define MPU6050_INT_ENABLE       0x38

#define MPU6050_ACCEL_XOUT_H     0x3B
#define MPU6050_ACCEL_XOUT_L     0x3C

#define MPU6050_ACCEL_YOUT_H     0x3D
#define MPU6050_ACCEL_YOUT_L     0x3E

#define MPU6050_ACCEL_ZOUT_H     0x3F
#define MPU6050_ACCEL_ZOUT_L     0x40

#define MPU6050_TEMP_OUT_H       0x41
#define MPU6050_TEMP_OUT_L       0x42

#define MPU6050_PWR_MGMT_1       0x6B
#define MPU6050_PWR_MGMT_2       0x6C

#define MPU6050_WHO_AM_I         0x75


/********************************************************/
/* MPU6050 Expected ID                                  */
/********************************************************/

#define MPU6050_WHO_AM_I_VALUE   0x68


/********************************************************/
/* Accelerometer Sensitivity                            */
/********************************************************/

/*
 * ±2g  -> 16384 LSB/g
 * ±4g  -> 8192  LSB/g
 * ±8g  -> 4096  LSB/g
 * ±16g -> 2048  LSB/g
 */

#define MPU6050_ACCEL_SENSITIVITY    16384.0f


/********************************************************/
/* Private Functions                                    */
/********************************************************/

static s16 MPU6050_s16ReadTwoBytes(u8 Copy_u8HighRegister);

#endif

