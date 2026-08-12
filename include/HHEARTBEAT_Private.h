/*
 * HHEARTBEAT_Private.h
 *
 * Created on: Aug 2026
 * Author: admin
 */

#ifndef HHEARTBEAT_PRIVATE_H_
#define HHEARTBEAT_PRIVATE_H_


/*=========================================================
 * Heartbeat Internal Definitions
 *=========================================================*/


/*
 * Minimum time between two beats
 * 300 ms = 200 BPM maximum
 */
#define HHEARTBEAT_MIN_PERIOD_MS      300



/*
 * Maximum time between two beats
 * 2000 ms = 30 BPM minimum
 */
#define HHEARTBEAT_MAX_PERIOD_MS      2000



/*
 * Sampling period
 * The driver checks the sensor every 10 ms
 */
#define HHEARTBEAT_SAMPLE_TIME_MS     10



/*
 * Convert milliseconds to one minute
 * BPM = 60000 / Beat Period
 */
#define HHEARTBEAT_ONE_MINUTE_MS      60000



/*
 * Sensor states
 */

#define HHEARTBEAT_BEAT_DETECTED      1
#define HHEARTBEAT_NO_BEAT            0



#endif /* HHEARTBEAT_PRIVATE_H_ */
