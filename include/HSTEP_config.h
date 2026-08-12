#ifndef HSTEP_CONFIG_H
#define HSTEP_CONFIG_H


/********************************************************/
/* Sampling Configuration                               */
/********************************************************/

/*
 * MPU6050 data will be processed every 20 ms.
 *
 * 20 ms = 50 Hz
 */

#define HSTEP_SAMPLE_TIME_MS       20


/********************************************************/
/* Step Detection                                       */
/********************************************************/

/*
 * Dynamic acceleration threshold.
 *
 * Start with 0.15g and calibrate experimentally.
 */

#define HSTEP_STEP_THRESHOLD       0.15f


/*
 * Minimum time between two detected steps.
 *
 * Prevents one step from being counted several times.
 */

#define HSTEP_MIN_STEP_TIME_MS     300


/********************************************************/
/* Walking / Running                                    */
/********************************************************/

/*
 * Steps per minute below this:
 * Walking
 *
 * Above this:
 * Running
 */

#define HSTEP_RUNNING_SPM          120


/********************************************************/
/* Distance                                             */
/********************************************************/

/*
 * Average stride length.
 *
 * 0.70 meter = 70 cm
 */

#define HSTEP_STRIDE_LENGTH_M      0.70f


/********************************************************/
/* Calories                                             */
/********************************************************/

/*
 * Simple project-level estimation.
 *
 * Approximately 0.04 kcal per step.
 *
 * This is an estimate, not a medical-grade calculation.
 */

#define HSTEP_CALORIES_PER_STEP    0.04f


#endif
