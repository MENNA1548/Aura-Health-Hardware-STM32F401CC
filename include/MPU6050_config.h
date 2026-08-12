#ifndef MPU6050_CONFIG_H
#define MPU6050_CONFIG_H

/* GY-521 AD0 connected to GND */
#define MPU6050_ADDRESS              0x68

/* Sample rate = 100 Hz
 * Gyroscope internal rate = 1 kHz
 * 1000 / (1 + 9) = 100 Hz
 */
#define MPU6050_SAMPLE_RATE_DIV      9

/* Digital Low Pass Filter */
#define MPU6050_DLPF_CONFIG          3

/* Accelerometer: ±2g */
#define MPU6050_ACCEL_CONFIG_VALUE   0

/* Gyroscope: ±250 deg/sec */
#define MPU6050_GYRO_CONFIG_VALUE    0

/* ±2g = 16384 LSB/g */
#define MPU6050_ACCEL_SENSITIVITY    16384.0f

#endif
