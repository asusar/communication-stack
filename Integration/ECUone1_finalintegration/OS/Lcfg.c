#include "include/AutoSARConfig.h"
UBaseType_t const volatile Null;
OsResource GlobalRes;


#ifndef TASK_1_EVENT_1
    #define TASK_1_EVENT_1       Null
#endif

#ifndef TASK_1_EVENT_2
    #define TASK_1_EVENT_2       Null
#endif

#ifndef TASK_1_EVENT_3
    #define TASK_1_EVENT_3       Null
#endif

#ifndef TASK_1_EVENT_4
    #define TASK_1_EVENT_4       Null
#endif

#ifndef TASK_1_EVENT_5
    #define TASK_1_EVENT_5       Null
#endif

#ifndef TASK_1_EVENT_6
    #define TASK_1_EVENT_6       Null
#endif

#ifndef TASK_1_RESOURCE_1
    #define TASK_1_RESOURCE_1       Null
#endif

#ifndef TASK_1_RESOURCE_2
    #define TASK_1_RESOURCE_2       Null
#endif

#define _2_RESOURCES_IN_TASK(ExtTaskID) \    
      OsResource * ResourcesInTask_##ExtTaskID[2] = {\ 
                                                                   (OsResource *) &TASK_## ExtTaskID ##_RESOURCE_1, \ 
                                                                   (OsResource *) &TASK_## ExtTaskID ##_RESOURCE_2, \ 
                                                                      };


#define _1_RESOURCES_IN_TASK(ExtTaskID) \    
      OsResource * ResourcesInTask_##ExtTaskID[1] = {\ 
                                                                   (OsResource *) &TASK_## ExtTaskID ##_RESOURCE_1                                                                      };


#define _0_RESOURCES_IN_TASK(ExtTaskID) \ 
         OsResource * ResourcesInTask_##ExtTaskID = (OsResource *) &GlobalRes;

#if NUMBER_OF_RESOURCES > 0 

#ifndef RESOURCE_LINKEDRESOURCE_1
    #define RESOURCE_LINKEDRESOURCE_1   Null
#endif


#ifndef RESOURCE_LINKEDRESOURCE_2
    #define RESOURCE_LINKEDRESOURCE_2   Null
#endif


OsResource ResourceStruct[NUMBER_OF_RESOURCES];

/* Create Resource Handle (ID) for all Resources. The handle can be used to
GetResource, ReleaseResource.*/

UBaseType_t const RESOURCE_NAME_1 = (UBaseType_t) &ResourceStruct[0];

#if NUMBER_OF_RESOURCES >= 2
UBaseType_t const volatile RESOURCE_NAME_2 = (UBaseType_t) &ResourceStruct[1];
#endif

/*************************** Resource struct ******************************************/


OsResource ResourceStruct[NUMBER_OF_RESOURCES] = {
                                     {
                                               .ResourceProperty = RESOURCE_PROPERTY_1,
                                               .LinkedResource = (OsResourceContainer *) &RESOURCE_LINKEDRESOURCE_1,
                                               .CeilingPriority = NULL,
                                               .Availability = TRUE,
                                              },
#if NUMBER_OF_RESOURCES >= 2
                                     {
                                               .ResourceProperty = RESOURCE_PROPERTY_2,
                                               .LinkedResource = (OsResourceContainer *) &RESOURCE_LINKEDRESOURCE_2,
                                               .CeilingPriority = NULL,
                                               .Availability = TRUE,
                                              },
#endif
}; 
 #endif
/* Declaration of ResourcesInTask */
#if NUMBER_OF_EXTENDEDTASK > 0

    #if TASK_1_NUMBER_OF_RES_IN_TASK == 0
        _0_RESOURCES_IN_TASK( 1 );
    #endif
    #if TASK_1_NUMBER_OF_RES_IN_TASK == 1
        _1_RESOURCES_IN_TASK( 1 );
    #endif
#endif
#if NUMBER_OF_EVENTS > 0

/* Create Event Handle (ID) for all Events. The handle can be used to SetEvent, WaitEvent, GetEvent, etc.*/
UBaseType_t const volatile OS_EVENT_NAME_1 = (1 << 0);
#if NUMBER_OF_EVENTS >= 2
UBaseType_t const volatile OS_EVENT_NAME_2 = (1 << 1);
#endif
#if NUMBER_OF_EVENTS >= 3
UBaseType_t const volatile OS_EVENT_NAME_3 = (1 << 2);
#endif
#if NUMBER_OF_EVENTS >= 4
UBaseType_t const volatile OS_EVENT_NAME_4 = (1 << 3);
#endif
#if NUMBER_OF_EVENTS >= 5
UBaseType_t const volatile OS_EVENT_NAME_5 = (1 << 4);
#endif
#if NUMBER_OF_EVENTS >= 6
UBaseType_t const volatile OS_EVENT_NAME_6 = (1 << 5);
#endif

 OsEvent EventStruct[NUMBER_OF_EVENTS] = {
                                {
                                  .Mask = (UBaseType_t) &EventStruct[0],
                                },
#if NUMBER_OF_EVENTS >= 2
                                {
                                  .Mask = (UBaseType_t) &EventStruct[1],
                                },
#endif
#if NUMBER_OF_EVENTS >= 3
                                {
                                  .Mask = (UBaseType_t) &EventStruct[2],
                                },
#endif
#if NUMBER_OF_EVENTS >= 4
                                {
                                  .Mask = (UBaseType_t) &EventStruct[3],
                                },
#endif
#if NUMBER_OF_EVENTS >= 5
                                {
                                  .Mask = (UBaseType_t) &EventStruct[4],
                                },
#endif
#if NUMBER_OF_EVENTS >= 6
                                {
                                  .Mask = (UBaseType_t) &EventStruct[5],
                                },
#endif
};
#endif


#if NUMBER_OF_EVENTS > 0
TaskEventsRef EventsInTask[NUMBER_OF_EXTENDEDTASK] = {
                                {
                                 .event1 = (UBaseType_t) &TASK_1_EVENT_1,
                                 .event2 = (UBaseType_t) &TASK_1_EVENT_2,
                                 .event3 = (UBaseType_t) &TASK_1_EVENT_3,
                                 .event4 = (UBaseType_t) &TASK_1_EVENT_4,
                                 .event5 = (UBaseType_t) &TASK_1_EVENT_5,
                                 .event6 = (UBaseType_t) &TASK_1_EVENT_6,
                                },
};
#endif


/******************************* Task Struct *********************************************/
/* declare Task stack for each task */
static StackType_t IdleStack[IDLETASK_STACK_SIZE];
#if NUMBER_OF_TASKS >= 1
static StackType_t TaskStack1 [OS_TASK_SIZE_1];
#endif



 OsTask TaskStruct[NUMBER_OF_TASKS + 1] = {
                                 {
                                  .StackRef = IdleStack,
                                  .StackSize = IDLETASK_STACK_SIZE,
                                  .TaskCode = (TaskFunction_t) IdleTask,
                                  .Priority = NULL,
                                  .StartingPriority = NULL,
                                  .Activation = 1,
                                  .Schedule = full,
                                  .AutoStart = TRUE,
                                  .TaskType = basic,
                                   },
#if NUMBER_OF_TASKS >= 1
                                      {
                                       .StackRef = TaskStack1,
                                       .StackSize = OS_TASK_SIZE_1,
                                       .TaskCode = (TaskFunction_t) TASK_FUNCTION_NAME(OS_TASK_NAME_1),
                                       .Priority =  OS_TASK_PRIORITY_1,
                                       .StartingPriority = OS_TASK_PRIORITY_1,
                                       .Activation = OS_TASK_ACTIVATION_1,
                                       .Schedule = OS_TASK_SCHEDULE_1,
                                       .AutoStart = OS_TASK_AUTOSTART_1,
                                       .TaskType = OS_TASK_TYPE_1,
                                      },
#endif
};

/* Create Task Handle (ID) for all Tasks. The handle can be used to
ActivateTask, ChainTask, GetTaskState etc.*/

#if NUMBER_OF_TASKS >= 1
TaskType const OS_TASK_NAME_1 = (TaskType) &TaskStruct[1];
#endif
/***************************** Counter Structs ***************************************/

#if NUMBER_OF_COUNTER
OsCounter CounterStruct[NUMBER_OF_COUNTER] = { 
#if NUMBER_OF_COUNTER >= 1
                                        { 
                                          .MaxAllowedValue = OS_COUNTER_MAX_ALLOWED_VALUE_1,
                                          .TicksPerBase = OS_COUNTER_TICKS_PER_BASE_1,
                                          .MinCycle = OS_COUNTER_MIN_CYCLE_1,
                                        },
#endif
};
#endif





 /***************************** Alarm Structs ***************************************/

#if NUMBER_OF_ALARM != 0 
OsAlarm AlarmStruct[NUMBER_OF_ALARM] = { 
                                    {
                                     .pCounterID = (OsCounter *) &CounterStruct[OS_ALARM_COUNTER_REF_1],
                                     .Action = OS_ALARM_ACTION_1,
                                     .TaskID = (UBaseType_t *) &OS_ALARM_ACTION_TASK_REF_1,
#if OS_ALARM_ACTION_1 == SETEVENT
                                     .EventID = (UBaseType_t *) &OS_ALARM_ACTION_EVENT_REF_1,
#endif
                                     .AlarmTime = ALARM_TIME_1 - 1,
                                     .CycleTime = CYCLE_TIME_1,
                                     .AutoStart = AUTOSTART_1,
                                    #if ALARM_CALLBACK
                                     .AlarmCallBackFunc = (AlarmCallBackFunction_t) ALARM_CALLBACK_FUNCTION_1,
                                    #endif
                                    },
#if NUMBER_OF_ALARM >= 2
                                    {
                                     .pCounterID = (OsCounter *) &CounterStruct[OS_ALARM_COUNTER_REF_2],
                                     .Action = OS_ALARM_ACTION_2,
                                     .TaskID = (UBaseType_t *) &OS_ALARM_ACTION_TASK_REF_2,
#if OS_ALARM_ACTION_2 == SETEVENT
                                     .EventID = (UBaseType_t *) &OS_ALARM_ACTION_EVENT_REF_2,
#endif
                                     .AlarmTime = ALARM_TIME_2 - 1,
                                     .CycleTime = CYCLE_TIME_2,
                                     .AutoStart = AUTOSTART_2,
                                    #if ALARM_CALLBACK
                                     .AlarmCallBackFunc = (AlarmCallBackFunction_t) ALARM_CALLBACK_FUNCTION_2,
                                    #endif
                                    },
#endif
#if NUMBER_OF_ALARM >= 3
                                    {
                                     .pCounterID = (OsCounter *) &CounterStruct[OS_ALARM_COUNTER_REF_3],
                                     .Action = OS_ALARM_ACTION_3,
                                     .TaskID = (UBaseType_t *) &OS_ALARM_ACTION_TASK_REF_3,
#if OS_ALARM_ACTION_3 == SETEVENT
                                     .EventID = (UBaseType_t *) &OS_ALARM_ACTION_EVENT_REF_3,
#endif
                                     .AlarmTime = ALARM_TIME_3 - 1,
                                     .CycleTime = CYCLE_TIME_3,
                                     .AutoStart = AUTOSTART_3,
                                    #if ALARM_CALLBACK
                                     .AlarmCallBackFunc = (AlarmCallBackFunction_t) ALARM_CALLBACK_FUNCTION_3,
                                    #endif
                                    },
#endif
#if NUMBER_OF_ALARM >= 4
                                    {
                                     .pCounterID = (OsCounter *) &CounterStruct[OS_ALARM_COUNTER_REF_4],
                                     .Action = OS_ALARM_ACTION_4,
                                     .TaskID = (UBaseType_t *) &OS_ALARM_ACTION_TASK_REF_4,
#if OS_ALARM_ACTION_4 == SETEVENT
                                     .EventID = (UBaseType_t *) &OS_ALARM_ACTION_EVENT_REF_4,
#endif
                                     .AlarmTime = ALARM_TIME_4 - 1,
                                     .CycleTime = CYCLE_TIME_4,
                                     .AutoStart = AUTOSTART_4,
                                    #if ALARM_CALLBACK
                                     .AlarmCallBackFunc = (AlarmCallBackFunction_t) ALARM_CALLBACK_FUNCTION_4,
                                    #endif
                                    },
#endif
#if NUMBER_OF_ALARM >= 5
                                    {
                                     .pCounterID = (OsCounter *) &CounterStruct[OS_ALARM_COUNTER_REF_5],
                                     .Action = OS_ALARM_ACTION_5,
                                     .TaskID = (UBaseType_t *) &OS_ALARM_ACTION_TASK_REF_5,
#if OS_ALARM_ACTION_5 == SETEVENT
                                     .EventID = (UBaseType_t *) &OS_ALARM_ACTION_EVENT_REF_5,
#endif
                                     .AlarmTime = ALARM_TIME_5 - 1,
                                     .CycleTime = CYCLE_TIME_5,
                                     .AutoStart = AUTOSTART_5,
                                    #if ALARM_CALLBACK
                                     .AlarmCallBackFunc = (AlarmCallBackFunction_t) ALARM_CALLBACK_FUNCTION_5,
                                    #endif
                                    },
#endif
#if NUMBER_OF_ALARM >= 6
                                    {
                                     .pCounterID = (OsCounter *) &CounterStruct[OS_ALARM_COUNTER_REF_6],
                                     .Action = OS_ALARM_ACTION_6,
                                     .TaskID = (UBaseType_t *) &OS_ALARM_ACTION_TASK_REF_6,
#if OS_ALARM_ACTION_6 == SETEVENT
                                     .EventID = (UBaseType_t *) &OS_ALARM_ACTION_EVENT_REF_6,
#endif
                                     .AlarmTime = ALARM_TIME_6 - 1,
                                     .CycleTime = CYCLE_TIME_6,
                                     .AutoStart = AUTOSTART_6,
                                    #if ALARM_CALLBACK
                                     .AlarmCallBackFunc = (AlarmCallBackFunction_t) ALARM_CALLBACK_FUNCTION_6,
                                    #endif
                                    },
#endif
};
#endif


#if NUMBER_OF_ALARM >= 1
AlarmType const OS_ALARM_NAME_1 = (AlarmType) &AlarmStruct[0];
#endif
#if NUMBER_OF_ALARM >= 2
AlarmType const OS_ALARM_NAME_2 = (AlarmType) &AlarmStruct[1];
#endif
#if NUMBER_OF_ALARM >= 3
AlarmType const OS_ALARM_NAME_3 = (AlarmType) &AlarmStruct[2];
#endif
#if NUMBER_OF_ALARM >= 4
AlarmType const OS_ALARM_NAME_4 = (AlarmType) &AlarmStruct[3];
#endif
#if NUMBER_OF_ALARM >= 5
AlarmType const OS_ALARM_NAME_5 = (AlarmType) &AlarmStruct[4];
#endif
#if NUMBER_OF_ALARM >= 6
AlarmType const OS_ALARM_NAME_6 = (AlarmType) &AlarmStruct[5];
#endif
