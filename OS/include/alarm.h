/*
 * alarm.h
 *
 *  Created on: Apr 8, 2018
 *      Author: Dell
 */

#ifndef ALARM_H_
#define ALARM_H_

#include "AutoSARConfig.h"

typedef UBaseType_t         AlarmType;
typedef UBaseType_t         TickType;
typedef AlarmType           *TickRefType;

typedef void *              AlarmHandle_t;
typedef void *              CounterHandle_t;

#define DeclareAlarm(AlarmID) extern AlarmType const AlarmID;

typedef struct AlarmBase
{
    UBaseType_t                  TicksPerBase;             /* TICKSPERBASE */
    UBaseType_t                  MaxAllowedValue;          /* MAXALLOWEDVALUE */
    UBaseType_t                  MinCycle;
}AlarmBaseType;

typedef AlarmBaseType       *AlarmBaseRefType;

void InitCounter (void);
void InitAlarm (void);

StatusType GetAlarmBase ( AlarmType AlarmID, AlarmBaseRefType Info );
StatusType GetAlarm ( AlarmType AlarmID, TickRefType Tick );
StatusType SetRelAlarm ( AlarmType AlarmID, TickType increment, TickType cycle );
StatusType SetAbsAlarm ( AlarmType AlarmID, TickType start, TickType cycle );
StatusType CancelAlarm ( AlarmType AlarmID );

#endif /* ALARM_H_ */
