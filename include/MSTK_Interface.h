#ifndef MSTK_INTERFACE_H
#define MSTK_INTERFACE_H

#define MSTK_AHB          0
#define MSTK_AHB_DIV_8    1

void MSTK_voidInit(void);
void MSTK_voidStart(u32 Copy_u32LoadValue);
void MSTK_voidStop(void);

u32 MSTK_u32GetElapsedTime(void);
u32 MSTK_u32GetRemainingTime(void);
void MSTK_voidSetBusyWait(u32 Copy_u32Ticks);
#endif
