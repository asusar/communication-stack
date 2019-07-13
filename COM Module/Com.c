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
#include "include/Com.h"
#include "include/Com_Types.h"
#include "include/Com_helper.h"
#include "include/Com_Buffer.h"
#include "include/Com_Asu_Types.h"
#include "PduR/include/PduR_Com.h"


/*****************************************************************
 *                     Functions Definitions                     *
 *****************************************************************/


/* Com_Config declaration*/
const ComConfig_type * ComConfig;
uint8 com_pdur[] = {vcom};

/* Com_Asu_Config declaration*/
extern Com_Asu_Config_type ComAsuConfiguration;
static Com_Asu_Config_type * Com_Asu_Config = &ComAsuConfiguration;


void Com_Init( const ComConfig_type* config)
{
	/* Initialize ComConfig */
	ComConfig = config;
	const ComSignal_type *Signal;
	const ComGroupSignal_Type *GroupSignal;

	//1- loop on IPDUs
	uint16 pduId;
	for ( pduId = 0; pduId<COM_NUM_OF_IPDU; pduId++) {

		// 1.1- Initialize I-PDU
		const ComIPdu_type *IPdu = GET_IPdu(pduId);
		Com_Asu_IPdu_type *Asu_IPdu = GET_AsuIPdu(pduId);

		Asu_IPdu->Com_Asu_TxIPduTimers.ComTxModeRepetitionPeriodTimer = \
						IPdu->ComTxIPdu.ComTxModeFalse.ComTxMode.ComTxModeRepetitionPeriod;

		Asu_IPdu->Com_Asu_TxIPduTimers.ComTxModeTimePeriodTimer = \
								IPdu->ComTxIPdu.ComTxModeFalse.ComTxMode.ComTxModeTimePeriod;

		Asu_IPdu->Com_Asu_Pdu_changed = FALSE;

		Asu_IPdu->Com_Asu_First_Repetition = TRUE;


		// Initialize the memory with the default value.
		if (IPdu->ComIPduDirection == SEND) {
			memset((void *)IPdu->ComIPduDataPtr, IPdu->ComTxIPdu.ComTxIPduUnusedAreasDefault, IPdu->ComIPduSize);
		}

		// For each signal in this PDU
		uint16 signalId;
		for ( signalId = 0; (IPdu->ComIPduSignalRef != NULL) && \
								(IPdu->ComIPduSignalRef[signalId] != NULL); signalId++)
		{
			Signal = IPdu->ComIPduSignalRef[signalId];

			// Clear update bits
			CLEARBIT(IPdu->ComIPduDataPtr, Signal->ComUpdateBitPosition);



	        // If this signal is a signal group
	        if(!GET_SIGNAL_TYPE(signalId)){
	            ComSignalGroup_Type *signalGroup=IPdu->ComIPduSignalGroupRef[pduId];
	            Com_Asu_SignalGroup_type *AsuSignalGroup=GET_ASUSIGNALGROUP(signalGroup->ComHandleId);

	            // Set pointer to shadow buffer
	            AsuSignalGroup->Com_Asu_ShadowBuffer=(void*)signalGroup->Com_Asu_ShadowBuffer;

	            // For each group signal of this signal group.
	            uint8 groupSignalId;
	            for(groupSignalId=0;(signalGroup->ComGroupSignal!=Null && signalGroup->ComGroupSignal[groupSignalId]!=NULL);groupSignalId++)
	            {
	                GroupSignal=signalGroup->ComGroupSignal[groupSignalId];
	                //update group initial value to the shadow buffer
	                Com_WriteSignalDataToShadowBuffer(GroupSignal->ComSignalGroupId,GroupSignal->ComHandleId, GroupSignal->ComSignalInitValue)

	            }
	        }
		}



	}
}

static void Com_RxProcessSignals(PduIdType ComRxPduId)
{
    const ComSignal_type *comSignal = NULL;
    const ComIPdu_type *IPdu = GET_IPdu(ComRxPduId);
    Com_Asu_Signal_type * Asu_Signal = NULL;
    uint8 signalId;
        for( signalId = 0; IPdu->ComIPduSignalRef[signalId] != NULL; signalId++)
        {
        	comSignal = IPdu->ComIPduSignalRef[signalId];
        	Asu_Signal = GET_AsuSignal(comSignal->ComHandleId);

        	if (CHECKBIT(IPdu->ComIPduDataPtr, comSignal->ComUpdateBitPosition))
        	{
				if (IPdu->ComIPduSignalProcessing == IMMEDIATE)
				{
					// unpack the pdu and update signal buffer
					Com_UnPackSignalsFromPdu(ComRxPduId);

					// If signal processing mode is IMMEDIATE, notify the signal callback.
					if (IPdu->ComIPduSignalRef[signalId]->ComNotification != NULL)
					{
						IPdu->ComIPduSignalRef[signalId]->ComNotification();
					}
				}
				else
				{
					// Signal processing mode is DEFERRED, mark the signal as updated.
					Asu_Signal->ComSignalUpdated = 1;
				}
        	}
        }
}

void Com_MainFunctionRx(void)
{
	const ComIPdu_type *IPdu = NULL;
	const ComSignal_type *signal = NULL;
	Com_Asu_Signal_type * Asu_Signal = NULL;
	uint16 signalID;

    /* Loop on IPDUs */
	uint16 pduId;
	for ( pduId = 0; pduId < COM_NUM_OF_IPDU; pduId++)
	{
		IPdu = GET_IPdu(pduId);

		if (IPdu->ComIPduSignalProcessing == DEFERRED && IPdu->ComIPduDirection == RECEIVE)
		{
			/* copy the deferred buffer to the actual pdu buffer */
			Com_UnPackSignalsFromPdu(pduId);

			/* loop on the signal in this ipdu */
			for (signalID = 0; (IPdu->ComIPduSignalRef != NULL) && (IPdu->ComIPduSignalRef[signalID] != NULL); signalID++)
			{
				signal = IPdu->ComIPduSignalRef[signalID];
				Asu_Signal = GET_AsuSignal(signal->ComHandleId);

				/* if at least on signal is Updated, mark this Pdu as Updated */
				if (Asu_Signal->ComSignalUpdated)
				{
					if (signal->ComNotification != NULL)
					{
						signal->ComNotification();
					}
					Asu_Signal->ComSignalUpdated = FALSE;
				}
			}
		}
	}
}

void Com_MainFunctionTx(void)
{
    int x;
	const ComIPdu_type *IPdu;
	Com_Asu_IPdu_type *Asu_IPdu;
	static uint64 timer=0;
	char* str;
	timer++;
//	printString("time elapsed : ");
//	UART_OutUDec(timer);
//	printString("\n\r");

	//Loop on IPDUs
	uint16 pduId;
	for ( pduId = 0; pduId<COM_NUM_OF_IPDU; pduId++)
	{
		IPdu = GET_IPdu(pduId);
		Asu_IPdu = GET_AsuIPdu(pduId);


		/* if it is a send PDU*/
		if(IPdu->ComIPduDirection == SEND)
		{
			boolean mixed = FALSE;

			switch(IPdu->ComTxIPdu.ComTxModeFalse.ComTxMode.ComTxModeMode)
			{
			/* if the transmission mode is mixed */
			case MIXED:
				mixed = TRUE;
				/* no break because the mixed is periodic and direct */
			/* if the transmission mode is periodic */
			case PERIODIC:

				timerDec(Asu_IPdu->Com_Asu_TxIPduTimers.ComTxModeTimePeriodTimer);

				if(Asu_IPdu->Com_Asu_TxIPduTimers.ComTxModeTimePeriodTimer<=0)
				{
					if(Com_TriggerIPDUSend(pduId) == E_OK)
					{
						Asu_IPdu->Com_Asu_TxIPduTimers.ComTxModeTimePeriodTimer = \
								IPdu->ComTxIPdu.ComTxModeFalse.ComTxMode.ComTxModeTimePeriod;
					}
				}
				if(!mixed)/* in case the Pdu is mixed don't break */
					break;
			/* if the transmission mode is direct */
			case DIRECT:
			    x = Asu_IPdu->Com_Asu_TxIPduTimers.ComTxIPduNumberOfRepetitionsLeft ;
				if(Asu_IPdu->Com_Asu_TxIPduTimers.ComTxIPduNumberOfRepetitionsLeft > 0)
				{

				        timerDec(Asu_IPdu->Com_Asu_TxIPduTimers.ComTxModeRepetitionPeriodTimer);

					if(Asu_IPdu->Com_Asu_TxIPduTimers.ComTxModeRepetitionPeriodTimer <= 0 || Asu_IPdu->Com_Asu_First_Repetition )
					{
						if(Com_TriggerIPDUSend(pduId)== E_OK)
						{
							Asu_IPdu->Com_Asu_TxIPduTimers.ComTxModeRepetitionPeriodTimer = \
											IPdu->ComTxIPdu.ComTxModeFalse.ComTxMode.ComTxModeRepetitionPeriod;

							Asu_IPdu->Com_Asu_First_Repetition = FALSE;

							Asu_IPdu->Com_Asu_TxIPduTimers.ComTxIPduNumberOfRepetitionsLeft --;
						}
					}
				}
			}
		}
	}
}

/* Updates the signal object identified by SignalId with the signal referenced by the SignalDataPtr parameter */
uint8 Com_SendSignal( Com_SignalIdType SignalId, const void* SignalDataPtr )
{
	/* validate signalID */
	if(!validateSignalID(SignalId) )
		return E_NOT_OK;

	/* Get signal of "SignalId" */
	const ComSignal_type *Signal = GET_Signal(SignalId);

	/*Get IPdu of this signal */
	const ComIPdu_type *IPdu = GET_IPdu(Signal->ComIPduHandleId);

	/* Get IPDU_Asu of signal ipduHandleId */
	Com_Asu_IPdu_type *Asu_IPdu = GET_AsuIPdu(Signal->ComIPduHandleId);

	/* update the Signal buffer with the signal data */
	Com_WriteSignalDataToSignalBuffer(Signal->ComHandleId, SignalDataPtr);

	/* if the signal is a group signal ,we should copy the signal to the shadow buffer  */

	switch(Signal->ComTransferProperty)
	{
	case TRIGGERED_WITHOUT_REPETITION:
		Asu_IPdu->Com_Asu_TxIPduTimers.ComTxIPduNumberOfRepetitionsLeft = 1;
		break;

	case TRIGGERED:
		Asu_IPdu->Com_Asu_TxIPduTimers.ComTxIPduNumberOfRepetitionsLeft = \
								(IPdu->ComTxIPdu.ComTxModeFalse.ComTxMode.ComTxModeNumberOfRepetitions) + 1;
		break;

	case TRIGGERED_ON_CHANGE:
		if (Asu_IPdu->Com_Asu_Pdu_changed)
		{
			Asu_IPdu->Com_Asu_TxIPduTimers.ComTxIPduNumberOfRepetitionsLeft = \
											(IPdu->ComTxIPdu.ComTxModeFalse.ComTxMode.ComTxModeNumberOfRepetitions) + 1;
			Asu_IPdu->Com_Asu_Pdu_changed = FALSE;
		}
		break;

	case TRIGGERED_ON_CHANGE_WITHOUT_REPETITION:
			if (Asu_IPdu->Com_Asu_Pdu_changed)
			{
				Asu_IPdu->Com_Asu_TxIPduTimers.ComTxIPduNumberOfRepetitionsLeft = 1;
				Asu_IPdu->Com_Asu_Pdu_changed = FALSE;
			}
	}


	/* If the signal has an update bit. Set it! */
	SETBIT(IPdu->ComIPduDataPtr, Signal->ComUpdateBitPosition);

	Asu_IPdu->Com_Asu_First_Repetition = TRUE;


	return E_OK;
}

/* Copies the data of the signal identified by SignalId to the location specified by SignalDataPtr */
uint8 Com_ReceiveSignal( Com_SignalIdType SignalId, void* SignalDataPtr )
{
	/* validate signalID */
	if(!validateSignalID(SignalId) )
		return E_NOT_OK;

	/* Get signal of "SignalId" */
	const ComSignal_type *Signal = GET_Signal(SignalId);

	/* Get IPDU of signal ipduHandleId */
	const ComIPdu_type *IPdu = GET_IPdu(Signal->ComIPduHandleId);

	/*if the it's an ordinary signal*/
	if(GET_SIGNAL_TYPE(SignalId)){
	    /* check ipdu direction is receive */
        if(IPdu->ComIPduDirection == RECEIVE)
        {
              Com_ReadSignalDataFromSignalBuffer(SignalId, SignalDataPtr);
        }
        else
        {
            return E_NOT_OK;
        }
	}
	/* the signa is a group signal */
	else{
	   // we should copy the signal from pdu to the shadow buffer
	}
    return E_OK;
}

uint8 Com_SendSignalGroup( Com_SignalGroupIdType SignalGroupId )
{
    ComSignalGroup_Type * SignalGroup=GET_SIGNALGROUP(SignalGroup);
    Com_Asu_IPdu_type * AsuIPdu=GET_AsuIPdu(SignalGroup->ComIPduHandleId);
    ComIPdu_type *IPdu = GET_IPdu(SignalGroup->ComIPduHandleId);

    if (AsuIPdu->PduBufferState.Locked) {
        return COM_BUSY;
    }
    // this copying process should be done atomically ,so we need to disable interrupts

    Com_CopySignalGroupDataFromShadowBufferToPdu(SignalGroupId);

    //  Set it the update bit
        SETBIT(IPdu->ComIPduDataPtr, SignalGroup->ComUpdateBitPosition);

    // If signal has triggered transmit property, trigger a transmission!
        if (SignalGroup->ComTransferProperty == TRIGGERED) {
            AsuIPdu->Com_Asu_TxIPduTimers.ComTxIPduNumberOfRepetitionsLeft = IPdu->ComTxIPdu.ComTxModeTrue.ComTxMode.ComTxModeNumberOfRepetitions+1;
        }

       //enable interrupt

        return E_OK;

}

uint8 Com_ReceiveSignalGroup( Com_SignalGroupIdType SignalGroupId )
{
    const ComSignalGroup_Type * SignalGroup = GET_SIGNALGROUP(SignalGroupId);
    const ComIPdu_type *IPdu = GET_IPdu(SignalGroup->ComIPduHandleId);
    const Com_Asu_IPdu_type *AsuIPdu=GET_AsuIPdu(SignalGroup->ComIPduHandleId);

    if (AsuIPdu->PduBufferState.Locked) {
        return COM_BUSY;
    }

    // Copy Ipdu data buffer to shadow buffer.
    Com_CopySignalGroupDataFromPduToShadowBuffer(SignalGroupId);

    return E_OK;
}
BufReq_ReturnType Com_CopyTxData( PduIdType id,  PduInfoType* info, const RetryInfoType* retry, PduLengthType* availableDataPtr )
{
    ComIPdu_type *IPdu = GET_IPdu(id);
    Com_Asu_IPdu_type *Asu_IPdu = GET_AsuIPdu(id);

    if( (IPdu->ComIPduDirection == SEND) &&
            (Asu_IPdu->PduBufferState.CurrentPosition + info->SduLength <= IPdu->ComIPduSize) )
    {
        void const * source = (uint8*)IPdu->ComIPduDataPtr + Asu_IPdu->PduBufferState.CurrentPosition;
        LOCKBUFFER(&Asu_IPdu->PduBufferState);
        info->SduDataPtr = source;
        //memcpy( (void*) info->SduDataPtr, source, info->SduDataPtr);
        Asu_IPdu->PduBufferState.CurrentPosition += info->SduLength;
        *availableDataPtr = IPdu->ComIPduSize - Asu_IPdu->PduBufferState.CurrentPosition;
        return BUFREQ_OK;
    }
    else
    {
        return BUFREQ_E_NOT_OK;
    }

}

BufReq_ReturnType Com_CopyRxData( PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr )
{
    ComIPdu_type *IPdu = GET_IPdu(id);
    Com_Asu_IPdu_type *Asu_IPdu = GET_AsuIPdu(id);

    if( (IPdu->ComIPduDirection == RECEIVE) &&\
                (IPdu->ComIPduSize - Asu_IPdu->PduBufferState.CurrentPosition >= info->SduLength )&&\
				!Asu_IPdu->PduBufferState.Locked)
    {
        //lock the buffer until copying is done
                    LOCKBUFFER(&AsuIPduAsu_IPdu->PduBufferState);
        void* distination =(void*)((uint8 *) IPdu->ComIPduDataPtr+ Asu_IPdu->PduBufferState.CurrentPosition);
        if(info->SduDataPtr != NULL)
        	memcpy(distination, info->SduDataPtr, info->SduLength);
        Asu_IPdu->PduBufferState.CurrentPosition += info->SduLength;
        *bufferSizePtr = IPdu->ComIPduSize - Asu_IPdu->PduBufferState.CurrentPosition;

        return BUFREQ_OK;
    }
    else
    {
        return BUFREQ_E_NOT_OK;
    }
}

Std_ReturnType Com_TriggerIPDUSend( PduIdType PduId )
{
	const ComIPdu_type *IPdu = GET_IPdu(PduId);
	Com_Asu_IPdu_type *Asu_IPdu = GET_AsuIPdu(PduId);
	PduInfoType PduInfoPackage;
	uint8 signalID;

	Com_PackSignalsToPdu(PduId);
	PduInfoPackage.SduDataPtr = (uint8 *)IPdu->ComIPduDataPtr;
	PduInfoPackage.SduLength = IPdu->ComIPduSize;

	if (Asu_IPdu->PduBufferState.Locked)
	{
		return E_NOT_OK;
	}

	if (PduR_ComTransmit(com_pdur[IPdu->ComIPduHandleId], &PduInfoPackage) == E_OK)
	{
		// Clear all update bits for the contained signals
	    for ( signalID = 0; (IPdu->ComIPduSignalRef[signalID] != NULL); signalID++)
		{
			CLEARBIT(IPdu->ComIPduDataPtr, IPdu->ComIPduSignalRef[signalID]->ComUpdateBitPosition);
		}

	}
	else
	{
		return E_NOT_OK;
	}
	return E_OK;
}

void Com_RxIndication(PduIdType ComRxPduId, const PduInfoType* PduInfoPtr)
{
	const ComIPdu_type *IPdu = GET_IPdu(ComRxPduId);


	/* copy the received data to the actual IPdu buffer */
//	if(IPdu->ComIPduSignalProcessing == IMMEDIATE)
//	{
//		memcpy(IPdu->ComIPduDataPtr, PduInfoPtr->SduDataPtr, IPdu->ComIPduSize);
//	}
//	/* copy the received data to the Deferred buffer then copy it to the actual buffer in Com_MainFunctionRX */
//	else
//	{
//		memcpy(IPdu->ComIPduDeferredDataPtr, PduInfoPtr->SduDataPtr, IPdu->ComIPduSize);
//	}

	memcpy(IPdu->ComIPduDataPtr, PduInfoPtr->SduDataPtr, IPdu->ComIPduSize);

	Com_RxProcessSignals(ComRxPduId);

	return;
}

BufReq_ReturnType Com_StartOfReception(PduIdType id,const PduInfoType *info,PduLengthType TpSduLength,PduLengthType *bufferSizePtr)
{
	Com_Asu_IPdu_type *AsuIPdu=GET_AsuIPdu(id);
	PduLengthType ComIPduSize;

	if(GET_IPdu(id)->ComIPduDirection==RECEIVE)
	{
		//making sure that the buffer is unlocked
		if(!AsuIPdu->PduBufferState.Locked)
		{
			//getting the ipdu size
			ComIPduSize = GET_IPdu(id)->ComIPduSize;
			//making sure that we have the enough space for the sdu
			if(ComIPduSize>=TpSduLength)
			{

				///return the available buffer size
				*bufferSizePtr=ComIPduSize;
			}
			else
			{
				return BUFREQ_E_OVFL;
			}
		}
		else
		{
			return BUFREQ_E_BUSY;
		}
	}
	return BUFREQ_OK;
}



void Com_TpRxIndication(PduIdType id,Std_ReturnType Result)
{
    const ComIPdu_type *ipdu=GET_IPdu(id);
    Com_Asu_IPdu_type *AsuIPdu=GET_AsuIPdu(id);

    if (Result == E_OK)
    {
        if (ipdu->ComIPduSignalProcessing == IMMEDIATE)
        {
          UNLOCKBUFFER(&AsuIPdu->PduBufferState);

        // In deferred mode, buffers are unlocked in mainfunction
        Com_RxProcessSignals(id);
        }
    }
    else
    {
        UNLOCKBUFFER(&AsuIPdu->PduBufferState);
    }
}


void Com_TpTxConfirmation(PduIdType PduId, Std_ReturnType Result)
{
	Com_Asu_IPdu_type *AsuIPdu=GET_AsuIPdu(PduId);
	UNLOCKBUFFER(&AsuIPdu->PduBufferState);
}
