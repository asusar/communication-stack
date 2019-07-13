/*
 * event.h
 *
 *  Created on: Apr 5, 2018
 *      Author: Dell
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "AutoSARConfig.h"

#define DeclareEvent(EventID) extern EventMaskType EventID;

#define NONEXISTANT    portMAX_DELAY

typedef void * EventHandle_t;
typedef UBaseType_t EventType;
typedef UBaseType_t EventMaskType;
typedef EventMaskType * EventMaskRefType;

StatusType SetEvent ( TaskType TaskID ,EventMaskType Mask);
StatusType WaitEvent ( EventMaskType Mask );
StatusType GetEvent ( TaskType TaskID , EventMaskRefType Event );
StatusType ClearEvent ( EventMaskType Mask );

#endif /* EVENT_H_ */
