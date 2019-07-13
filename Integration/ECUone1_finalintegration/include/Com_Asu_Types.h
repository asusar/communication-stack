 /***************************************************
 *
 * File Name: Com_Asu_Types.h
 *
 * Author: AUTOSAR COM Team
 *
 * Date Created: 10 April 2019
 *
 * Version	: 01
 *
 ****************************************************/

#ifndef COM_ASU_TYPES_H_
#define COM_ASU_TYPES_H_

#include "Com_Types.h"
#include "ComStack_Types.h"


typedef struct {

	uint32 Com_Asu_DeadlineCounter;
	uint8 ComSignalUpdated;
} Com_Asu_Signal_type;


typedef struct {
	uint16  ComTxIPduNumberOfRepetitionsLeft;
	uint16 ComTxModeRepetitionPeriodTimer;
	uint16 ComTxModeTimePeriodTimer;
} Com_Asu_TxIPduTimer_type;

typedef struct
{
    PduLengthType CurrentPosition;
    boolean Locked;
}PduBufferState_type;


typedef struct {

	Com_Asu_TxIPduTimer_type Com_Asu_TxIPduTimers;

	/* to check if the signal updated or not */
	boolean Com_Asu_IpduStarted;

	boolean Com_Asu_Pdu_changed;

	/* in case direct or mixed mode.
	 * this flag indicates whether this is the first transmission of the IPDU or not
	 */
	boolean Com_Asu_First_Repetition;
	uint16 Com_Asu_DynSignalLength;
	uint16 Com_Asu_DeferredDynSignalLength;
	uint64 Deffert;
	PduBufferState_type PduBufferState;
} Com_Asu_IPdu_type;




typedef struct {
	void *Com_Arc_ShadowBuffer;
	uint8 ComSignalUpdated;
	uint8 Com_Arc_EOL;
} Com_Asu_GroupSignal_type;

typedef struct {
	Com_Asu_IPdu_type *ComIPdu; // Only used in PduIdCheck()
	Com_Asu_Signal_type *ComSignal;
	Com_Asu_GroupSignal_type *ComGroupSignal;
} Com_Asu_Config_type;


#endif
