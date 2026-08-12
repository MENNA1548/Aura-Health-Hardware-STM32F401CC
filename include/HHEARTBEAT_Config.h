#ifndef HHEARTBEAT_CONFIG_H_
#define HHEARTBEAT_CONFIG_H_


/*
 * HW-827 Heartbeat Sensor
 *
 * Connection:
 * Signal ---> PA0 ---> ADC1 Channel 0
 *
 */

#define HEARTBEAT_ADC_CHANNEL        0



/*
 * Sampling period
 *
 * HHEARTBEAT_u8GetBPM()
 * must be called every 10 ms
 *
 */

#define HEARTBEAT_SAMPLE_TIME        10



/*
 * ADC Detection Threshold
 *
 * ADC Range:
 * 0 ---- 4095
 *
 * Adjust after testing sensor values
 *
 */

#define HEARTBEAT_THRESHOLD          1800



/*
 * Valid heartbeat period
 *
 * 300ms  = 200 BPM
 * 2000ms = 30 BPM
 *
 */

#define HEARTBEAT_MIN_PERIOD         300

#define HEARTBEAT_MAX_PERIOD         2000



#endif /* HHEARTBEAT_CONFIG_H_ */
