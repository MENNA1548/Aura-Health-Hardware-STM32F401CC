/**************************************************************
 * File Name : MOS_Program.c
 * Author    : Your Name
 * Layer     : OS
 *************************************************************/

#include "Std_type.h"

#include "MOS_Interface.h"
#include "MOS_Private.h"
#include "MOS_Config.h"

#include "MSTK_Interface.h"

/*=========================================================
                Global Variables
=========================================================*/

static Task_t OS_Tasks[MAX_TASKS];

/*=========================================================
                Scheduler
=========================================================*/

static void OS_voidScheduler(void)
{
    u8 Local_u8Task;

    for(Local_u8Task = 0 ; Local_u8Task < MAX_TASKS ; Local_u8Task++)
    {
        if(OS_Tasks[Local_u8Task].State == TASK_READY)
        {
            if(OS_Tasks[Local_u8Task].FirstDelay == 0)
            {
                OS_Tasks[Local_u8Task].TaskHandler();

                OS_Tasks[Local_u8Task].FirstDelay =
                        OS_Tasks[Local_u8Task].Periodicity - 1;
            }
            else
            {
                OS_Tasks[Local_u8Task].FirstDelay--;
            }
        }
    }
}

/*=========================================================
                Initialize OS
=========================================================*/

void MOS_voidInit(void)
{
    u8 Local_u8Task;

    for(Local_u8Task=0 ; Local_u8Task<MAX_TASKS ; Local_u8Task++)
    {
        OS_Tasks[Local_u8Task].TaskHandler = 0;

        OS_Tasks[Local_u8Task].Periodicity = 0;

        OS_Tasks[Local_u8Task].FirstDelay = 0;

        OS_Tasks[Local_u8Task].State = TASK_SUSPENDED;
    }

    MSTK_voidInit();
}

/*=========================================================
                Start Scheduler
=========================================================*/

void MOS_voidStart(void)
{
    MSTK_voidSetIntervalPeriodic(1000,OS_voidScheduler);
}

/*=========================================================
                Create Task
=========================================================*/

void MOS_voidCreateTask
(
        u8 Copy_u8Priority,
        u32 Copy_u32Periodicity,
        void (*Copy_pvTaskCode)(void),
        u32 Copy_u32FirstDelay
)
{
    OS_Tasks[Copy_u8Priority].TaskHandler
            = Copy_pvTaskCode;

    OS_Tasks[Copy_u8Priority].Periodicity
            = Copy_u32Periodicity;

    OS_Tasks[Copy_u8Priority].FirstDelay
            = Copy_u32FirstDelay;

    OS_Tasks[Copy_u8Priority].State
            = TASK_READY;
}

/*=========================================================
                Suspend Task
=========================================================*/

void MOS_voidSuspendTask(u8 Copy_u8Priority)
{
    OS_Tasks[Copy_u8Priority].State
            = TASK_SUSPENDED;
}

/*=========================================================
                Resume Task
=========================================================*/

void MOS_voidResumeTask(u8 Copy_u8Priority)
{
    OS_Tasks[Copy_u8Priority].State
            = TASK_READY;
}

/*=========================================================
                Delete Task
=========================================================*/

void MOS_voidDeleteTask(u8 Copy_u8Priority)
{
    OS_Tasks[Copy_u8Priority].TaskHandler = 0;

    OS_Tasks[Copy_u8Priority].Periodicity = 0;

    OS_Tasks[Copy_u8Priority].FirstDelay = 0;

    OS_Tasks[Copy_u8Priority].State = TASK_SUSPENDED;
}
