//#ifndef SEVENSEG_INTERFACE_H_
//#define SEVENSEG_INTERFACE_H_
//
//#include "Std_type.h"
//#include <stdint.h>
//
///* Initializes all segment pins as outputs */
//void SevenSeg_voidInit(void);
//
///* Displays a digit 0-9 on the display */
//void SevenSeg_voidDisplayDigit(uint8_t Copy_Digit);
//
///* Turns all segments off */
//void SevenSeg_voidOff(void);
//
///* Turns all segments on (lamp test) */
//void SevenSeg_voidAllOn(void);
//
//#endif /* SEVENSEG_INTERFACE_H_ */
#ifndef SEVENSEG_INTERFACE_H_
#define SEVENSEG_INTERFACE_H_

#include "Std_type.h"
#include <stdint.h>


/* Initialize both 7-segment displays */
void SevenSeg_voidInit(void);


/* Display one digit on 7-segment 1 */
void SevenSeg_voidDisplayDigit1(
        uint8_t Copy_Digit);


/* Display one digit on 7-segment 2 */
void SevenSeg_voidDisplayDigit2(
        uint8_t Copy_Digit);


/* Display two-digit number
 *
 * Example:
 * 72 -> Display 1 = 7
 *      Display 2 = 2
 */
void SevenSeg_voidDisplayNumber(
        uint8_t Copy_Number);


/* Turn both displays OFF */
void SevenSeg_voidOff(void);


/* Turn all segments ON */
void SevenSeg_voidAllOn(void);

#endif
