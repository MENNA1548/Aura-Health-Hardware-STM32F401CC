//#ifndef MSTP_INTERFACE_H_
//#define MSTP_INTERFACE_H_
//
//#include "Std_type.h"
//
///* APIs */
//
//void MSTP_voidInit(void);
//
//void MSTP_voidSendByte(u8 Copy_u8Data);
//
//void MSTP_voidSendArray(u8 *Copy_pu8Data, u8 Copy_u8Size);
//
//void MSTP_voidClear(void);
//
//#endif
#ifndef HSTP_INTERFACE_H_
#define HSTP_INTERFACE_H_


#include "Std_type.h"


void HSTP_voidInit(void);


void HSTP_voidSendByte(u8 Copy_u8Data);


void HSTP_voidSendArray(u8 *Copy_pu8Data,u8 Copy_u8Size);


void HSTP_voidClear(void);


#endif
