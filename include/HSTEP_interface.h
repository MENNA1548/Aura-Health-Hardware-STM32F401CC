#ifndef HSTEP_INTERFACE_H
#define HSTEP_INTERFACE_H

#include "Std_type.h"


/********************************************************/
/* Initialization                                       */
/********************************************************/

void HSTEP_voidInit(void);


/********************************************************/
/* Step Processing                                      */
/********************************************************/

void HSTEP_voidUpdate(void);


/********************************************************/
/* Step Information                                     */
/********************************************************/

u32 HSTEP_u32GetSteps(void);

float HSTEP_f32GetDistance(void);

float HSTEP_f32GetCalories(void);


/********************************************************/
/* Activity Information                                 */
/********************************************************/

u8 HSTEP_u8GetActivity(void);


/********************************************************/
/* Reset                                                */
/********************************************************/

void HSTEP_voidReset(void);


#endif
