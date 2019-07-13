/*
 * wr.task.h
 *
 *  Created on: Dec 12, 2017
 *      Author: Dell
 */

#ifndef WR_TASK_H_
#define WR_TASK_H_

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/list.h"
#include "freertos/projdefs.h"
#include "freertos/StackMacros.h"
#include "portable/portmacro.h"
#include "Std_Types.h"

typedef enum {
   RUNNING,
   WAITING,
   READY,
   SUSPENDED,
   MAX_TASKSTATETYPE
}TaskStateType;

//#define E_OK              0
#define E_OS_ACCESS       1
#define E_OS_CALLEVEL     2
#define E_OS_ID           3
#define E_OS_LIMIT        4
#define E_OS_NOFUNC       5
#define E_OS_RESOURCE     6
#define E_OS_STATE        7
#define E_OS_VALUE        8


#define StatusType UBaseType_t



typedef void * TaskHandle_t;

typedef UBaseType_t  AppModeType;
typedef UBaseType_t TaskType;
typedef UBaseType_t PriorityType;
typedef UBaseType_t *TaskRefType;
typedef TaskStateType *TaskStateRefType;


#define OSDEFAULTAPPMODE    (UBaseType_t) 0U

#define SystemCounter                       1
#define SystemCounter_TICKSPERBASE        configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ

#define DeclareTask(TaskID) extern TaskType const TaskID;


#define TASK(TaskNameID)    void INTERNAL_OS_##TaskNameID (void);       \
                            void OS_##TaskNameID (void)                 \
                            {                                           \
                                for(;;)                                 \
                                {                                       \
                                    INTERNAL_OS_##TaskNameID();         \
                                }                                       \
                            }                                           \
                            void INTERNAL_OS_##TaskNameID (void)



//typedef enum { False , True } boolean;
typedef enum { NON_PREEMPTIONTASK, FULL_PREEMPTIONTASK } PreemtionType;

void InitTask (void);



/*-----------------------------------------------------------
 * SCHEDULER INTERNALS AVAILABLE FOR PORTING PURPOSES
 *----------------------------------------------------------*/

/*
 * THIS FUNCTION MUST NOT BE USED FROM APPLICATION CODE.  IT IS ONLY
 * INTENDED FOR USE WHEN IMPLEMENTING A PORT OF THE SCHEDULER AND IS
 * AN INTERFACE WHICH IS FOR THE EXCLUSIVE USE OF THE SCHEDULER.
 *
 * Called from the real time kernel tick (either preemptive or cooperative),
 * this increments the tick count and checks if any tasks that are blocked
 * for a finite period required removing from a blocked list and placing on
 * a ready list.  If a non-zero value is returned then a context switch is
 * required because either:
 *   + A task was removed from a blocked list because its timeout had expired,
 *     or
 *   + Time slicing is in use and there is a task of equal priority to the
 *     currently running task.
 */
BaseType_t xTaskIncrementTick( void );

/*
 * THIS FUNCTION MUST NOT BE USED FROM APPLICATION CODE.  IT IS ONLY
 * INTENDED FOR USE WHEN IMPLEMENTING A PORT OF THE SCHEDULER AND IS
 * AN INTERFACE WHICH IS FOR THE EXCLUSIVE USE OF THE SCHEDULER.
 *
 * Sets the pointer to the current TCB to the TCB of the highest priority task
 * that is ready to run.
 */
void vTaskSwitchContext( void );

StatusType ActivateTask (TaskType TaskID);
StatusType ChainTask (TaskType TaskID);
StatusType TerminateTask (void);
StatusType GetTaskID ( TaskRefType TaskID );
StatusType GetTaskState ( TaskType TaskID, TaskStateRefType State );

void StartOS (AppModeType Mode);

/*************** ALARM Buffers ***********************/

#if NOALARM >= 1
StaticTimer_t AlarmBuffer1;
#endif
#if NOALARM >= 2
StaticTimer_t AlarmBuffer2;
#endif
#if NOALARM >= 3
StaticTimer_t AlarmBuffer3;
#endif
#if NOALARM >= 4
StaticTimer_t AlarmBuffer4;
#endif
#if NOALARM >= 5
StaticTimer_t AlarmBuffer5;
#endif
#if NOALARM >= 6
StaticTimer_t AlarmBuffer6;
#endif
#if NOALARM >= 7
StaticTimer_t AlarmBuffer7;
#endif
#if NOALARM >= 8
StaticTimer_t AlarmBuffer8;
#endif
#if NOALARM >= 9
StaticTimer_t AlarmBuffer9;
#endif
#if NOALARM >= 10
StaticTimer_t AlarmBuffer10;
#endif

#endif /* WR_TASK_H_ */
