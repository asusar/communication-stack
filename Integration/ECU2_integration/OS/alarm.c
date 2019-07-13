/*
 * alarm.c
 *
 *  Created on: Apr 8, 2018
 *      Author: Dell
 */

#include "include/alarm.h"
#include "freertos/list.h"
#include "include/event.h"

#define SYSTEM_COUNTER_ID       NULL

#if NUMBER_OF_ALARM

List_t CounterList;
List_t DormantAlarmList;

static volatile UBaseType_t CurrentNumberOfCounters             = ( UBaseType_t ) 0U;
static volatile UBaseType_t CurrentNumberOfAlarms               = ( UBaseType_t ) 0U;

extern OsCounter CounterStruct[NUMBER_OF_COUNTER];
extern OsAlarm AlarmStruct[NUMBER_OF_ALARM];
extern void AddTaskToReadyList(TCB_t * pxTCB, BaseType_t *YieldRequired);
extern UBaseType_t CheckEventTask( TCB_t * pxTCB, UBaseType_t Mask );

static void InitialiseNewCounter (UBaseType_t CounterID)
{
    OsCounter * NewCCB;
    NewCCB = &CounterStruct[CounterID];

    if (CurrentNumberOfCounters == 0)
    {

        vListInitialise( &CounterList );
    }

    NewCCB->CountValue = 1;
    NewCCB->TickValue = 0;
    vListInitialiseItem( &(NewCCB->CounterListItem) );
    listSET_LIST_ITEM_OWNER( &(NewCCB->CounterListItem), NewCCB );
    vListInsertEnd( &CounterList, &(NewCCB->CounterListItem) );

    /* Initialise empty List of Alarms which are based for this Counter */
    vListInitialise (&(NewCCB->AlarmList));

    CurrentNumberOfCounters++;
}

void InitCounter (void)
{
    UBaseType_t CounterID;

    for(CounterID = SYSTEM_COUNTER_ID; CounterID < NUMBER_OF_COUNTER; CounterID++)
    {
        InitialiseNewCounter(CounterID);
    }
}

/* Using this function in SysTick_Handler > TaskIncrementTick */
void CounterIncrementHook ( void )
{
    OsCounter * pCCB;
    UBaseType_t i;

    for ( i = 0; i < CurrentNumberOfCounters; i++)
    {
        listGET_OWNER_OF_NEXT_ENTRY(pCCB,&CounterList)

        pCCB->TickValue++;
        if ( pCCB->CountValue == pCCB->MaxAllowedValue )
        {
            pCCB->CountValue = 1;
            pCCB->TickValue = 0;
        }
        if ( ((pCCB->TickValue == (pCCB->TicksPerBase)*(pCCB->CountValue)) || ( pCCB->TickValue == pCCB->TicksPerBase )) && ( pCCB->TickValue != 0) )
        {
            pCCB->CountValue++;
        }
    }
}


static UBaseType_t InitialiseNewAlarm (UBaseType_t AlarmID)
{
    OsAlarm *NewACB;
    TickType_t TimeTickToWake;
    NewACB = &AlarmStruct[AlarmID];

    if (CurrentNumberOfAlarms == 0)
    {
        vListInitialise(&DormantAlarmList);
    }
    vListInitialiseItem( &( NewACB->TimerListItem ) );
    if (NewACB->CycleTime <= NewACB->pCounterID->MinCycle)
    {
        return NULL;
    }
    else
    {
        if(NewACB->AutoStart == pdTRUE)
        {

            NewACB->LocalNextAlarmTime = NewACB->CycleTime + 1;
            TimeTickToWake = NewACB->LocalNextAlarmTime;
            listSET_LIST_ITEM_VALUE( &( NewACB->TimerListItem ), TimeTickToWake);
            listSET_LIST_ITEM_OWNER( &( NewACB->TimerListItem ), NewACB );
            vListInsert( &(NewACB->pCounterID->AlarmList), &( NewACB->TimerListItem ) );
        }
        else
        {
            listSET_LIST_ITEM_OWNER( &( NewACB->TimerListItem ), NewACB );
            vListInsert( &DormantAlarmList, &( NewACB->TimerListItem ) );
        }
        CurrentNumberOfAlarms++;
    }
    return NULL;
}




void InitAlarm (void)
{
    #if NUMBER_OF_ALARM
    UBaseType_t AlarmID;
    for(AlarmID = NULL; AlarmID < NUMBER_OF_ALARM; AlarmID++)
    {
        InitialiseNewAlarm(AlarmID);
    }
    #endif
}


void  AlarmHook ( BaseType_t * SwitchRequired )             /* This function using in sysTick Handler */
{
    OsAlarm * pACB;
    OsCounter * pCCB;
    TCB_t * pTCB;
    UBaseType_t *Ptr1;
    UBaseType_t *Ptr2;
    UBaseType_t i,j=0;

    /* Loop in Counter's list */
    for ( i = 0; i < CurrentNumberOfCounters; i++)
    {
        /* Beginning get the the first Counter in the list counter
         * and point it using pCCB, after each loop, the pointer pCCB
         * point to next counter in the list */
        listGET_OWNER_OF_NEXT_ENTRY(pCCB,&CounterList);

        /* Loop in Alarms in the Counter */
        ///////////////////////////////////////////////////////////////////////
        ////// Error in 2*.. because if we have many counters /////////////////
        ///////////////////////////////////////////////////////////////////////
        for ( j = 0; j < (2*listCURRENT_LIST_LENGTH( &(pCCB->AlarmList) )); j++)
        {
            /* Get Alarms that related to this counter and chick if the
             * Count tick value of the counter is equal to the LocalNextAlarmTime
             * to be performed */
            listGET_OWNER_OF_NEXT_ENTRY( pACB, &( pCCB->AlarmList ) )
            if ( pACB->LocalNextAlarmTime == pCCB->CountValue )
            {
                switch (pACB->Action)
                {
                case ACTIVATETASK:
                    Ptr1 = (UBaseType_t *) *(pACB->TaskID);
                    pTCB = (TCB_t *) Ptr1;
                    AddTaskToReadyList(pTCB, SwitchRequired);
                    break;
#if NUMBER_OF_EVENTS
                case SETEVENT:
                    Ptr1 = (UBaseType_t *) *(pACB->TaskID);
                    pTCB = (TCB_t *) Ptr1;
                    if ( pTCB->TaskType != basic )
                    {
                        pTCB->EventSet |= *(pACB->EventID);
                        if ( (pTCB->EventSet & pTCB->EventWait) )//==  *(pACB->EventID))
                        {
                            AddTaskToReadyList(pTCB, SwitchRequired);
                        }
                    }
                    break;
#endif
                default: break;
                }
                /* Chick if there are Cycles remain to be performed */
                if (pACB->AlarmTime != 0)
                {
                    ( void ) uxListRemove( &( pACB->TimerListItem ) );
                    /* Check if the addition Cycle will lead to Overflow of the counter */
                    if ( ((pACB->CycleTime) + pCCB->CountValue) >= pCCB->MaxAllowedValue )
                    {
                        pACB->LocalNextAlarmTime = ((pACB->CycleTime) + pCCB->CountValue) - pCCB->MaxAllowedValue;
                    }
                    else
                    {
                        pACB->LocalNextAlarmTime = ((pACB->CycleTime) + pCCB->CountValue);
                    }
                    listSET_LIST_ITEM_VALUE( &( pACB->TimerListItem ), pACB->LocalNextAlarmTime );
                    vListInsert( &(pCCB->AlarmList), &( pACB->TimerListItem ) );

                    pACB->AlarmTime--;
                }
                else
                {
                    ( void ) uxListRemove( &( pACB->TimerListItem ) );
                    vListInsert( &DormantAlarmList, &( pACB->TimerListItem ) );
                }
            }
        }
    }
}

StatusType GetAlarm ( AlarmType AlarmID, TickRefType Tick )
{
    StatusType ret = E_OK;
    AlarmHandle_t AlarmHandle;
    OsAlarm * pACB;
    AlarmHandle = (void *) AlarmID;
    pACB = (OsAlarm *) AlarmHandle;

    portENTER_CRITICAL();
    {
        if ( listIS_CONTAINED_WITHIN(&DormantAlarmList, &(pACB->TimerListItem)) )
        {
            ret = E_OS_NOFUNC;
        }
        else
        {
            if ( pACB->LocalNextAlarmTime >= pACB->pCounterID->CountValue)
            {
                *Tick = pACB->LocalNextAlarmTime - pACB->pCounterID->CountValue;
            }
            else
            {
                *Tick = ( (pACB->pCounterID->MaxAllowedValue) - (pACB->pCounterID->CountValue) ) + pACB->LocalNextAlarmTime;
            }
        }
    }
    portEXIT_CRITICAL();
    return ret;
}

StatusType GetAlarmBase ( AlarmType AlarmID, AlarmBaseRefType Info )
{
    StatusType ret = E_OK;
    AlarmHandle_t AlarmHandle;
    OsAlarm * pACB;
    AlarmHandle = (void *) AlarmID;
    pACB = (OsAlarm *) AlarmHandle;

    Info->TicksPerBase = pACB->pCounterID->TicksPerBase;
    Info->MaxAllowedValue = pACB->pCounterID->MaxAllowedValue;
    Info->MinCycle = pACB->pCounterID->MinCycle;

    return ret;
}

StatusType SetRelAlarm ( AlarmType AlarmID, TickType increment, TickType cycle )
{
    StatusType ret = E_OK;
    AlarmHandle_t AlarmHandle;
    OsAlarm * pACB;
    TickType TimeTickToWake;
    AlarmHandle = (void *) AlarmID;
    pACB = (OsAlarm *) AlarmHandle;

    portENTER_CRITICAL();
    {
        if ( listIS_CONTAINED_WITHIN( &DormantAlarmList, &( pACB->TimerListItem )) )
        {
            if ( increment <= pACB->pCounterID->MinCycle )
            {
                ret = E_OS_VALUE;
            }
            else
            {
                ( void ) uxListRemove( &( pACB->TimerListItem ) );
                pACB->AlarmTime = cycle - 1;
                pACB->CycleTime =  increment;
                if ( ((pACB->CycleTime) + pACB->pCounterID->CountValue) >= pACB->pCounterID->MaxAllowedValue )              /* Counter Overflow */
                {
                    pACB->LocalNextAlarmTime = ((pACB->CycleTime) + (pACB->pCounterID->CountValue)) - pACB->pCounterID->MaxAllowedValue;
                }
                else
                {
                    pACB->LocalNextAlarmTime = ((pACB->CycleTime) + (pACB->pCounterID->CountValue));
                }
                TimeTickToWake = pACB->LocalNextAlarmTime;
                listSET_LIST_ITEM_VALUE( &( pACB->TimerListItem ), TimeTickToWake );
                vListInsert( &pACB->pCounterID->AlarmList, &( pACB->TimerListItem ) );
            }
        }
        else
        {
            ret = E_OS_STATE;;
        }
    }
    portEXIT_CRITICAL();
    return ret;
}

StatusType SetAbsAlarm ( AlarmType AlarmID, TickType start, TickType cycle )
{
    StatusType ret = E_OK;
    AlarmHandle_t AlarmHandle;
    OsAlarm * pACB;
    TickType TimeTickToWake;
    AlarmHandle = (void *) AlarmID;
    pACB = (OsAlarm *) AlarmHandle;

    portENTER_CRITICAL();
    {
        if ( listIS_CONTAINED_WITHIN( &DormantAlarmList, &( pACB->TimerListItem )) )
        {
            if ( start <= pACB->pCounterID->MinCycle )
            {
                ret = E_OS_VALUE;
            }
            else
            {
                ( void ) uxListRemove( &( pACB->TimerListItem ) );
                pACB->AlarmTime = cycle - 1;
                pACB->CycleTime = start;
                pACB->LocalNextAlarmTime = start;
                TimeTickToWake = pACB->LocalNextAlarmTime;
                listSET_LIST_ITEM_VALUE( &( pACB->TimerListItem ), TimeTickToWake );
                vListInsert( &pACB->pCounterID->AlarmList, &( pACB->TimerListItem ) );
            }
        }
        else
        {
            ret = E_OS_STATE;;
        }
    }
    portEXIT_CRITICAL();
    return ret;
}

StatusType CancelAlarm ( AlarmType AlarmID )
{
    StatusType ret = E_OK;
    AlarmHandle_t AlarmHandle;
    OsAlarm * pACB;
    AlarmHandle = (void *) AlarmID;
    pACB = (OsAlarm *) AlarmHandle;

    portENTER_CRITICAL();
    {
        if ( listIS_CONTAINED_WITHIN( &DormantAlarmList, &( pACB->TimerListItem )) )
        {
            ret = E_OS_NOFUNC;
        }
        else
        {
            ( void ) uxListRemove( &( pACB->TimerListItem ) );
            vListInsert( &DormantAlarmList, &( pACB->TimerListItem ) );
        }
    }
    portEXIT_CRITICAL();
    return ret;
}

#endif
