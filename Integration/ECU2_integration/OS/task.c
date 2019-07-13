/*
 * wr.task.c
 *
 *  Created on: Dec 12, 2017
 *      Author: Dell
 */


#include "include/task.h"
#include "include/alarm.h"
#include "include/resource.h"
#include "include/AutoSARConfig.h"
#include "portable/portmacro.h"
#include <stdlib.h>
#include <string.h>


#define tskSTACK_FILL_BYTE  ( 0xa5U )
#define IDLETASK_ID              0
#define IDLETASK_PRIORITY        0

//extern TCB_t * pxCurrentTCB;

extern OsTask TaskStruct[NUMBER_OF_TASKS];

#if NUMBER_OF_EVENTS > 0
    extern TaskEventsRef EventsInTask[NUMBER_OF_EXTENDEDTASK];
#endif

/*
#if NUMBER_OF_EXTENDEDTASK > 0
    extern UBaseType_t ResourcesInTask_1[];
#if NUMBER_OF_EXTENDEDTASK >=2
    extern UBaseType_t ResourcesInTask_2[];
#endif
#if NUMBER_OF_EXTENDEDTASK >=3
    extern UBaseType_t ResourcesInTask_3[];
#endif

#if NUMBER_OF_EXTENDEDTASK >=4
    extern UBaseType_t ResourcesInTask_4[];
#endif

#if NUMBER_OF_EXTENDEDTASK >=5
    extern UBaseType_t ResourcesInTask_5[];
#endif

#if NUMBER_OF_EXTENDEDTASK >=6
    extern UBaseType_t ResourcesInTask_6[];
#endif

#if NUMBER_OF_EXTENDEDTASK >=7
    extern UBaseType_t ResourcesInTask_7[];
#endif

#if NUMBER_OF_EXTENDEDTASK >=8
    extern UBaseType_t ResourcesInTask_8[];
#endif
#endif
*/
OsTask * volatile pxCurrentTCB = NULL;

/* Lists for ready and blocked tasks. --------------------*/
static List_t ReadyTasksLists[ MAX_PRIORITY ];         /*< Prioritised ready tasks. */
static List_t DelayedTaskList1;                          /*< Delayed tasks. */
static List_t DelayedTaskList2;                          /*< Delayed tasks (two lists are used - one for delays that have overflowed the current tick count. */
static List_t * volatile pDelayedTaskList;                /*< Points to the delayed task list currently being used. */
static List_t * volatile pOverflowDelayedTaskList;        /*< Points to the delayed task list currently being used to hold tasks that have overflowed the current tick count. */
static List_t SuspendedTaskList;                        /*< Tasks that are currently suspended. */

/* Other file private variables. --------------------------------*/
static volatile UBaseType_t CurrentNumberOfTasks    = ( UBaseType_t ) 0U;
static volatile TickType_t TickCount                = ( TickType_t ) 0U;
static volatile UBaseType_t TopReadyPriority        = IDLETASK_PRIORITY;
static volatile BaseType_t SchedulerRunning         = pdFALSE;
static volatile UBaseType_t PendedTicks             = ( UBaseType_t ) 0U;
static volatile BaseType_t YieldPending             = pdFALSE;
static volatile BaseType_t NumOfOverflows           = ( BaseType_t ) 0;
static UBaseType_t TaskNumber                       = ( UBaseType_t ) 0U;
static volatile TickType_t NextTaskUnblockTime      = ( TickType_t ) 0U;    /* Initialised to portMAX_DELAY before the scheduler starts. */
static volatile UBaseType_t SchedulerSuspended      = ( UBaseType_t ) pdFALSE;
static volatile UBaseType_t ExtendedTaskCount       = ( UBaseType_t ) 0U;

#if NUMBER_OF_COUNTER
extern void CounterIncrementHook ( void );
#endif
#if NUMBER_OF_ALARM
extern void AlarmHook ( BaseType_t * SwitchRequired );
#endif

void IdleTask(void)
{
    for(;;)
    {

    }
}

static void InitialiseTaskLists( void )
{
UBaseType_t uxPriority;

    for( uxPriority = ( UBaseType_t ) 0U; uxPriority < ( UBaseType_t ) MAX_PRIORITY; uxPriority++ )
    {
        vListInitialise( &( ReadyTasksLists[ uxPriority ] ) );
    }

    vListInitialise( &DelayedTaskList1 );
    vListInitialise( &DelayedTaskList2 );
    vListInitialise( &SuspendedTaskList );

    /* Start with DelayedTaskList using list1 and the OverflowDelayedTaskList
    using list2. */
    pDelayedTaskList = &DelayedTaskList1;
    pOverflowDelayedTaskList = &DelayedTaskList2;
}

static void TaskRegistration( OsTask *pxNewTCB )
{
    CurrentNumberOfTasks++;
    if( pxCurrentTCB == NULL )
    {
        /* There are no other tasks, or all the other tasks are in
        the suspended state - make this the current task. */
        pxCurrentTCB = pxNewTCB;

        if( CurrentNumberOfTasks == ( UBaseType_t ) 1 )
        {
            /* This is the first task to be created so do the preliminary
            initialisation required.  We will not recover if this call
            fails, but we will report the failure. */
            InitialiseTaskLists();
        }
        else
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    else
    {
        if ( pxNewTCB->AutoStart != FALSE )
        {
            /* Make this task the current task if it is the highest
            priority task to be created so far. */
            if( pxCurrentTCB->Priority <= pxNewTCB->Priority )
            {
                pxCurrentTCB = pxNewTCB;
            }
            else
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        else
        {

        }
    }
    TaskNumber++;
}


static void InitialiseNewTask ( UBaseType_t TaskID )
{
    OsTask *NewTCB;
    UBaseType_t *pAccessRes;
    UBaseType_t *ppRes;
    OsResource *pResInResourceStruct;
    StackType_t *pxTopOfStack;
    UBaseType_t x;
    NewTCB = &TaskStruct[TaskID];

    /* Avoid dependency on memset() if it is not required. */
    #if( ( configCHECK_FOR_STACK_OVERFLOW > 1 ) || ( configUSE_TRACE_FACILITY == 1 ) || ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) )
    {
        /* Fill the stack with a known value to assist debugging. */
        ( void ) memset( NewTCB->StackRef, ( int ) tskSTACK_FILL_BYTE, ( size_t ) (NewTCB->StackSize) * sizeof( StackType_t ) );
    }
    #endif /* ( ( configCHECK_FOR_STACK_OVERFLOW > 1 ) || ( ( configUSE_TRACE_FACILITY == 1 ) || ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) ) ) */

    /* Calculate the top of stack address.  This depends on whether the stack
    grows from high memory to low (as per the 80x86) or vice versa.
    portSTACK_GROWTH is used to make the result positive or negative as required
    by the port. */
    #if( portSTACK_GROWTH < 0 )
    {
        pxTopOfStack = NewTCB->StackRef + ( (NewTCB->StackSize) - ( uint32_t ) 1 );
        pxTopOfStack = ( StackType_t * ) ( ( ( portPOINTER_SIZE_TYPE ) pxTopOfStack ) & ( ~( ( portPOINTER_SIZE_TYPE ) portBYTE_ALIGNMENT_MASK ) ) ); /*lint !e923 MISRA exception.  Avoiding casts between pointers and integers is not practical.  Size differences accounted for using portPOINTER_SIZE_TYPE type. */
    }
    #else /* portSTACK_GROWTH */
    {
        pxTopOfStack = NewTCB->StackRef;

        /* Check the alignment of the stack buffer is correct. */
        configASSERT( ( ( ( portPOINTER_SIZE_TYPE ) NewTCB->StackRef & ( portPOINTER_SIZE_TYPE ) portBYTE_ALIGNMENT_MASK ) == 0UL ) );

        /* The other extreme of the stack space is required if stack checking is
        performed. */
        NewTCB->pxEndOfStack = NewTCB->StackRef + ( (NewTCB->StackSize) - ( uint32_t ) 1 );
    }
    #endif /* portSTACK_GROWTH */

    #if( NUMBER_OF_EXTENDEDTASK > 0)
    if ( NewTCB->TaskType == extended )
    {
        ExtendedTaskCount++;

        #if (NUMBER_OF_EVENTS > 0)
        NewTCB->EventsRel = &EventsInTask[ExtendedTaskCount-1];
        NewTCB->EventSet = NULL;
        NewTCB->EventWait = NULL;
        #endif /* NUMBER_OF_EVENTS */

        #if (NUMBER_OF_RESOURCES > 0)
        if(ExtendedTaskCount == 1)
        {
            /* The extern ResourcesInTask_1 exists in resource.h  */
            NewTCB->ResourcesRel = ResourcesInTask_1;
            NewTCB->NumberOfResources = sizeof(ResourcesInTask_1)/sizeof(ResourcesInTask_1[0]);
        }

                                                                            /* Edit:: it prefare to be like for loop , array of ResourcesInTask  */
        #if (NUMBER_OF_EXTENDEDTASK >= 2)
        else if (ExtendedTaskCount == 2)
        {
            NewTCB->ResourcesRel = ResourcesInTask_2;
            NewTCB->NumberOfResources = sizeof(ResourcesInTask_2)/sizeof(ResourcesInTask_2[0]);
        }
        #endif
        #if (NUMBER_OF_EXTENDEDTASK >= 3)
        else if (ExtendedTaskCount == 3)
        {
            NewTCB->ResourcesRel = ResourcesInTask_3;
            NewTCB->NumberOfResources = sizeof(ResourcesInTask_3)/sizeof(ResourcesInTask_3[0]);
        }
        #endif
        #if (NUMBER_OF_EXTENDEDTASK >= 4)
        else if (ExtendedTaskCount == 4)
        {
            NewTCB->ResourcesRel = ResourcesInTask_4;
            NewTCB->NumberOfResources = sizeof(ResourcesInTask_4)/sizeof(ResourcesInTask_4[0]);
        }
        #endif
        #if (NUMBER_OF_EXTENDEDTASK >= 5)
        else if (ExtendedTaskCount == 5)
        {
            NewTCB->ResourcesRel = ResourcesInTask_5;
            NewTCB->NumberOfResources = sizeof(ResourcesInTask_5)/sizeof(ResourcesInTask_5[0]);
        }
        #endif
        #if (NUMBER_OF_EXTENDEDTASK >= 6)
        else if (ExtendedTaskCount == 6)
        {
            NewTCB->ResourcesRel = ResourcesInTask_6;
            NewTCB->NumberOfResources = sizeof(ResourcesInTask_6)/sizeof(ResourcesInTask_6[0]);
        }
        #endif
        #if (NUMBER_OF_EXTENDEDTASK >= 7)
        else if (ExtendedTaskCount == 7)
        {
            NewTCB->ResourcesRel = ResourcesInTask_7;
            NewTCB->NumberOfResources = sizeof(ResourcesInTask_7)/sizeof(ResourcesInTask_7[0]);
        }
        #endif
        #if (NUMBER_OF_EXTENDEDTASK >= 8)
        else if (ExtendedTaskCount == 8)
        {
            NewTCB->ResourcesRel = ResourcesInTask_8;
            NewTCB->NumberOfResources = sizeof(ResourcesInTask_8)/sizeof(ResourcesInTask_8[0]);
        }
        #endif

        /* Set/Edit Priority Ceiling of the Resources,
         * The ceiling priority shall be set at least to the highest
         * priority of all tasks that access a resource or any of the resources linked
         * to this resource */
        pAccessRes = (UBaseType_t *) &(*NewTCB->ResourcesRel);
        for(x = NULL; x < (NewTCB->NumberOfResources); x++)
        {
            ppRes = (UBaseType_t *) (*pAccessRes);
            pResInResourceStruct = (OsResource *) (*ppRes);
            if (NewTCB->Priority > pResInResourceStruct->CeilingPriority)
            {
                pResInResourceStruct->CeilingPriority = NewTCB->Priority;
            }
            pAccessRes++;
        }
        #endif /* NUMBER_OF_RESOURCES */
    }
    #endif /* NUMBER_OF_EXTENDEDTASK */

    NewTCB->TaskRequest = NULL;
    NewTCB->TaskActivation =NULL;

   vListInitialiseItem( &( NewTCB->StateListItem ) );

   /* Set the NewTCB as a link back from the ListItem_t.  This is so we can get
   back to the containing TCB from a generic item in a list. */
   listSET_LIST_ITEM_OWNER( &( NewTCB->StateListItem ), NewTCB );

   NewTCB->TopOfStack = pxPortInitialiseStack( pxTopOfStack, NewTCB->TaskCode , NULL );

   NewTCB->TaskHandle = ( TaskHandle_t ) NewTCB;

   TaskRegistration(NewTCB);

   if ( NewTCB->AutoStart != FALSE )
   {
       /* Place the task represented by NewTCB into the appropriate ready list for
       the task. It is inserted at the end of the list. */

       /* TopReadyPriority holds the priority of the highest priority ready
       state task. */
       if ( NewTCB->Priority > TopReadyPriority )
       {
           TopReadyPriority = NewTCB->Priority;
       }
       vListInsertEnd( &( ReadyTasksLists[ NewTCB->Priority ] ), &( NewTCB->StateListItem ) );
       /* Setup TCB */
       ( void ) NewTCB;
   }
   else
   {
       /* Place the task represented by NewTCB into the Suspended list
       It is inserted at the end of the list. */
       vListInsertEnd( &SuspendedTaskList, &( NewTCB->StateListItem ) );
       /* Setup TCB */
       ( void ) NewTCB;
   }
}

void AddTaskToReadyList(TCB_t * pxTCB, BaseType_t *YieldRequired)
{
    ( void ) uxListRemove(  &( pxTCB->StateListItem ) );
    if( (pxTCB->Priority ) > TopReadyPriority )
    {
        TopReadyPriority = ( pxTCB->Priority);
    }
    vListInsertEnd( &( ReadyTasksLists[ pxTCB->Priority ] ), &( pxTCB->StateListItem ) );
    /* The context switch should be performed if the Activated task
     * has a priority that is equal to or higher than the currently
     * executing task and the current task defined as full preemption */
    if( pxTCB->Priority >= pxCurrentTCB->Priority )
    {
        *YieldRequired = pdTRUE;
    }
}
#if NUMBER_OF_RESOURCES
void ResComeAddTaskToReadyList(OsResource *r_Res,  BaseType_t *YieldRequired)
{
    OsTask *b_TCB;
    UBaseType_t i;
    for(i = 0; i < listCURRENT_LIST_LENGTH( &DelayedTaskList1 ); i++)
    {
        if(listLIST_IS_EMPTY( &DelayedTaskList1 ))
        {
            /* The delayed list is empty.*/
            break;
        }
        else
        {
            /* The delayed list is not empty,
             * get the next task in the delayed list.*/
            listGET_OWNER_OF_NEXT_ENTRY(b_TCB, &DelayedTaskList1 )
            if (b_TCB->ResRequired == r_Res)
            {
                /* Place the unblocked task into the appropriate ready list. */
                AddTaskToReadyList(b_TCB, YieldRequired);
                b_TCB->ResRequired = NULL;
                break;
            }
        }
    }
}

#endif

void BlockTask(TCB_t * pxTCB)
{
    ( void ) uxListRemove(  &( pxTCB->StateListItem ) );
    vListInsertEnd( &DelayedTaskList1, &( pxCurrentTCB->StateListItem ) );
    portYIELD();
}

void InitTask (void)
{
    TaskType TaskID;

    for(TaskID = IDLETASK_ID; TaskID <= NUMBER_OF_TASKS; TaskID++)
    {
        InitialiseNewTask(TaskID);
    }
}

BaseType_t xTaskIncrementTick( void )
{
    BaseType_t xSwitchRequired = pdFALSE;

    /* Called by the portable layer each time a tick interrupt occurs.
    Increments the tick then checks to see if the new tick value will cause any
    tasks to be unblocked. */
    if( SchedulerSuspended == ( UBaseType_t ) pdFALSE )
    {
        /* Minor optimisation.  The tick count cannot change in this
        block. */
        const TickType_t xConstTickCount = TickCount + 1;

        /* Increment the RTOS tick, switching the delayed and overflowed
        delayed lists if it wraps to 0. */
        TickCount = xConstTickCount;
#if NUMBER_OF_COUNTER
        CounterIncrementHook();
#endif
#if NUMBER_OF_ALARM
        AlarmHook( &xSwitchRequired );
#endif
    }
    else
    {
        ++PendedTicks;
    }

#if ( configUSE_PREEMPTION == 1 )
    {
        if( YieldPending != pdFALSE )
        {
            xSwitchRequired = pdTRUE;
        }
        else
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
#endif /* configUSE_PREEMPTION */

    return xSwitchRequired;
}

void vTaskSwitchContext( void )
{
    if( SchedulerSuspended != ( UBaseType_t ) pdFALSE )
    {
        /* The scheduler is currently suspended - do not allow a context
        switch. */
        YieldPending = pdTRUE;
    }
    else
    {
        YieldPending = pdFALSE;

        /* Select a new task to run using either the generic C or port
        optimised asm code. */
        {
            UBaseType_t TopPriority = TopReadyPriority;
            /* Find the highest priority queue that contains ready tasks. */
            while( listLIST_IS_EMPTY( &( ReadyTasksLists[ TopPriority ] ) ) )
            {
                --TopPriority;
            }

            if ((listIS_CONTAINED_WITHIN( &SuspendedTaskList, &( pxCurrentTCB->StateListItem ) ) != pdFALSE) || (pxCurrentTCB->Schedule != non))
            {
                /* listGET_OWNER_OF_NEXT_ENTRY indexes through the list, so the tasks of
                the same priority get an equal share of the processor time. */
                listGET_OWNER_OF_NEXT_ENTRY( pxCurrentTCB, &( ReadyTasksLists[ TopPriority ] ) );
                TopReadyPriority = TopPriority;
            }
        }
    }
}


void StartOS (AppModeType Mode)
{
    /* Interrupts are turned off here, to ensure a tick does not occur
    before or during the call to StartOS(). The interrupts will automatically
    get re-enabled when the first task
    starts to run. */
    portDISABLE_INTERRUPTS();
    NextTaskUnblockTime = portMAX_DELAY;

    InitTask();
#if NUMBER_OF_COUNTER
    InitCounter();
#endif
#if NUMBER_OF_ALARM
    InitAlarm();
#endif
    SchedulerRunning = pdTRUE;
    TickCount = ( TickType_t ) 0U;

    if( xPortStartScheduler() != pdFALSE )
    {
        /* Should not reach here as if the scheduler is running the
        function will not return. */
    }
    else
    {
        /* Should only reach here if a task calls xTaskEndScheduler(). */
    }
}

static BaseType_t TaskResume( TCB_t * pxTCB, BaseType_t ChainTask )
    {
    BaseType_t xYieldRequired = pdFALSE;
    UBaseType_t uxSavedInterruptStatus;

        portASSERT_IF_INTERRUPT_PRIORITY_INVALID();

        uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();
        {
            /* Chick if this function called from ChainTask API or not */
            if( ChainTask != pdFALSE )
            {
                /* The TaskResume API called from ChainTask API,
                Terminate the current task and re-activate it if it has multiple activation */
                ( void ) uxListRemove( &( pxCurrentTCB->StateListItem ) );
                vListInsertEnd( &SuspendedTaskList, &( pxCurrentTCB->StateListItem ) );
                if (pxCurrentTCB->TaskRequest > 1)
                {
                    pxCurrentTCB->TaskRequest--;
                    ( void ) uxListRemove( &( pxCurrentTCB->StateListItem ) );
                    vListInsertEnd( &( ReadyTasksLists[ pxCurrentTCB->Priority ] ), &( pxCurrentTCB->StateListItem ) );
                    xYieldRequired = pdTRUE;
                }
                else
                {
                    pxCurrentTCB->TaskRequest = NULL;
                }
            }
            /* Chick if this function called from ActivateTask API or
            from ChainTask API with zero activation of Current Task */
            if ( (ChainTask == pdFALSE) || (pxCurrentTCB->TaskRequest == NULL) )
            {
                if( listIS_CONTAINED_WITHIN( &SuspendedTaskList, &( pxTCB->StateListItem ) ) != pdFALSE )
                {
                    /* Ready lists can be accessed so move the task from the
                    suspended list to the ready list directly. */
                    if( pxTCB->Priority >= pxCurrentTCB->Priority )
                    {
                        xYieldRequired = pdTRUE;
                    }
                    else
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    ( void ) uxListRemove( &( pxTCB->StateListItem ) );

                    /* Place the task represented by NewTCB into the appropriate ready list for
                    the task. It is inserted at the end of the list. */

                    /* TopReadyPriority holds the priority of the highest priority ready
                    state task. */
                    if ( pxTCB->Priority > TopReadyPriority )
                    {
                        TopReadyPriority = pxTCB->Priority;
                    }
                    vListInsertEnd( &( ReadyTasksLists[ pxTCB->Priority ] ), &( pxTCB->StateListItem ) );

                    if ((pxTCB->TaskRequest) < (pxTCB->TaskActivation))
                    {
                        pxTCB->TaskRequest++;
                    }
                }
                else
                {
                    mtCOVERAGE_TEST_MARKER();
                }
            }
        }
        portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus );

        return xYieldRequired;
    }

/*******************************************************************************/

StatusType ActivateTask (TaskType TaskID)
{
    TaskHandle_t TaskHandle;
    TCB_t *pxTCB;
    StatusType ret = E_OK;
    TaskHandle = (void *) TaskID;
    pxTCB = ( TCB_t * ) TaskHandle;

    /* The context switch should be performed if
    the current task defined as full preemption */
    if ( (TaskResume( pxTCB, pdFALSE ) != pdFALSE) && (pxCurrentTCB->Schedule != NON_PREEMPTIONTASK) )
    {
        portYIELD();
    }
    else
    {
        /* The Current Task doesn't let any task to preempt it */
    }
    return ret;
}


StatusType TerminateTask (void)
{
    StatusType ret = E_OK;
    TCB_t *pxTCB;
    pxTCB = ( TCB_t * ) pxCurrentTCB;

    portDISABLE_INTERRUPTS();
    {
        ( void ) uxListRemove( &( pxTCB->StateListItem ) );
        vListInsertEnd( &SuspendedTaskList, &( pxTCB->StateListItem ) );
        if (pxTCB->TaskRequest > 1)
        {
            pxTCB->TaskRequest--;
            ( void ) uxListRemove( &( pxTCB->StateListItem ) );
            if ( pxTCB->Priority > TopReadyPriority )
            {
                TopReadyPriority = pxTCB->Priority;
            }
            vListInsertEnd( &( ReadyTasksLists[ pxTCB->Priority ] ), &( pxTCB->StateListItem ) );
            portYIELD_WITHIN_API();
        }
        else
        {
            pxTCB->TaskRequest = 0;
        }
    }
    portENABLE_INTERRUPTS();
    portYIELD_WITHIN_API();

    return ret;
}

StatusType ChainTask (TaskType TaskID)
{
    TaskHandle_t TaskHandle;
    TCB_t *pxTCB;
    StatusType ret = E_OK;
    TaskHandle = (void *) TaskID;
    pxTCB = ( TCB_t * ) TaskHandle;

    /* The context switch should be performed if
    the current task defined as full preemption */
    if ( (TaskResume( pxTCB, pdFALSE ) != pdFALSE) && (pxCurrentTCB->Schedule != NON_PREEMPTIONTASK) )
    {
        portYIELD();
    }
    else
    {
        /* The Current Task doesn't let any task to preempt it */
    }
    return ret;
}

StatusType GetTaskID ( TaskRefType TaskID )
{
    StatusType ret = E_OK;
    TaskHandle_t TaskHandle;
    TaskHandle = (void *) pxCurrentTCB;
    *TaskID = (TaskType) TaskHandle;
    return ret;
}

StatusType GetTaskState ( TaskType TaskID, TaskStateRefType State )
{
    StatusType ret = E_OK;
    TaskHandle_t TaskHandle;
    List_t *pStateList;
    TaskHandle = (void *) TaskID;
    const TCB_t * const pxTCB = ( TCB_t * ) TaskHandle;

    /* We should to enter critical section and save the state of the task
    to ensure the task will not change his state while read it */
    portDISABLE_INTERRUPTS();
    {
        pStateList = ( List_t * ) listLIST_ITEM_CONTAINER( &( pxTCB->StateListItem ) );
    }
    portENABLE_INTERRUPTS();

    if(pxTCB == pxCurrentTCB)
    {
        *State = RUNNING;
    }
    else if (pStateList == &DelayedTaskList1)
    {
        *State = WAITING;
    }
    else if (pStateList == &SuspendedTaskList)
    {
        *State = SUSPENDED;
    }
    else
    {
        /* If the task is not in any other state, it must be in the
        Ready state */
        *State = READY;
    }
    return ret;
}
