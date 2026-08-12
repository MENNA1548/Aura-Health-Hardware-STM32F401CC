//#ifndef SEVENSEG_CONFIG_H_
//#define SEVENSEG_CONFIG_H_
//
///* Port used for all segments */
//#define SEVENSEG_PORT   PORTB
//
///* Pin mapping: change these if your wiring differs */
//#define SEVENSEG_PIN_A  PIN0
//#define SEVENSEG_PIN_B  PIN1
//#define SEVENSEG_PIN_C  PIN2
//#define SEVENSEG_PIN_D  PIN3
//#define SEVENSEG_PIN_E  PIN4
//#define SEVENSEG_PIN_F  PIN5
//#define SEVENSEG_PIN_G  PIN6
//
//#endif /* SEVENSEG_CONFIG_H_ */
//
#ifndef SEVENSEG_CONFIG_H_
#define SEVENSEG_CONFIG_H_

/******************************************************
 * 7-SEGMENT 1
 *
 * A  -> PB0
 * B  -> PB1
 * C  -> PB2
 * D  -> PB3
 * E  -> PB4
 * F  -> PB5
 * G  -> PB6
 * DP -> PB7
 *
 * COM -> GND
 ******************************************************/

#define SEVENSEG1_PORT       PORTB

#define SEVENSEG1_PIN_A      PIN0
#define SEVENSEG1_PIN_B      PIN1
#define SEVENSEG1_PIN_C      PIN2
#define SEVENSEG1_PIN_D      PIN3
#define SEVENSEG1_PIN_E      PIN4
#define SEVENSEG1_PIN_F      PIN5
#define SEVENSEG1_PIN_G      PIN6
#define SEVENSEG1_PIN_DP     PIN7


/******************************************************
 * 7-SEGMENT 2
 *
 * A  -> PB8
 * B  -> PB9
 * C  -> PB10
 * D  -> PB11
 * E  -> PB12
 * F  -> PB13
 * G  -> PB14
 * DP -> PB15
 *
 * COM -> GND
 ******************************************************/

#define SEVENSEG2_PORT       PORTB

#define SEVENSEG2_PIN_A      PIN8
#define SEVENSEG2_PIN_B      PIN9
#define SEVENSEG2_PIN_C      PIN10
#define SEVENSEG2_PIN_D      PIN11
#define SEVENSEG2_PIN_E      PIN12
#define SEVENSEG2_PIN_F      PIN13
#define SEVENSEG2_PIN_G      PIN14
#define SEVENSEG2_PIN_DP     PIN15

#endif
