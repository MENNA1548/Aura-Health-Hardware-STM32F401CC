
/********************************************************/
/* MPU6050_program.c                                    */
/********************************************************/

#include "Std_type.h"

#include "MPU6050_interface.h"
#include "MPU6050_private.h"
#include "MPU6050_config.h"

/*
 * IMPORTANT:
 * Include your I2C driver here.
 *
 * Change this name if your I2C driver uses another
 * interface filename.
 */
#include "MI2C_interface.h"


/********************************************************/
/* Private Variables                                    */
/********************************************************/

static s16 MPU6050_s16AccelX = 0;
static s16 MPU6050_s16AccelY = 0;
static s16 MPU6050_s16AccelZ = 0;


/********************************************************/
/* Private Functions                                    */
/********************************************************/

static s16 MPU6050_s16ReadTwoBytes(u8 Copy_u8HighRegister)
{
    u8 HighByte;
    u8 LowByte;

    /*
     * Read HIGH byte
     */
    HighByte = MPU6050_u8ReadRegister(Copy_u8HighRegister);

    /*
     * Read LOW byte
     */
    LowByte = MPU6050_u8ReadRegister(Copy_u8HighRegister + 1);

    /*
     * Combine two bytes
     */
    return (s16)(((u16)HighByte << 8) | LowByte);
}


/********************************************************/
/* MPU6050 Initialization                               */
/********************************************************/

void MPU6050_voidInit(void)
{
    /*
     * Wake up MPU6050
     *
     * PWR_MGMT_1 = 0
     */
    MPU6050_voidWriteRegister(
        MPU6050_PWR_MGMT_1,
        0x00
    );


    /*
     * Set sample rate
     *
     * Sample rate = 100 Hz
     */
    MPU6050_voidWriteRegister(
        MPU6050_SMPLRT_DIV,
        MPU6050_SAMPLE_RATE_DIV
    );


    /*
     * Configure Digital Low Pass Filter
     */
    MPU6050_voidWriteRegister(
        MPU6050_CONFIG,
        MPU6050_DLPF_CONFIG
    );


    /*
     * Configure accelerometer
     *
     * ±2g
     */
    MPU6050_voidWriteRegister(
        MPU6050_ACCEL_CONFIG,
        MPU6050_ACCEL_CONFIG_VALUE << 3
    );


    /*
     * Configure gyroscope
     *
     * ±250 degree/sec
     */
    MPU6050_voidWriteRegister(
        MPU6050_GYRO_CONFIG,
        MPU6050_GYRO_CONFIG_VALUE << 3
    );


    /*
     * Disable interrupts for now
     */
    MPU6050_voidWriteRegister(
        MPU6050_INT_ENABLE,
        0x00
    );
}


/********************************************************/
/* Read WHO_AM_I                                       */
/********************************************************/

u8 MPU6050_u8ReadWhoAmI(void)
{
    return MPU6050_u8ReadRegister(
        MPU6050_WHO_AM_I
    );
}


/********************************************************/
/* Read Register                                        */
/********************************************************/

u8 MPU6050_u8ReadRegister(u8 Copy_u8Register)
{
    u8 Local_u8Data = 0;

    /*
     * IMPORTANT:
     *
     * Replace the following I2C calls with the
     * functions from your MI2C driver.
     */

    /*
     * Send register address
     */
    MI2C_voidWriteRead(
        MPU6050_ADDRESS,
        &Copy_u8Register,
        1,
        &Local_u8Data,
        1
    );

    return Local_u8Data;
}


/********************************************************/
/* Write Register                                       */
/********************************************************/

void MPU6050_voidWriteRegister(u8 Copy_u8Register,
                                u8 Copy_u8Data)
{
    u8 Local_u8Buffer[2];

    Local_u8Buffer[0] = Copy_u8Register;
    Local_u8Buffer[1] = Copy_u8Data;

    /*
     * IMPORTANT:
     *
     * Replace this function with the equivalent
     * transmit function from your MI2C driver.
     */

    MI2C_voidMasterTransmit(
        MPU6050_ADDRESS,
        Local_u8Buffer,
        2
    );
}


/********************************************************/
/* Read Accelerometer                                  */
/********************************************************/

void MPU6050_voidReadAccel(s16 *Copy_s16AccelX,
                           s16 *Copy_s16AccelY,
                           s16 *Copy_s16AccelZ)
{
    /*
     * Read X
     */
    MPU6050_s16AccelX =
        MPU6050_s16ReadTwoBytes(
            MPU6050_ACCEL_XOUT_H
        );


    /*
     * Read Y
     */
    MPU6050_s16AccelY =
        MPU6050_s16ReadTwoBytes(
            MPU6050_ACCEL_YOUT_H
        );


    /*
     * Read Z
     */
    MPU6050_s16AccelZ =
        MPU6050_s16ReadTwoBytes(
            MPU6050_ACCEL_ZOUT_H
        );


    /*
     * Return values
     */
    *Copy_s16AccelX = MPU6050_s16AccelX;
    *Copy_s16AccelY = MPU6050_s16AccelY;
    *Copy_s16AccelZ = MPU6050_s16AccelZ;
}


/********************************************************/
/* Read Temperature                                    */
/********************************************************/

s16 MPU6050_s16ReadTemperature(void)
{
    return MPU6050_s16ReadTwoBytes(
        MPU6050_TEMP_OUT_H
    );
}


/********************************************************/
/* Get X Acceleration in g                             */
/********************************************************/

float MPU6050_f32GetAccelX_g(void)
{
    return ((float)MPU6050_s16AccelX /
            MPU6050_ACCEL_SENSITIVITY);
}


/********************************************************/
/* Get Y Acceleration in g                             */
/********************************************************/

float MPU6050_f32GetAccelY_g(void)
{
    return ((float)MPU6050_s16AccelY /
            MPU6050_ACCEL_SENSITIVITY);
}


/********************************************************/
/* Get Z Acceleration in g                             */
/********************************************************/

float MPU6050_f32GetAccelZ_g(void)
{
    return ((float)MPU6050_s16AccelZ /
            MPU6050_ACCEL_SENSITIVITY);
}

