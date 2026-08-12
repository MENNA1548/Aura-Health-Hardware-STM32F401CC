/**************************************************************
 * File Name : MOS_Interface.h
 * Author    : Your Name
 * Layer     : OS
 *************************************************************/

#ifndef MOS_INTERFACE_H_
#define MOS_INTERFACE_H_

#include "Std_type.h"

/*=========================================================
                Task State
=========================================================*/
typedef enum
{
    TASK_READY = 0,
    TASK_RUNNING,
    TASK_WAITING,
    TASK_SUSPENDED

}TaskState_t;

/*=========================================================
                Task Control Block (TCB)
=========================================================*/
typedef struct
{
    void (*TaskHandler)(void);

    u32 Periodicity;

    u32 FirstDelay;

    TaskState_t State;

}Task_t;

/*=========================================================
                Function Prototypes
=========================================================*/

/* Initialize OS */
void MOS_voidInit(void);

/* Start Scheduler */
void MOS_voidStart(void);

/* Create New Task */
void MOS_voidCreateTask
(
        u8 Copy_u8Priority,
        u32 Copy_u32Periodicity,
        void (*Copy_pvTaskCode)(void),
        u32 Copy_u32FirstDelay
);

/* Suspend Task */
void MOS_voidSuspendTask(u8 Copy_u8Priority);

/* Resume Task */
void MOS_voidResumeTask(u8 Copy_u8Priority);

/* Delete Task */
void MOS_voidDeleteTask(u8 Copy_u8Priority);

#endif
