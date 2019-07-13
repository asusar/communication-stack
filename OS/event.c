/*
 * Copyright (c) 2018-2019 Faculty of Engineering Ain Shams University Dr.Sherif Hammad Email: Sherif.hammad@eng.asu.edu.eg Eng.Mohamed abdelhay Email: mhmd.a.elhay@gmail.com.
 *
 * This file is part of ASUSAR
 * (see https://github.com/asusar/communication-stack).
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "include/task.h"
#include "include/event.h"

#if NUMBER_OF_EVENTS

#define NONEXISTANT    portMAX_DELAY

extern OsTask * volatile pxCurrentTCB;
extern void AddTaskToReadyList(TCB_t * pxTCB, BaseType_t *YieldRequired);
extern void BlockTask(TCB_t * pxTCB);

/* This function gets extern to AlarmHook fuction */
UBaseType_t CheckEventTask( TCB_t * pxTCB, UBaseType_t Mask )
{
    UBaseType_t x;
    UBaseType_t *ePtr;

    /* Pointer to address which EventsRel point to */
    ePtr = (UBaseType_t *) &(*(pxTCB->EventsRel));

    /* Check if the Event is declare in the Task and return his order in the Task */
    for(x = NULL; x < MAX_EVENTS_FOR_TASK; x++)
    {
        if(*ePtr == Mask)
        {
            return x;
        }
        else
        {
            ePtr++;
        }
    }
    /* this event doesn't exist in the task */
    return NONEXISTANT;
}

StatusType SetEvent ( TaskType TaskID ,EventMaskType Mask)
{

    StatusType ret = E_OK;
    TaskHandle_t TaskHandle;
    TCB_t *pxTCB;
    BaseType_t xYieldRequired = pdFALSE;
    UBaseType_t uxSavedInterruptStatus;
    TaskStateType TaskState = SUSPENDED;

    TaskHandle = (void *) TaskID;
    pxTCB = ( TCB_t * ) TaskHandle;

    if ( pxTCB->TaskType != basic )
    {
        GetTaskState(TaskID, &TaskState);

        portASSERT_IF_INTERRUPT_PRIORITY_INVALID();
        uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();
        {
            pxTCB->EventSet |= Mask;
            if (TaskState == WAITING)
            {
                if ( (pxTCB->EventSet & pxTCB->EventWait) )// == Mask)
                {
                    AddTaskToReadyList(pxTCB, &xYieldRequired);
                }
            }
            ret = E_OK;
        }
        portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus );

        if (xYieldRequired != pdFALSE)
        {
            portYIELD();
        }
    }
    else
    {
        ret = E_OS_ACCESS;
    }
    return ret;
}



StatusType WaitEvent ( EventMaskType Mask )
{
    StatusType ret = E_OK;
    UBaseType_t YieldNotRequired = pdFALSE;

    portDISABLE_INTERRUPTS();
    {
        if ( pxCurrentTCB->TaskType != basic)
        {
            pxCurrentTCB->EventWait |= Mask;
            ///////////////// if we wait for every
            if ( pxCurrentTCB->EventSet & pxCurrentTCB->EventWait )
            {
                YieldNotRequired = pdTRUE;
            }

            if ( !(YieldNotRequired) )
            {
                BlockTask(pxCurrentTCB);
            }
        }
        else
        {
            ret = E_OS_ACCESS;
        }
    }
    portENABLE_INTERRUPTS();
    return ret;
}

StatusType GetEvent ( TaskType TaskID , EventMaskRefType Event )
{
    StatusType ret = E_OK;
    TCB_t *pxTCB;
    TaskHandle_t TaskHandle;
    UBaseType_t x;
    UBaseType_t *ePtr;
    TaskStateType TaskState = SUSPENDED;

    TaskHandle = ( void * ) TaskID;
    pxTCB = ( TCB_t * ) TaskHandle;

    portDISABLE_INTERRUPTS();
    {
        if ( pxTCB->TaskType != basic)
        {
            GetTaskState(TaskID, &TaskState);
            if (TaskState != SUSPENDED )
            {
                *Event = pxCurrentTCB->EventSet & pxCurrentTCB->EventWait;
                ret = E_OK;
            }
            else
            {
                ret = E_OS_STATE;
            }
        }
        else
        {
            ret = E_OS_ACCESS;
        }
    }
    portENABLE_INTERRUPTS();
    return ret;
}

StatusType ClearEvent ( EventMaskType Mask )
{
    StatusType ret;

    if ( pxCurrentTCB->TaskType != basic)
    {
        portDISABLE_INTERRUPTS();
        {
            pxCurrentTCB->EventSet &= ~Mask;
        }
        portENABLE_INTERRUPTS();
        ret = E_OK;
    }
    else
    {
        ret = E_OS_ACCESS;
    }
    return ret;
}

#endif
