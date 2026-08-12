/**************************************************************
 * File Name : MOS_Private.h
 * Author    : Your Name
 * Layer     : OS
 *************************************************************/

#ifndef MOS_PRIVATE_H_
#define MOS_PRIVATE_H_
#include "Std_type.h"
/*=========================================================
                Configuration
=========================================================*/

#define MAX_TASKS          10

#define TASK_READY         0
#define TASK_RUNNING       1
#define TASK_WAITING       2
#define TASK_SUSPENDED     3

/*=========================================================
                Stack Configuration
=========================================================*/

#define STACK_SIZE         256U

/*=========================================================
                SysTick Registers
=========================================================*/

#define STK_BASE_ADDRESS   0xE000E010UL

typedef struct
{
    volatile u32 CTRL;
    volatile u32 LOAD;
    volatile u32 VAL;
    volatile u32 CALIB;

}STK_t;

#define STK    ((volatile STK_t *)STK_BASE_ADDRESS)

/*=========================================================
                SCB Registers
=========================================================*/

#define SCB_ICSR      (*(volatile u32 *)0xE000ED04UL)

#define SCB_SHPR3     (*(volatile u32 *)0xE000ED20UL)

#define SCB_INTCTRL_PENDSVSET      (1UL<<28)

/*=========================================================
                Internal Scheduler States
=========================================================*/

#define OS_STOPPED      0
#define OS_RUNNING      1

/*=========================================================
                Internal Functions
=========================================================*/

static void OS_voidScheduler(void);
static void OS_voidContextSwitch(void);

#endif
