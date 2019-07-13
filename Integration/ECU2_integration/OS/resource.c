/*
 * resource.c
 *
 *  Created on: Apr 12, 2018
 *      Author: Dell
 */


#ifdef NumberOfResources

#include "resource.h"

extern OsResource ResourceStruct[NUMBER_OF_RESOURCES];
extern OsTask * volatile pxCurrentTCB;
extern void BlockTask(TCB_t * pxTCB);
extern void ResComeAddTaskToReadyList(OsResource *r_Res,  BaseType_t *YieldRequired);


StatusType GetResource ( ResourceType ResID )
{
    StatusType ret = E_OK;
    OsTask *CurrentTCB;
    OsResource *Res;
    UBaseType_t *ppRes;
    UBaseType_t *ResMatch;
    UBaseType_t *pAccessRes;
    UBaseType_t x,match;
    ResourceHandle_t ResourceHandle;
    ResourceHandle = (void *) ResID;

    CurrentTCB = ( TCB_t * ) pxCurrentTCB;
    Res = (OsResource *) ResourceHandle;

    /* Check if the CurrentTCB has an authority to access the Resource */
    pAccessRes = (UBaseType_t *) &(*pxCurrentTCB->ResourcesRel);
    for(x = NULL; x < (pxCurrentTCB->NumberOfResources); x++)
    {
        ppRes = (UBaseType_t *) (*pAccessRes);
        ResMatch = (UBaseType_t *) (*ppRes);
        if (ResID == (ResourceType) ResMatch)
        {
            match = TRUE;
        }
        pAccessRes++;
    }
    if (match == FALSE)
    {
        ret = E_OS_ID;
    }
    else
    {
        portDISABLE_INTERRUPTS();
        {
            if (Res->Availability == FALSE)
            {
                /* The Resource is already taken from another task,
                 the current task will be block. */
                CurrentTCB->ResRequired = Res;
                BlockTask(CurrentTCB);
            }
            CurrentTCB->Priority = Res->CeilingPriority;
            Res->Availability = FALSE;
        }
        portENABLE_INTERRUPTS();
    }
return ret;
}

StatusType ReleaseResource ( ResourceType ResID )
{
    StatusType ret = E_OK;
    OsResource *Res;
    UBaseType_t *ppRes;
    UBaseType_t *ResMatch;
    UBaseType_t *pAccessRes;
    UBaseType_t x,match;
    ResourceHandle_t ResourceHandle;
    BaseType_t YieldRequired = FALSE;
    ResourceHandle = (void *) ResID;

    Res = (OsResource *) ResourceHandle;

    /* Check if the CurrentTCB has an authority to access the Resource */
    pAccessRes = (UBaseType_t *) &(*pxCurrentTCB->ResourcesRel);
    for(x = NULL; x < (pxCurrentTCB->NumberOfResources); x++)
    {
        ppRes = (UBaseType_t *) (*pAccessRes);
        ResMatch = (UBaseType_t *) (*ppRes);
        if (ResID == (ResourceType) ResMatch)
        {
            match = TRUE;
        }
        pAccessRes++;
    }
    if (match == FALSE)
    {
        ret = E_OS_ID;
    }
    else
    {
        if (Res->Availability == FALSE)
        {
            ResComeAddTaskToReadyList(Res, &YieldRequired);
            Res->Availability = TRUE;      /*Now Res is available to get*/
            if (YieldRequired)
            {
                portYIELD();
            }
        }
    }
    return ret;
}


#endif
