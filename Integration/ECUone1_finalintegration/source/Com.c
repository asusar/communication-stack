 /***************************************************
 *
 * File Name: Com.c 
 *
 * Author: AUTOSAR COM Team
 * 
 * Date Created: 6 MAsuh 2019
 * 
 * Version	: 01	
 * 
 ****************************************************/
#include "include/Com.h"
#include "include/Com_Types.h"
#include "include/Com_helper.h"
#include "include/Com_Buffer.h"
#include "include/Com_Asu_Types.h"
#include "include/PduR_Com.h"
#include "include/Com_Cbk.h"

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
	Com_Asu_IPdu_type *Asu_IPdu = NULL;
	uint16 signalID;
	boolean pduUpdated = FALSE;

    /* Loop on IPDUs */
	uint16 pduId;
	for ( pduId = 0; pduId < COM_NUM_OF_IPDU; pduId++)
	{
		IPdu = GET_IPdu(pduId);
		Asu_IPdu = GET_AsuIPdu(pduId);

		for (signalID = 0; (IPdu->ComIPduSignalRef != NULL) && (IPdu->ComIPduSignalRef[signalID] != NULL); signalID++)
		{
            if (Asu_Signal->ComSignalUpdated)
            {
                pduUpdated = TRUE;
            }
		}

		if (pduUpdated && IPdu->ComIPduSignalProcessing == DEFERRED && IPdu->ComIPduDirection == RECEIVE && IPdu->ComIPduType == NORMAL)
		{
		    /* unlock the buffer */
		    UNLOCKBUFFER(&Asu_IPdu->PduBufferState)

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
	const ComIPdu_type *IPdu;
	Com_Asu_IPdu_type *Asu_IPdu;
	boolean mixed_t;
	boolean mixedSent;

	//Loop on IPDUs
	uint16 pduId;
	for ( pduId = 0; pduId<COM_NUM_OF_IPDU; pduId++)
	{
		IPdu = GET_IPdu(pduId);
		Asu_IPdu = GET_AsuIPdu(pduId);


		/* if it is a send PDU*/
		if(IPdu->ComIPduDirection == SEND)
		{
			mixed_t = FALSE;

			switch(IPdu->ComTxIPdu.ComTxModeFalse.ComTxMode.ComTxModeMode)
			{
			/* if the transmission mode is mixed */
			case MIXED:
				mixed_t = TRUE;
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
				if(!mixed_t)/* in case the Pdu is mixed don't break */
					break;
			/* if the transmission mode is direct */
			case DIRECT:
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


	/* Set the update bit of this signal */
	SETBIT(IPdu->ComIPduDataPtr, Signal->ComUpdateBitPosition);
	uint8 x;
	uint8 i;
    for ( i =0; i<8; i++)
    {
        x = *(uint8 *)((uint8 *)IPdu->ComIPduDataPtr + i);
    }

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

	/* check ipdu direction is receive */
	if(IPdu->ComIPduDirection == RECEIVE)
	{
		  Com_ReadSignalDataFromSignalBuffer(SignalId, SignalDataPtr);
	}
	else
	{
		return E_NOT_OK;
	}
    return E_OK;
}

BufReq_ReturnType Com_CopyTxData( PduIdType id, const PduInfoType* info, const RetryInfoType* retry, PduLengthType* availableDataPtr )
{
    ComIPdu_type *IPdu = GET_IPdu(id);
    Com_Asu_IPdu_type *Asu_IPdu = GET_AsuIPdu(id);

    if( (IPdu->ComIPduDirection == SEND) &&
            (Asu_IPdu->PduBufferState.CurrentPosition + info->SduLength <= IPdu->ComIPduSize) )
    {
        void * source = (uint8*)IPdu->ComIPduDataPtr + Asu_IPdu->PduBufferState.CurrentPosition;
        LOCKBUFFER(&Asu_IPdu->PduBufferState);
        memcpy( (void*) info->SduDataPtr, source, info->SduLength);
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
				Asu_IPdu->PduBufferState.Locked)
    {
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
	uint8 i;
	uint8 x;
	for ( i =0; i<PduInfoPackage.SduLength; i++)
	{
	    x = *(uint8 *)((uint8 *)PduInfoPackage.SduDataPtr + i);
	}

	if (Asu_IPdu->PduBufferState.Locked)
	{
		return E_NOT_OK;
	}

	if (PduR_ComTransmit(com_pdur[IPdu->ComIPduHandleId], &PduInfoPackage) == E_OK)
	{
		// Clear all update bits for the contained signals
	    if(IPdu->ComTxIPdu.ComTxIPduClearUpdateBit == TRANSMIT)
	    {
            for ( signalID = 0; (IPdu->ComIPduSignalRef[signalID] != NULL); signalID++)
            {
                CLEARBIT(IPdu->ComIPduDataPtr, IPdu->ComIPduSignalRef[signalID]->ComUpdateBitPosition);
            }
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

	memcpy(IPdu->ComIPduDataPtr, PduInfoPtr->SduDataPtr, IPdu->ComIPduSize);

	Com_RxProcessSignals(ComRxPduId);

	return;
}

BufReq_ReturnType Com_StartOfReception(PduIdType id,const PduInfoType *info,PduLengthType TpSduLength,PduLengthType *bufferSizePtr)
{
	Com_Asu_IPdu_type *AsuIPdu=GET_AsuIPdu(id);
	PduLengthType ComIPduSize;

	if(GET_IPdu(id)->ComIPduDirection==RECEIVE && GET_IPdu(id)->ComIPduType == TP)
	{
		//making sure that the buffer is unlocked
		if(!AsuIPdu->PduBufferState.Locked)
		{
			//getting the ipdu size
			ComIPduSize = GET_IPdu(id)->ComIPduSize;
			//making sure that we have the enough space for the sdu
			if(ComIPduSize>=TpSduLength)
			{
				//lock the buffer until copying is done
				LOCKBUFFER(&AsuIPdu->PduBufferState);
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
		return BUFREQ_OK;
	}
	return BUFREQ_E_NOT_OK;
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
    uint8 signalId;
    ComSignal_type * signal = NULL;
    ComIPdu_type *ipdu=GET_IPdu(PduId);
	Com_Asu_IPdu_type *AsuIPdu=GET_AsuIPdu(PduId);

	UNLOCKBUFFER(&AsuIPdu->PduBufferState);

	if (ipdu->ComTxIPdu.ComTxIPduClearUpdateBit == CONFIRMATION)
	{
        for(signalId = 0; (ipdu->ComIPduSignalRef != NULL) && (ipdu->ComIPduSignalRef[signalId] != NULL) ; signalId++)
        {
            signal = ipdu->ComIPduSignalRef[signalId];
            CLEARBIT(ipdu->ComIPduDataPtr,signal->ComUpdateBitPosition);
        }
	}
}
