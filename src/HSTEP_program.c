/********************************************************/
/* HSTEP_program.c                                      */
/********************************************************/

#include "Std_type.h"

#include "MPU6050_interface.h"

#include "HSTEP_interface.h"
#include "HSTEP_private.h"
#include "HSTEP_config.h"

#include <math.h>


/********************************************************/
/* Private Variables                                    */
/********************************************************/

static u32 HSTEP_u32Steps = 0;

static float HSTEP_f32Distance = 0.0f;

static float HSTEP_f32Calories = 0.0f;

static u8 HSTEP_u8Activity =
        HSTEP_ACTIVITY_INACTIVE;


/* Previous acceleration value */

static float HSTEP_f32PreviousMotion = 0.0f;


/* Time since last detected step */

static u32 HSTEP_u32TimeSinceLastStep = 0;


/* Number of samples used for activity calculation */

static u32 HSTEP_u32ActivitySamples = 0;


/* Number of detected steps during activity window */

static u32 HSTEP_u32ActivitySteps = 0;


/********************************************************/
/* Private Function Prototypes                          */
/********************************************************/

static float HSTEP_f32CalculateMotion(
        s16 Copy_s16X,
        s16 Copy_s16Y,
        s16 Copy_s16Z);

static void HSTEP_voidDetectStep(
        float Copy_f32Motion);

static void HSTEP_voidUpdateActivity(void);


/********************************************************/
/* Initialization                                       */
/********************************************************/

void HSTEP_voidInit(void)
{
    HSTEP_u32Steps = 0;

    HSTEP_f32Distance = 0.0f;

    HSTEP_f32Calories = 0.0f;

    HSTEP_u8Activity =
            HSTEP_ACTIVITY_INACTIVE;

    HSTEP_f32PreviousMotion = 0.0f;

    HSTEP_u32TimeSinceLastStep = 0;

    HSTEP_u32ActivitySamples = 0;

    HSTEP_u32ActivitySteps = 0;
}


/********************************************************/
/* Update                                               */
/********************************************************/

void HSTEP_voidUpdate(void)
{
    s16 AccelX;
    s16 AccelY;
    s16 AccelZ;

    float Motion;


    /****************************************************/
    /* Read MPU6050                                     */
    /****************************************************/

    MPU6050_voidReadAccel(
        &AccelX,
        &AccelY,
        &AccelZ
    );


    /****************************************************/
    /* Calculate dynamic acceleration                   */
    /****************************************************/

    Motion =
        HSTEP_f32CalculateMotion(
            AccelX,
            AccelY,
            AccelZ
        );


    /****************************************************/
    /* Update step timer                                 */
    /****************************************************/

    HSTEP_u32TimeSinceLastStep +=
            HSTEP_SAMPLE_TIME_MS;


    /****************************************************/
    /* Detect step                                       */
    /****************************************************/

    HSTEP_voidDetectStep(Motion);


    /****************************************************/
    /* Activity                                          */
    /****************************************************/

    HSTEP_u32ActivitySamples++;

    HSTEP_voidUpdateActivity();


    /****************************************************/
    /* Store previous motion                             */
    /****************************************************/

    HSTEP_f32PreviousMotion = Motion;
}


/********************************************************/
/* Calculate Motion                                     */
/********************************************************/

static float HSTEP_f32CalculateMotion(
        s16 Copy_s16X,
        s16 Copy_s16Y,
        s16 Copy_s16Z)
{
    float X;
    float Y;
    float Z;

    float Magnitude;

    float Motion;


    /*
     * Convert raw values to g.
     *
     * MPU6050 is configured for ±2g.
     *
     * 16384 LSB = 1g
     */

    X = (float)Copy_s16X / 16384.0f;

    Y = (float)Copy_s16Y / 16384.0f;

    Z = (float)Copy_s16Z / 16384.0f;


    /*
     * Calculate total acceleration.
     */

    Magnitude =
        sqrtf(
            (X * X) +
            (Y * Y) +
            (Z * Z)
        );


    /*
     * Remove approximately 1g gravity.
     */

    Motion =
        fabsf(Magnitude - HSTEP_GRAVITY);


    return Motion;
}


/********************************************************/
/* Step Detection                                       */
/********************************************************/

static void HSTEP_voidDetectStep(
        float Copy_f32Motion)
{
    /*
     * Detect upward threshold crossing.
     */

    if((Copy_f32Motion >
            HSTEP_STEP_THRESHOLD) &&

       (HSTEP_f32PreviousMotion <=
            HSTEP_STEP_THRESHOLD))
    {
        /*
         * Check minimum time between steps.
         */

        if(HSTEP_u32TimeSinceLastStep >=
                HSTEP_MIN_STEP_TIME_MS)
        {
            /********************************************/
            /* New step                                 */
            /********************************************/

            HSTEP_u32Steps++;

            HSTEP_u32ActivitySteps++;

            HSTEP_u32TimeSinceLastStep = 0;


            /********************************************/
            /* Distance                                 */
            /********************************************/

            HSTEP_f32Distance =
                HSTEP_u32Steps *
                HSTEP_STRIDE_LENGTH_M;


            /********************************************/
            /* Calories                                 */
            /********************************************/

            HSTEP_f32Calories =
                HSTEP_u32Steps *
                HSTEP_CALORIES_PER_STEP;
        }
    }
}


/********************************************************/
/* Activity Classification                              */
/********************************************************/

static void HSTEP_voidUpdateActivity(void)
{
    /*
     * Evaluate activity every 5 seconds.
     *
     * 5 seconds / 20 ms = 250 samples
     */

    if(HSTEP_u32ActivitySamples >= 250)
    {
        /*
         * Convert detected steps to
         * approximate steps/minute.
         *
         * 5 second window × 12
         */

        u32 StepsPerMinute =
            HSTEP_u32ActivitySteps * 12;


        if(HSTEP_u32ActivitySteps == 0)
        {
            HSTEP_u8Activity =
                HSTEP_ACTIVITY_INACTIVE;
        }

        else if(StepsPerMinute <
                HSTEP_RUNNING_SPM)
        {
            HSTEP_u8Activity =
                HSTEP_ACTIVITY_WALKING;
        }

        else
        {
            HSTEP_u8Activity =
                HSTEP_ACTIVITY_RUNNING;
        }


        /*
         * Reset activity window.
         */

        HSTEP_u32ActivitySamples = 0;

        HSTEP_u32ActivitySteps = 0;
    }
}


/********************************************************/
/* Get Steps                                            */
/********************************************************/

u32 HSTEP_u32GetSteps(void)
{
    return HSTEP_u32Steps;
}


/********************************************************/
/* Get Distance                                         */
/********************************************************/

float HSTEP_f32GetDistance(void)
{
    return HSTEP_f32Distance;
}


/********************************************************/
/* Get Calories                                         */
/********************************************************/

float HSTEP_f32GetCalories(void)
{
    return HSTEP_f32Calories;
}


/********************************************************/
/* Get Activity                                         */
/********************************************************/

u8 HSTEP_u8GetActivity(void)
{
    return HSTEP_u8Activity;
}


/********************************************************/
/* Reset                                                */
/********************************************************/

void HSTEP_voidReset(void)
{
    HSTEP_u32Steps = 0;

    HSTEP_f32Distance = 0.0f;

    HSTEP_f32Calories = 0.0f;

    HSTEP_u8Activity =
        HSTEP_ACTIVITY_INACTIVE;

    HSTEP_f32PreviousMotion = 0.0f;

    HSTEP_u32TimeSinceLastStep = 0;

    HSTEP_u32ActivitySamples = 0;

    HSTEP_u32ActivitySteps = 0;
}
