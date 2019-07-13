/*
 * AutoSARConfig.h
 *
 *  Created on: Jan 26, 2018
 *      Author: Dell
 */

#ifndef AUTOSARCONFIG_H_
#define AUTOSARCONFIG_H_

#include "task.h"
#include "alarm.h"
#include "Config.h"


#define NUMBER_OF_TASKS          (NUMBER_OF_BASICTASK + NUMBER_OF_EXTENDEDTASK)

/* Put 'OS_' before Task function name that required two level of indirection */
#define PASTER(x,y) x ## _ ## y
#define TASK_FUNCTION_NAME(TaskName)   PASTER(OS, TaskName)

/******************** General Configuration ************************/


#define MAX_PRIORITY             5
#define MAX_NUMBER_OF_TASKS      15
#define MAX_EVENTS_FOR_TASK      8

/*************************************************************/
#define DeclareResource(ResID) extern UBaseType_t const ResID;
#define standard        0
#define LINKED          1
#define INTERNAL        2

#define ACTIVATETASK    0
#define SETEVENT        1
#define ALARMCALLBACK   2
#ifndef TRUE
    #define TRUE        1
#endif
#ifndef FALSE
    #define FALSE       2
#endif
/************** Extern Task Function from user ***************/

#ifndef basic
#define basic 0
#endif
#ifndef extended
#define extended 1
#endif

#ifndef non
#define non 0
#endif
#ifndef full
#define full 1
#endif



/* we need to extern the Task function from main to point to it in their own TCB */

extern void IdleTask(void);
#if NUMBER_OF_TASKS >= 1
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_1)(void);
#endif
#if NUMBER_OF_TASKS >= 2
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_2)(void);
#endif
#if NUMBER_OF_TASKS >= 3
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_3)(void);
#endif
#if NUMBER_OF_TASKS >= 4
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_4)(void);
#endif
#if NUMBER_OF_TASKS >= 5
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_5)(void);
#endif
#if NUMBER_OF_TASKS >= 6
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_6)(void);
#endif
#if NUMBER_OF_TASKS >= 7
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_7)(void);
#endif
#if NUMBER_OF_TASKS >= 8
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_8)(void);
#endif
#if NUMBER_OF_TASKS >= 9
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_9)(void);
#endif
#if NUMBER_OF_TASKS >= 10
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_10)(void);
#endif
#if NUMBER_OF_TASKS >= 11
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_11)(void);
#endif
#if NUMBER_OF_TASKS >= 12
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_12)(void);
#endif
#if NUMBER_OF_TASKS >= 13
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_13)(void);
#endif
#if NUMBER_OF_TASKS >= 14
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_14)(void);
#endif
#if NUMBER_OF_TASKS >= 15
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_15)(void);
#endif
#if NUMBER_OF_TASKS >= 16
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_16)(void);
#endif
#if NUMBER_OF_TASKS >= 17
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_17)(void);
#endif
#if NUMBER_OF_TASKS >= 18
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_18)(void);
#endif
#if NUMBER_OF_TASKS >= 19
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_19)(void);
#endif
#if NUMBER_OF_TASKS >= 20
    extern void TASK_FUNCTION_NAME(OS_TASK_NAME_20)(void);
#endif

#if ALARM_CALLBACK
#if NUMBER_OF_CALLBACK_FUNCTION >= 1
    extern void ALARM_CALLBACK_FUNCTION_1 (void);
#endif
#if NUMBER_OF_CALLBACK_FUNCTION >= 2
    extern void ALARM_CALLBACK_FUNCTION_2 (void);
#endif
#if NUMBER_OF_CALLBACK_FUNCTION >= 3
    extern void ALARM_CALLBACK_FUNCTION_3 (void);
#endif
#if NUMBER_OF_CALLBACK_FUNCTION >= 4
    extern void ALARM_CALLBACK_FUNCTION_4 (void);
#endif
#if NUMBER_OF_CALLBACK_FUNCTION >= 5
    extern void ALARM_CALLBACK_FUNCTION_5 (void);
#endif
#if NUMBER_OF_CALLBACK_FUNCTION >= 6
    extern void ALARM_CALLBACK_FUNCTION_6 (void);
#endif
#if NUMBER_OF_CALLBACK_FUNCTION >= 7
    extern void ALARM_CALLBACK_FUNCTION_7 (void);
#endif
#if NUMBER_OF_CALLBACK_FUNCTION >= 8
    extern void ALARM_CALLBACK_FUNCTION_8 (void);
#endif
#if NUMBER_OF_CALLBACK_FUNCTION >= 9
    extern void ALARM_CALLBACK_FUNCTION_9 (void);
#endif
#if NUMBER_OF_CALLBACK_FUNCTION >= 10
    extern void ALARM_CALLBACK_FUNCTION_10 (void);
#endif
#endif


/********************* Typedef SECTION ***********************/

typedef void (*AlarmCallBackFunction_t)( void * );


/********************** OS Containers ************************/

typedef struct OsResourceContainer {
    uint16_t ResourceProperty;                              /* ResourceProperty: STANDARD, LINKED or INTERNAL */
    uint16_t Availability;                                  /* Availability: TRUE or FALSE */
    UBaseType_t CeilingPriority;                            /* Priority Ceiling Protocol */
    struct OsResourceContainer * LinkedResource;
}OsResource;

typedef OsResource  OsResourceContainer;

typedef struct OsEventContainer {
    UBaseType_t Mask;
}OsEvent;

typedef struct TaskEventsContainer {
    UBaseType_t             event1;
    UBaseType_t             event2;
    UBaseType_t             event3;
    UBaseType_t             event4;
    UBaseType_t             event5;
    UBaseType_t             event6;
    UBaseType_t             event7;
    UBaseType_t             event8;
}TaskEventsRef;

typedef struct OsTaskContainer {
    volatile StackType_t    *TopOfStack;    /*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */
    ListItem_t              StateListItem;  /*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
    StackType_t             *StackRef;      /*< Points to the start of the stack. */
    StackType_t             StackSize;      /*< Declare the task size that has been configured */
    TaskFunction_t          TaskCode;
    #if ( portSTACK_GROWTH > 0 )
        StackType_t     *pxEndOfStack;      /*< Points to the end of the stack on architectures where the stack grows up from low memory. */
    #endif
    UBaseType_t             Activation;
    UBaseType_t             Priority;       /*< The current priority of the task. the current priority may differ from the Base priority, when the task occupies the resources (Priority Ceiling Protocol).*/
    UBaseType_t             const StartingPriority; /*< The base priority of the task.  0 is the lowest priority. */
    TaskHandle_t            TaskHandle;
    #if NUMBER_OF_EVENTS
    TaskEventsRef           const *EventsRel;
    UBaseType_t             EventSet;
    UBaseType_t             EventWait;
    #endif
    #if NUMBER_OF_RESOURCES
    UBaseType_t             const *ResourcesRel;    /*< Points to the Resources which has the authority to access */
    UBaseType_t             NumberOfResources;
    OsResource              *ResRequired;
    #endif
    UBaseType_t             Schedule;
    uint8_t                 AutoStart;
    UBaseType_t             TaskType;
    volatile uint8_t        TaskRequest;
    uint8_t                 TaskActivation;
}OsTask;

typedef OsTask TCB_t;


/*********************** Counter Containers ******************************/

typedef struct OsCounterContainer
{
    volatile UBaseType_t         CountValue;                  /* Count Value */
    volatile UBaseType_t         TickValue;
    UBaseType_t                  TicksPerBase;                /* TICKSPERBASE */
    UBaseType_t                  MaxAllowedValue;             /* MAXALLOWEDVALUE */
    UBaseType_t                  MinCycle;
    ListItem_t                   CounterListItem;
    List_t                       AlarmList;
}OsCounter;

typedef struct OsAlarmContainer
{
    volatile UBaseType_t            LocalNextAlarmTime;
    OsCounter                       *pCounterID;            /* Pointer to Alarm's Counter */
    ListItem_t                      TimerListItem;
    #if ALARM_CALLBACK
    AlarmCallBackFunction_t         AlarmCallBackFunc;
    #endif
    UBaseType_t                     *TaskID;
    UBaseType_t                     *EventID;
    UBaseType_t                     AlarmTime;             /* Number of Cycles */
    UBaseType_t                     CycleTime;             /* Time of one Cycle */
    uint16_t                        AutoStart;              /* AutoStart */
    uint16_t                        Action;

}OsAlarm;


#endif /* AUTOSARCONFIG_H_ */
