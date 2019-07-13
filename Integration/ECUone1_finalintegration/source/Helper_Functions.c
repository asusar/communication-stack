#include "include/CanTpRuntime.h"
#include <stdio.h>
#include <stdlib.h>
#include "include/CanTp_Types.h"
#include "include/CanTp_Cfg.h"
#include "include/CanTp.h"
#include "include/Helper_Functions.h"
#include "include/CanTp_Cbk.h"
#include "include/SchM_CanTp.h"
#include "include/MemMap.h"
#include "include/ComStack_Types.h"
#include "include/CanTp_CanIf.h"
#include "include/PduR_CanTp.h"
#include "include/CanIf.h"  //add by moustafa
#include  "include/PduR.h"
//#include "include/Det.h"


extern CanTp_RunTimeDataType CanTpRunTimeData;
extern CanTp_ConfigType CanTp_Config;

uint8 canif_ids[]={cantp_canif_tx};
uint8 cantp_com_copy_tx[]={CanTp_copy_cantp};
uint8 cantp_com_rx_or_copy[]= {cantp_com_rx};
uint8 cantp_cainf_FC[] ={CanTpTxFcNPdu_canif};


//BufReq_ReturnType PduR_CanTpCopyTxData(PduIdType TxPduId , PduInfoType* PduInfoPtr , uint8 Retry , PduLengthType* availableDataSize)
//{
//	static uint8 count = 0;
//	uint8 Array[] = {'M','o','h','a','m','e','d','F','a','r','a','g','i','s','g','o','o','d'};
//
//	if (count == 0)
//	{
//		PduInfoPtr->SduDataPtr = Array;
//		*availableDataSize = 18 - PduInfoPtr->SduLength ;
//	}
//
//	if (count == 1)
//	{
//		PduInfoPtr->SduDataPtr = &Array[6];
//		*availableDataSize = 12 - PduInfoPtr->SduLength ;
//
//	}
//
//	if (count == 2)
//	{
//		PduInfoPtr->SduDataPtr = &Array[13];
//		*availableDataSize = 5 - PduInfoPtr->SduLength ;
//
//	}
//
//	count++;
//	return BUFREQ_OK;
//
//}

//Std_ReturnType CanIf_TransmitForTest(PduIdType CanTxPduId,const PduInfoType* PduInfoPtr)
//{
//    CanTp_RxIndication(1,PduInfoPtr);
//
//	return E_OK;
//}

/*************************************************** Helper Functions ************************************************************/


Std_ReturnType canTansmitPaddingHelper(const CanTp_TxNSduType *txConfig, CanTp_ChannelPrivateType *txRuntime,PduInfoType *PduInfoPtr)

{
	if (txConfig->CanTpTxPaddingActivation == CANTP_ON)
	{
		uint8 i = 0;
		for (i = PduInfoPtr->SduLength; i < MAX_SEGMENT_DATA_SIZE; i++)
		{
			PduInfoPtr->SduDataPtr[i] = 0x00;
		}

		PduInfoPtr->SduLength = MAX_SEGMENT_DATA_SIZE;
	}
	txRuntime->iso15765.NasNarTimeoutCount =(txConfig->CanTpNas);
	txRuntime->iso15765.NasNarPending = TRUE;
	uint8 canif_id = canif_ids[txConfig->CanTpTxNSduId];
    return  CanIf_Transmit(canif_id, PduInfoPtr);








}



Std_ReturnType canReceivePaddingHelper(const CanTp_RxNSduType *rxConfig, CanTp_ChannelPrivateType *rxRuntime, PduInfoType *PduInfoPtr)
{
    uint8 id = cantp_cainf_FC[rxConfig->CanTpRxNSduId];
	if (rxConfig->CanTpRxPaddingActivation == CANTP_ON)
	{
		uint8 i = 0;
		for ( i = PduInfoPtr->SduLength; i < MAX_SEGMENT_DATA_SIZE; i++)
		{
			PduInfoPtr->SduDataPtr[i] = 0x0;
		}
		PduInfoPtr->SduLength = MAX_SEGMENT_DATA_SIZE;
	}
	rxRuntime->iso15765.NasNarTimeoutCount = (rxConfig->CanTpNar);  // Value in seconds of the N_Ar timeout. N_Ar is the time for transmission of a CAN frame (any N_PDU) on the receiver side.
	rxRuntime->iso15765.NasNarPending = TRUE;

//	CanTp_RxIndication(1,PduInfoPtr);                       // To Send FlowControl To Transmit ECU.
 	//return CanIf_TransmitForTest(id, PduInfoPtr);           ///////////////////////////////////////////////////////////
 	 return  CanIf_Transmit(id, PduInfoPtr);
	//return E_OK;
}

/*
 * This function copies the segment to PduR Receiving Buffer, requests a new buffer from the SDUR if needed,
 * and reports the error to the Development Error Tracer (DET).
 *-3
 * Function Name: copySegmentToPduRRxBuffer
 * Parameters:
 * 				Inputs: 5
 *
 * 					1.	Name: *rxConfig
 * 						Type: CanTp_RxNSduType
 * 						Description: pointer to a structure contains the configurations of RX.
 *
 * 					2.	Name: *rxRuntime
 * 						Type: CanTp_ChannelPrivateType
 * 						Description: pointer to a structure contains the runtime parameters of RX.
 *
 * 					3.	Name: *segment
 * 						Type: uint8
 * 						Description: pointer to the segment or the data to be copied.
 *
 * 					4.	Name: segmentSize
 * 						Type: PduLengthType
 * 						Description: length of the Pdu.
 *
 * 					5.	Name: *bytesWrittenSuccessfully
 * 						Type: PduLengthType
 * 						Description: length of bytes written successfully.
 *
 *
 * 				Returns:
 *						BufReq_ReturnType:  BUFREQ_OK         0
 *	  								   		BUFREQ_E_NOT_OK     1
 *	  								   		BUFREQ_E_BUSY       2
 *	  								   		BUFREQ_E_OVFL       3
 *
 */

//ret = copySegmentToPduRRxBuffer(rxConfig, rxRuntime, data, pduLength, &bytesWrittenToSduRBuffer);

BufReq_ReturnType copySegmentToPduRRxBuffer(   const CanTp_RxNSduType *rxConfig,
													CanTp_ChannelPrivateType *rxRuntime,
																PduInfoType *info        // { Data , length }
																)

{

	BufReq_ReturnType return_value = BUFREQ_OK;
	uint8 id = cantp_com_rx_or_copy[rxConfig->CanTpRxNSduId] ;  //


		/* copy the data in the buffer as long as loop there`s a room for copying */

	if (rxRuntime->Buffersize == 0)          /* in case of SF and FF only */
	{

		return_value = PduR_CanTpStartOfReception(id,info,rxRuntime->transferTotal,&rxRuntime->Buffersize); //
	}

		/* return form  PduR_CanTpStartOfReception */

		if (return_value == BUFREQ_OK)
		{

			return_value = PduR_CanTpCopyRxData(id,info,&rxRuntime->Buffersize); //

		}

		else if (return_value == BUFREQ_E_BUSY)
		{

		}

		else	 /* in case of BUFREQ_E_NOT_OK or BUFREQ_E_OVFL */
		{

		}

	return return_value;
}

/* this function coping data and length to Rx_runtime.canFrameBufferData if segementsize < MAX_SEGMENT_DATA_SIZE and return True if copying Done */
boolean copySegmentToLocalRxBuffer(CanTp_ChannelPrivateType *rxRuntime, uint8 *segment,PduLengthType segmentSize)
{
	boolean ret = FALSE;

	if ( segmentSize < MAX_SEGMENT_DATA_SIZE )
	{
		uint8 i;
		/*This for loop copying the Data to local Buffer*/
		for (i=0; i < segmentSize; i++)
		{
			rxRuntime->canFrameBuffer.data[i] = segment[i];              // segment is data
		}

		rxRuntime->canFrameBuffer.byteCount = segmentSize;              // copy Length To The local Buffer
		ret = TRUE;
	}
	return ret;			/* return True if copying is Done as the size is small than MAX_SEGMENT_DATA_SIZE */
}

/* This Function get The Frame Type { SF,FF,CF,CTS_FC,WAIT_FC,OVERFLOW_FC } */

ISO15765FrameType getFrameType(const CanTp_AddressingFormatType *formatType,const PduInfoType *CanTpRxPduPtr)
{
	ISO15765FrameType res = INVALID_FRAME;
	uint8 tpci = 0;

	switch (*formatType)
	{
	case CANTP_STANDARD:
		tpci = CanTpRxPduPtr->SduDataPtr[0];
		break;

	case CANTP_EXTENDED:
		tpci = CanTpRxPduPtr->SduDataPtr[1];
		break;

	default:
		break;
	}

	switch (tpci & ISO15765_TPCI_MASK)
	{
	case ISO15765_TPCI_SF:
		res = SINGLE_FRAME;
		break;
	case ISO15765_TPCI_FF:
		res = FIRST_FRAME;
		break;
	case ISO15765_TPCI_CF:
		res = CONSECUTIVE_FRAME;
		break;

	case ISO15765_TPCI_FC: 						/* check which kind of flow control. */
		switch (tpci & ISO15765_TPCI_FS_MASK)
		{
		case ISO15765_FLOW_CONTROL_STATUS_CTS:
			res = FLOW_CONTROL_CTS_FRAME;
			break;
		case ISO15765_FLOW_CONTROL_STATUS_WAIT:
			res = FLOW_CONTROL_WAIT_FRAME;
			break;
		case ISO15765_FLOW_CONTROL_STATUS_OVFLW:
			res = FLOW_CONTROL_OVERFLOW_FRAME;
			break;
		}
	}
	return res;
}

/* This Fuction is used to get the length of the PDU from N_PCI */
PduLengthType getPduLength(const CanTp_AddressingFormatType *formatType,const ISO15765FrameType iso15765Frame, const PduInfoType *CanTpRxPduPtr)
{
	PduLengthType res = 0;
	uint8 tpci_offset = 0;


	 /* to check the format type */
	switch (*formatType)
	{
	case CANTP_STANDARD:
		tpci_offset = 0;
		break;
	case CANTP_EXTENDED:
		tpci_offset = 1;
		break;
	default:
		return 0;
	}

	switch (iso15765Frame)
	{
	case SINGLE_FRAME:
		// Parse the data length from the single frame header.
		res = CanTpRxPduPtr->SduDataPtr[tpci_offset] & ISO15765_TPCI_DL;
		break;
	case FIRST_FRAME:
		// Parse the data length form the first frame.
		res = CanTpRxPduPtr->SduDataPtr[tpci_offset + 1] + ((PduLengthType)((CanTpRxPduPtr->SduDataPtr[tpci_offset]) & 0xf) << 8);
		break;
	default:
		res = 0;
		break;
	}
	return res;
}


/* This function returns either it SF or FF */
ISO15765FrameType calcRequiredProtocolFrameType(const CanTp_TxNSduType *txConfig, CanTp_ChannelPrivateType *txRuntime)
{

	ISO15765FrameType ret = INVALID_FRAME;

	if (txConfig->CanTpTxAddressingFormat == CANTP_EXTENDED)
	{
		if (txRuntime->transferTotal <= MAX_PAYLOAD_CF_EXT_ADDR)
		{
			ret = SINGLE_FRAME;
		}
		else
		{
			if (txConfig->CanTpTxTaType == CANTP_PHYSICAL)
			{
				ret = FIRST_FRAME;
			}
			else
			{
			}
		}
	}

	else 					// in case of  CANTP_STANDARD
	{
		if (txRuntime->transferTotal <= MAX_PAYLOAD_CF_STD_ADDR)
		{
			ret = SINGLE_FRAME;
		}
		else
		{
			if (txConfig->CanTpTxTaType == CANTP_PHYSICAL)
			{
				ret = FIRST_FRAME;
			}
			else
			{
			}
		}
	}

	return ret;
}

/*************************************************** Handling All Frames ************************************************************/

void handleSingleFrame(const CanTp_RxNSduType *rxConfig,CanTp_ChannelPrivateType *rxRuntime, const PduInfoType *rxPduData)
{
	BufReq_ReturnType ret;
	PduLengthType pduLength;
	PduInfoType *info = NULL;
	uint8 * data = rxPduData->SduDataPtr;



	if (rxRuntime->iso15765.state != IDLE)
	{
		PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_E_NOT_OK);  // Abort current reception, we need to tell the current receiver it has been aborted.
	}

	initRx15765RuntimeData(rxRuntime);           // i think this line is useless
	pduLength = getPduLength(&rxConfig->CanTpRxAddressingFormat, SINGLE_FRAME, rxPduData);



	if (rxConfig->CanTpRxAddressingFormat == CANTP_STANDARD)
	{
		info->SduDataPtr = &rxPduData->SduDataPtr[1];
	}
	else								/* in case of Extended Addressing format */
	{
		info->SduDataPtr = &rxPduData->SduDataPtr[2];
	}

	rxRuntime->transferTotal = pduLength;                /* copying length to runtime */
	rxRuntime->iso15765.state = SF_OR_FF_RECEIVED_WAITING_PDUR_BUFFER;
	rxRuntime->mode = CANTP_RX_PROCESSING;
	rxRuntime->iso15765.stateTimeoutCount = (rxConfig->CanTpNbr);

	ret = copySegmentToPduRRxBuffer(rxConfig, rxRuntime, info);

	if (ret == BUFREQ_OK)
	{
		PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_OK);
		rxRuntime->iso15765.state = IDLE;
		rxRuntime->mode = CANTP_RX_WAIT;

	}
	else if (ret == BUFREQ_E_BUSY)
	{
		if (rxConfig->CanTpRxAddressingFormat == CANTP_STANDARD)
		{
			data = &rxPduData->SduDataPtr[1];
		}
		else
		{
			data = &rxPduData->SduDataPtr[2];
		}
		(void)copySegmentToLocalRxBuffer(rxRuntime, data, pduLength ); 			   /* copy data to local buffer in case of BUFREQ_E_BUSY */

		rxRuntime->iso15765.state = RX_WAIT_SDU_BUFFER;
		rxRuntime->mode = CANTP_RX_PROCESSING;
	}

	else      /* in case of BUFREQ_E_NOT_OK or BUFREQ_E_OVFL */
	{
		PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_E_NO_BUFFER);
		rxRuntime->iso15765.state = IDLE;
		rxRuntime->mode = CANTP_RX_WAIT;
	}
}


void handleFirstFrame(const CanTp_RxNSduType *rxConfig,CanTp_ChannelPrivateType *rxRuntime, const PduInfoType *rxPduData)
{
	BufReq_ReturnType ret;
	PduLengthType pduLength;
	PduInfoType *info = rxPduData;


	if (rxRuntime->iso15765.state != IDLE)
	{
		PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_E_NOT_OK); // Abort current reception, we need to tell the current receiver it has been aborted.
	}

	(void) initRx15765RuntimeData(rxRuntime);                         /* I think this line is useless */
	pduLength = getPduLength(&rxConfig->CanTpRxAddressingFormat, FIRST_FRAME,rxPduData);
	rxRuntime->transferTotal = pduLength;




	// Validate that that there is a reason for using the segmented transfers and
	// if not simply skip (single frame should have been used).
	if (rxConfig->CanTpRxAddressingFormat == CANTP_STANDARD)
	{
		if (pduLength <= MAX_PAYLOAD_SF_STD_ADDR)
		{
			return;
		}
	}
	else
	{
		if (pduLength <= MAX_PAYLOAD_SF_EXT_ADDR)
		{
			return;
		}
	}

	// Validate that the SDU is full length in this first frame.
	if (rxPduData->SduLength < MAX_SEGMENT_DATA_SIZE)
	{
		return;
	}

	/* point the data to correct byte  */

	if (rxConfig->CanTpRxAddressingFormat == CANTP_STANDARD)
	{
		info->SduDataPtr = &rxPduData->SduDataPtr[2];
	}
	else								/* in case of Extended Addressing format */
	{
		info->SduDataPtr = &rxPduData->SduDataPtr[3];
	}

	info->SduLength = info->SduLength - 2 ;

	rxRuntime->iso15765.framesHandledCount = 1;			 // Segment count begins with 1 (FirstFrame has the 0).
	rxRuntime->iso15765.state = SF_OR_FF_RECEIVED_WAITING_PDUR_BUFFER;
	rxRuntime->mode = CANTP_RX_PROCESSING;
	rxRuntime->iso15765.stateTimeoutCount = (rxConfig->CanTpNbr);


	ret = copySegmentToPduRRxBuffer(rxConfig, rxRuntime,info);



	if (ret == BUFREQ_OK)
	{
		rxRuntime->iso15765.stateTimeoutCount = (rxConfig->CanTpNcr); // Value in seconds of the N_Cr timeout. N_Cr is the time until reception of the next Consecutive Frame N_PDU.
		rxRuntime->iso15765.state = RX_WAIT_CONSECUTIVE_FRAME;
		rxRuntime->mode = CANTP_RX_PROCESSING;
		sendFlowControlFrame(rxConfig, rxRuntime, ret);
	}

	else if (ret == BUFREQ_E_BUSY)
	{
		if (rxConfig->CanTpRxAddressingFormat == CANTP_STANDARD)
		{
			(void)copySegmentToLocalRxBuffer(rxRuntime, &rxPduData->SduDataPtr[2], MAX_PAYLOAD_FF_STD_ADDR );
		}
		else
		{
			(void)copySegmentToLocalRxBuffer(rxRuntime, &rxPduData->SduDataPtr[3], MAX_PAYLOAD_FF_EXT_ADDR );
		}
		rxRuntime->iso15765.stateTimeoutCount = (rxConfig->CanTpNbr);
		rxRuntime->iso15765.state = RX_WAIT_SDU_BUFFER;
		rxRuntime->mode = CANTP_RX_PROCESSING;
		sendFlowControlFrame(rxConfig, rxRuntime, ret);
	}
	else if (ret == BUFREQ_E_OVFL)
	{
		sendFlowControlFrame(rxConfig, rxRuntime, ret);
		rxRuntime->iso15765.state = IDLE;
		rxRuntime->mode = CANTP_RX_WAIT;
	}
}



void handleFlowControlFrame(const CanTp_TxNSduType *txConfig,CanTp_ChannelPrivateType *txRuntime, const PduInfoType *txPduData)
{

	uint8 indexCount = 0;             // Farag change this from int to uint8

	CanTp_TxConfirmation(1,0);       // added for testing only


	if ( txRuntime->iso15765.state == TX_WAIT_FLOW_CONTROL )
	{
		if (txConfig->CanTpTxAddressingFormat == CANTP_EXTENDED)
		{
			indexCount++;
		}

		// txPduData->SduDataPtr[indexCount++] = 1st byte (frame type + flow control flag)
		switch (txPduData->SduDataPtr[indexCount++] & ISO15765_TPCI_FS_MASK) // checking the flow control flag (Clear To Send=0 , Wait=1, Overflow/abort =2)
		{
		uint8 bs;
		case ISO15765_FLOW_CONTROL_STATUS_CTS:

			bs = txPduData->SduDataPtr[indexCount++];        		  // parsing BS from PduData
			txRuntime->iso15765.BS = bs;
			txRuntime->iso15765.nextFlowControlCount = bs;

			txRuntime->iso15765.STmin = txPduData->SduDataPtr[indexCount++];	 // parsing STmin from PduData and Putting it in runtime


			// change state and setup timeout
			txRuntime->iso15765.stateTimeoutCount = (txConfig->CanTpNcs);
			txRuntime->iso15765.state = TX_WAIT_TRANSMIT;
			break;

		case ISO15765_FLOW_CONTROL_STATUS_WAIT:
			txRuntime->iso15765.stateTimeoutCount = (txConfig->CanTpNbs);
			txRuntime->iso15765.state = TX_WAIT_FLOW_CONTROL;
			break;

		case ISO15765_FLOW_CONTROL_STATUS_OVFLW:
			//PduR_CanTpRxIndication(txConfig->CanTpRxFcNPdu.CanTpRxFcNPduId, NTFRSLT_E_NOT_OK);       // 27na benehbed ,,,, PduR_PduID
			txRuntime->iso15765.state = IDLE;
			txRuntime->mode = CANTP_TX_WAIT;
			break;
		}
	}
}

/* TODO: this fuction requires a lot of change.   Done ! */
void handleConsecutiveFrame(const CanTp_RxNSduType *rxConfig,CanTp_ChannelPrivateType *rxRuntime, const PduInfoType *rxPduData)
{
	uint8 indexCount = 0;
	uint8 segmentNumber = 0;
	PduLengthType currentSegmentSize = 0;
	PduLengthType bytesCopiedToPdurRxBuffer = 0;
	BufReq_ReturnType ret = BUFREQ_E_NOT_OK;

	PduInfoType *info = rxPduData;


	if (rxRuntime->iso15765.state == RX_WAIT_CONSECUTIVE_FRAME)
	{
		if (rxConfig->CanTpRxAddressingFormat == CANTP_EXTENDED)
		{
		indexCount++;
		}

		// getting consecutive frame number
		segmentNumber = rxPduData->SduDataPtr[indexCount++] & SEGMENT_NUMBER_MASK;      //	segment number equals consecutive frame index (3..0 bits in first byte)

		// checking if this consecutive frame is handled
		if (segmentNumber != (rxRuntime->iso15765.framesHandledCount & SEGMENT_NUMBER_MASK))
		{
			PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_E_WRONG_SN);
			rxRuntime->iso15765.state = IDLE;
			rxRuntime->mode = CANTP_RX_WAIT;
		}

		else
		{

			// Copy received data to buffer provided by SDUR.
			info->SduDataPtr = &rxPduData->SduDataPtr[indexCount];

			info->SduLength = info->SduLength - 1;

			ret = copySegmentToPduRRxBuffer(rxConfig, rxRuntime,info);

			if (ret == BUFREQ_E_NOT_OK)
			{
				PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_E_NO_BUFFER);
				rxRuntime->iso15765.state = IDLE;
				rxRuntime->mode = CANTP_RX_WAIT;
			}

			else if (ret == BUFREQ_E_BUSY)           // Not handled Yet
			{
				boolean dataCopyFailure = FALSE;
				PduLengthType bytesNotCopiedToPdurRxBuffer = currentSegmentSize - bytesCopiedToPdurRxBuffer;

				// checking copy failure
				if (rxConfig->CanTpRxAddressingFormat == CANTP_STANDARD)
				{
					if ( copySegmentToLocalRxBuffer(rxRuntime,	&rxPduData->SduDataPtr[1 + bytesCopiedToPdurRxBuffer],bytesNotCopiedToPdurRxBuffer ) != TRUE )
					{
						rxRuntime->iso15765.state = IDLE;
						rxRuntime->mode = CANTP_RX_WAIT;
						dataCopyFailure = TRUE;
					}

				}
				else    // in extended add.
				{
					if ( copySegmentToLocalRxBuffer(rxRuntime,&rxPduData->SduDataPtr[2 + bytesCopiedToPdurRxBuffer],bytesNotCopiedToPdurRxBuffer) != TRUE )
					{
						rxRuntime->iso15765.state = IDLE;
						rxRuntime->mode = CANTP_RX_WAIT;
						dataCopyFailure = TRUE;
					}
				}

				if ( !dataCopyFailure )             // Data is copied correctly
				{
					rxRuntime->iso15765.framesHandledCount++;
					rxRuntime->iso15765.stateTimeoutCount = (rxConfig->CanTpNbr);
					rxRuntime->iso15765.state = RX_WAIT_SDU_BUFFER;
					rxRuntime->mode = CANTP_RX_PROCESSING;
					sendFlowControlFrame(rxConfig, rxRuntime, ret);
				}
			}

			else if (ret == BUFREQ_OK)
			{
				if (rxRuntime->Buffersize > 0)
				{
					rxRuntime->iso15765.framesHandledCount++;                 	  // hanzawed 3adad el frames elly 2tna2alet
					COUNT_DECREMENT(rxRuntime->iso15765.nextFlowControlCount); 	  // han2alel 3adad el frames elly fadla 3ala  el next flow control

					/* Now You should send the next flow control if the conditions is True */
					if (rxRuntime->iso15765.nextFlowControlCount == 0  && rxRuntime->iso15765.BS > 0)
					{
						sendFlowControlFrame(rxConfig, rxRuntime, BUFREQ_OK);
					}
					else
					{
						rxRuntime->iso15765.stateTimeoutCount = (rxConfig->CanTpNcr);  // Value in seconds of the N_Cr timeout. N_Cr is the time until reception of the next Consecutive Frame N_PDU.
					}
				}

				else		// rxRuntime.BufferSize == 0 ------>   received all PDU.
				{
					rxRuntime->iso15765.state = IDLE;
					rxRuntime->mode = CANTP_RX_WAIT;
					PduR_CanTpRxIndication(/*rxConfig->CanTpRxNPdu.CanTpRxNPduId*/1, NTFRSLT_OK);
				}
			}
		}
	}
}


void handleNextTxFrameSent(const CanTp_TxNSduType *txConfig, CanTp_ChannelPrivateType *txRuntime)
{
	txRuntime->iso15765.framesHandledCount++;

	// prepare TX buffer for next frame
	txRuntime->canFrameBuffer.byteCount = 0;

	if (txConfig->CanTpTxAddressingFormat == CANTP_EXTENDED)           /* for Extended */
	{
		txRuntime->canFrameBuffer.byteCount++;
	}

	// To prepare First byte in CF
	txRuntime->canFrameBuffer.data[txRuntime->canFrameBuffer.byteCount++] = (txRuntime->iso15765.framesHandledCount & SEGMENT_NUMBER_MASK) + ISO15765_TPCI_CF;


	COUNT_DECREMENT(txRuntime->iso15765.nextFlowControlCount);

	if (txRuntime->transferTotal <= txRuntime->transferCount)
	{
		// Transfer finished!
		PduR_CanTpTxConfirmation(cantp_com_copy_tx[txConfig->CanTpTxNSduId], E_OK);
		txRuntime->iso15765.state = IDLE;
		txRuntime->mode = CANTP_TX_WAIT;
	}

	else if (txRuntime->iso15765.nextFlowControlCount == 0 && txRuntime->iso15765.BS)
	{
		// TX ECU expects flow control.
		txRuntime->iso15765.stateTimeoutCount = (txConfig->CanTpNbs);
		txRuntime->iso15765.state = TX_WAIT_FLOW_CONTROL;

	}

	else if (txRuntime->iso15765.STmin == 0)
	{
		// Send next consecutive frame!
		Std_ReturnType resp;
		resp = sendNextTxFrame(txConfig, txRuntime);
		if (resp == BUFREQ_OK )
		{
			// successfully sent frame, wait for TX confirm
		} else if(BUFREQ_E_BUSY == resp)
		{
			// change state and setup timeout
			txRuntime->iso15765.stateTimeoutCount = (txConfig->CanTpNcs);
			txRuntime->iso15765.state = TX_WAIT_TRANSMIT;
		}
		else
		{
			PduR_CanTpTxConfirmation(cantp_com_copy_tx[txConfig->CanTpTxNSduId], E_NOT_OK);
			txRuntime->iso15765.state = IDLE;
			txRuntime->mode = CANTP_TX_WAIT;
		}
	}
	else
	{
		// Send next consecutive frame after stmin!
		//ST MIN error handling ISO 15765-2 sec 7.6
		if (txRuntime->iso15765.STmin < 0x80)
		{
			txRuntime->iso15765.stateTimeoutCount = (txRuntime->iso15765.STmin) + 1;
		}
		else if (txRuntime->iso15765.STmin > 0xF0 && txRuntime->iso15765.STmin < 0xFA)
		{
			txRuntime->iso15765.stateTimeoutCount = 1; //0.1 ms resoultion needs a lower task period. So hard coded to 1 main cycle
		}
		else
		{
			txRuntime->iso15765.stateTimeoutCount = (0x7F) + 1;
		}
		txRuntime->iso15765.state = TX_WAIT_STMIN;
	}
}

/****************************************************** sending  Frames **************************************************************/

/* this function for sending the flow control */
void sendFlowControlFrame(const CanTp_RxNSduType *rxConfig, CanTp_ChannelPrivateType *rxRuntime, BufReq_ReturnType flowStatus)
{

	uint8 indexCount = 0;
	Std_ReturnType ret = E_NOT_OK;
	PduInfoType pduInfo;
	uint8 sduData[8];				  		  // Note that buffer is declared on the stack.   dah fe moskla any awl lma a5rg mn al fn hytms7
	uint16 computedBs = 0;

	pduInfo.SduDataPtr = &sduData[0];         // make pointer points to array of data


	if (rxConfig->CanTpRxAddressingFormat == CANTP_EXTENDED)
	{
		sduData[indexCount++] = rxRuntime->iso15765.extendedAddress;
	}

	switch (flowStatus)
	{
	case BUFREQ_OK:
	{
		sduData[indexCount++] = ISO15765_TPCI_FC | ISO15765_FLOW_CONTROL_STATUS_CTS;        	// change the value of control flag (clear to send)


		if (rxConfig->CanTpRxAddressingFormat == CANTP_EXTENDED)                         // for Extended
		{
			computedBs = (rxRuntime->Buffersize	 / MAX_PAYLOAD_SF_EXT_ADDR) + 1;
		}
		else																			// for standard
		{
			computedBs = (rxRuntime->Buffersize	 / MAX_PAYLOAD_SF_STD_ADDR) + 1;
		}

		if (computedBs > rxConfig->CanTpBs)               /* we can't excced the maximum value (not sure yet)*/
		{
			computedBs = rxConfig->CanTpBs;
		}

		sduData[indexCount++] = computedBs;                                     // putting BlockSize in the Byte #2
		sduData[indexCount++] = (uint8) rxConfig->CanTpSTmin;				    // putting   STmin   in the Byte #3

		rxRuntime->iso15765.nextFlowControlCount = computedBs;
		pduInfo.SduLength = indexCount;                           	  // indexcount here = 3
		break;
	}

	case BUFREQ_E_NOT_OK:
		break;

	case BUFREQ_E_BUSY:
		sduData[indexCount++] = ISO15765_TPCI_FC | ISO15765_FLOW_CONTROL_STATUS_WAIT;         // change the value of control flag (wait)
		indexCount +=2;
		pduInfo.SduLength = indexCount;								  // indexcount here = 3
		break;

	case BUFREQ_E_OVFL:
		sduData[indexCount++] = ISO15765_TPCI_FC | ISO15765_FLOW_CONTROL_STATUS_OVFLW;		  // change the value of control flag (overflow)
		indexCount +=2;
		pduInfo.SduLength = indexCount;								 // indexcount here = 3
		break;

	default:
		break;
	}


	ret = canReceivePaddingHelper(rxConfig, rxRuntime, &pduInfo);       // pduinfo contains pointer to data and data length

	if (ret != E_OK)
	{
		//PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_E_NOT_OK);
		rxRuntime->iso15765.state = IDLE;
		rxRuntime->mode = CANTP_RX_WAIT;
	}
}


/*This fuction copies Data from pdurBuffer to CanFrameBuffer */
BufReq_ReturnType sendNextTxFrame(const CanTp_TxNSduType *txConfig, CanTp_ChannelPrivateType *txRuntime)
{
	BufReq_ReturnType ret = BUFREQ_OK;

	uint8 Retry = 0;
	txRuntime->pdurBuffer.SduDataPtr = & (txRuntime->canFrameBuffer.data[txRuntime->canFrameBuffer.byteCount]);

	// copy data to temp buffer  ,, i will edit it to make copying in com instead of CanTp
//	for(; txRuntime->canFrameBuffer.byteCount < MAX_SEGMENT_DATA_SIZE && ret == BUFREQ_OK ;)
//	{

			/* al if de bthandle lw fe mshakel */
//		if(txRuntime->pdurBuffer.SduDataPtr == NULL || txRuntime->pdurBufferCount == txRuntime->pdurBuffer.SduLength)   /*second condition is: pdurBufferCount == SduLength */
//		{
			// a3tkd bardo an lw awl condtion at722 yb2a dah SF or FF ,Lakn lw tany condtion ally at772 yb2a CF .. w mn hna mmkn 2fr2 benhom
			// data empty, request new data
//			txRuntime->pdurBufferCount = 0;

			if (txRuntime->availableDataSize == 0)           /* in case of SF or FF */
			{
				ret = PduR_CanTpCopyTxData(cantp_com_copy_tx[txConfig->CanTpTxNSduId],&txRuntime->pdurBuffer,Retry,&txRuntime->availableDataSize);
                txRuntime->transferCount += txRuntime->pdurBuffer.SduLength;

			}

			else if (txConfig->CanTpTxAddressingFormat == CANTP_STANDARD)          /* in case of standard */
			{
				if (txRuntime->availableDataSize > MAX_PAYLOAD_CF_STD_ADDR)	     /* in case of Full CF */
				{
					txRuntime->pdurBuffer.SduLength = MAX_PAYLOAD_SF_STD_ADDR;
					ret = PduR_CanTpCopyTxData(cantp_com_copy_tx[txConfig->CanTpTxNSduId],&txRuntime->pdurBuffer,Retry,&txRuntime->availableDataSize);
			//		txRuntime->canFrameBuffer.byteCount = txRuntime->pdurBuffer.SduLength + 1;
                    txRuntime->transferCount += txRuntime->pdurBuffer.SduLength;


				}

				else if (txRuntime->availableDataSize <= MAX_PAYLOAD_CF_STD_ADDR)	/* in case of Last CF */
				{
					txRuntime->pdurBuffer.SduLength = txRuntime->availableDataSize;
					ret = PduR_CanTpCopyTxData(cantp_com_copy_tx[txConfig->CanTpTxNSduId],&txRuntime->pdurBuffer,Retry,&txRuntime->availableDataSize);
           //       txRuntime->canFrameBuffer.byteCount = txRuntime->pdurBuffer.SduLength + 1;
                    txRuntime->transferCount += txRuntime->pdurBuffer.SduLength;


				}

			}


			else			  /* in case of Extended */
			{
				if (txRuntime->availableDataSize > MAX_PAYLOAD_SF_STD_ADDR)	     /* in case of Full CF */
				{
					txRuntime->pdurBuffer.SduLength = MAX_PAYLOAD_SF_STD_ADDR;
					ret = PduR_CanTpCopyTxData(txConfig->CanTpTxNSduId,&txRuntime->pdurBuffer,Retry,&txRuntime->availableDataSize);
				}

				else if (txRuntime->availableDataSize <= MAX_PAYLOAD_SF_STD_ADDR)	/* in case of Last CF */
				{
					txRuntime->pdurBuffer.SduLength = txRuntime->availableDataSize;
					ret = PduR_CanTpCopyTxData(txConfig->CanTpTxNSduId,&txRuntime->pdurBuffer,Retry,&txRuntime->availableDataSize);
				}
			}


//		}       // end of if condition



			if(ret == BUFREQ_OK)
			{
				// new data received
			}
			else
			{
				// failed to receive new data
//				txRuntime->pdurBuffer.SduDataPtr = NULL;

			}

			txRuntime->canFrameBuffer.byteCount += txRuntime->pdurBuffer.SduLength;   // Updating bytecount


//		 /* copying Data from pdurBuffer to canFrameBuffer and all in runtime */
//		txRuntime->canFrameBuffer.data[txRuntime->canFrameBuffer.byteCount++] =
//																				txRuntime->pdurBuffer.SduDataPtr[txRuntime->pdurBufferCount++];
//

//		txRuntime->transferCount++;            /* increase the transfer count */

//		if(txRuntime->transferCount == txRuntime->transferTotal)     /* for small bytes so the condition break here */
//		 {
//			// all bytes, send
//			break;
//
//
//		 }
//	}



// here company handle Tx_Confirmation and we don't need this right Now
 	if(ret == BUFREQ_OK)
	{
 		PduInfoType pduInfo;                // hna fe moskla ane dah hytms7
		Std_ReturnType resp;
		pduInfo.SduDataPtr = txRuntime->canFrameBuffer.data;
		pduInfo.SduLength = txRuntime->canFrameBuffer.byteCount;

		// change state to verify tx confirm within timeout
		txRuntime->iso15765.stateTimeoutCount = (txConfig->CanTpNas);
		txRuntime->iso15765.state = TX_WAIT_TX_CONFIRMATION;


		resp = canTansmitPaddingHelper(txConfig, txRuntime, &pduInfo);
		if(resp == E_OK)
		{
			// sending done
		}
		else
		{
			// failed to send
			ret = BUFREQ_E_NOT_OK;
		}
	}

 	return ret;
}

