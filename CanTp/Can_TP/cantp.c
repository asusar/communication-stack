#include "CanTp_Cfg.h"
#include "CanTp.h"
#include "CanTp_Types.h"
#include "CanTp_Cbk.h"
#include "SchM_CanTp.h"
#include "MemMap.h"
#include "Det.h"



void PduR_CanTpRxIndication(PduIdType CanTpRxPduId,NotifResultType Result)
{
	;

}


BufReq_ReturnType PduR_CanTpProvideRxBuffer(PduIdType id, PduLengthType length,
		PduInfoType **PduInfoPtr) {
	;
}





static void handleConsecutiveFrame(const CanTp_RxNSduType *rxConfig,CanTp_ChannelPrivateType *rxRuntime, const PduInfoType *rxPduData)
{
	uint8 indexCount = 0;
	uint8 segmentNumber = 0;
	uint8 extendedAddress = 0;
	PduLengthType bytesLeftToCopy = 0;
	PduLengthType bytesLeftToTransfer = 0;
	PduLengthType currentSegmentSize = 0;
	PduLengthType currentSegmentMaxSize = 0;
	PduLengthType bytesCopiedToPdurRxBuffer = 0;
	BufReq_ReturnType ret = BUFREQ_NOT_OK;

	if (rxRuntime->iso15765.state == RX_WAIT_CONSECUTIVE_FRAME)
	{
		if (rxConfig->CanTpRxAddressingFormat == CANTP_EXTENDED)
		{
			extendedAddress = rxPduData->SduDataPtr[indexCount++];
		}

		// getting consecutive frame number
		segmentNumber = rxPduData->SduDataPtr[indexCount++] & SEGMENT_NUMBER_MASK;      //segment number equals consecutive frame index (3..0 bits in first byte)

		// checking if this consecutive frame is handled
		if (segmentNumber != (rxRuntime->iso15765.framesHandledCount & SEGMENT_NUMBER_MASK)) {
			PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_E_WRONG_SN);
			rxRuntime->iso15765.state = IDLE;
			rxRuntime->mode = CANTP_RX_WAIT;
		}
		else
		{
			currentSegmentMaxSize = MAX_SEGMENT_DATA_SIZE - indexCount;                  // 6 bytes in extended add. & 7 bytes in standard add.
			bytesLeftToCopy = rxRuntime->transferTotal - rxRuntime->transferCount;

			// determining segment size
			if (bytesLeftToCopy < currentSegmentMaxSize) {
				currentSegmentSize = bytesLeftToCopy; // 1-5.
			} else {
				currentSegmentSize = currentSegmentMaxSize; // 6 or 7, depends on addressing format used.
			}
			// Copy received data to buffer provided by SDUR.
			ret = copySegmentToPduRRxBuffer(rxConfig, rxRuntime,&rxPduData->SduDataPtr[indexCount],currentSegmentSize, &bytesCopiedToPdurRxBuffer);

			if (ret == BUFREQ_NOT_OK) {
				PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_E_NO_BUFFER);
				rxRuntime->iso15765.state = IDLE;
				rxRuntime->mode = CANTP_RX_WAIT;
			}
			else if (ret == BUFREQ_BUSY)
			{
				bool dataCopyFailure = FALSE;
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
					rxRuntime->iso15765.stateTimeoutCount = CANTP_CONVERT_MS_TO_MAIN_CYCLES(rxConfig->CanTpNbr);
					rxRuntime->iso15765.state = RX_WAIT_SDU_BUFFER;
					rxRuntime->mode = CANTP_RX_PROCESSING;
					sendFlowControlFrame(rxConfig, rxRuntime, ret);
				}
			}
			else if (ret == BUFREQ_OK)
			{
				bytesLeftToTransfer = rxRuntime->transferTotal - rxRuntime->transferCount;
				if (bytesLeftToTransfer > 0)
				{
					rxRuntime->iso15765.framesHandledCount++;                  // hanzawed 3adad el frames elly 2tna2alet
					COUNT_DECREMENT(rxRuntime->iso15765.nextFlowControlCount); // han2alel 3adad el frames elly fadla 3ala  el next flow control

					if (rxRuntime->iso15765.nextFlowControlCount == 0  && rxRuntime->iso15765.BS > 0) {
						sendFlowControlFrame(rxConfig, rxRuntime, BUFREQ_OK);
					}
					else
					{
						rxRuntime->iso15765.stateTimeoutCount = CANTP_CONVERT_MS_TO_MAIN_CYCLES(rxConfig->CanTpNcr);  //UH
					}
				}
				else
				{
					rxRuntime->iso15765.state = IDLE;
					rxRuntime->mode = CANTP_RX_WAIT;
					PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_OK);
				}
			}
		}
	}
} 					// 438, 550 PC-lint: extendedAdress not accessed. Extended adress needs to be implemented. Ticket #136




static void sendFlowControlFrame(const CanTp_RxNSduType *rxConfig, CanTp_ChannelPrivateType *rxRuntime, BufReq_ReturnType flowStatus)
{
	uint8 indexCount = 0;
	Std_ReturnType ret = E_NOT_OK;
	PduInfoType pduInfo;
	uint8 sduData[8];				 // Note that buffer is declared on the stack.
	uint16 spaceFreePduRBuffer = 0;
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

		spaceFreePduRBuffer = rxRuntime->pdurBuffer->SduLength - rxRuntime->pdurBufferCount;



		if (rxConfig->CanTpRxAddressingFormat == CANTP_EXTENDED)                         // for Extended
		{
			computedBs = (spaceFreePduRBuffer / MAX_PAYLOAD_SF_EXT_ADDR) + 1;  // + 1 is for local buffer.
		}
		else																			// for standard
		{
			computedBs = (spaceFreePduRBuffer / MAX_PAYLOAD_SF_STD_ADDR) + 1;  // + 1 is for local buffer.
		}

		if (computedBs > rxConfig->CanTpBs)
		{
			computedBs = rxConfig->CanTpBs;
		}

		sduData[indexCount++] = computedBs; 							// 734 PC-lint: Okej att casta till uint8?
		sduData[indexCount++] = (uint8) rxConfig->CanTpSTmin;
		rxRuntime->iso15765.nextFlowControlCount = computedBs;
		pduInfo.SduLength = indexCount;                           	  // indexcount here = 3
		break;
	}

	case BUFREQ_NOT_OK:
		break;

	case BUFREQ_BUSY:
		sduData[indexCount++] = ISO15765_TPCI_FC | ISO15765_FLOW_CONTROL_STATUS_WAIT;         // change the value of control flag (wait)
		indexCount +=2;
		pduInfo.SduLength = indexCount;								  // indexcount here = 3
		break;

	case BUFREQ_OVFL:
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
		PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_E_NOT_OK);
		rxRuntime->iso15765.state = IDLE;
		rxRuntime->mode = CANTP_RX_WAIT;
	}
}


void CanTp_Init( const CanTp_ConfigType* CfgPtr )
{


		CanTp_ChannelPrivateType *runtimeData;
		//uint8 TxChannel;
		//uint8 RxChannel;


		uint8 i;
		for (i=0; i < CANTP_NSDU_CONFIG_LIST_SIZE; i++)
			{


				if ( CfgPtr->CanTpChannel.direction == IS015765_TRANSMIT )
				{
										/* For Tx */


				//	txConfigParams = (CanTp_TxNSduType*)&CfgPtr->CanTpChannel.CanTpTxNSdu[i];
				//	TxChannel = CfgPtr->CanTpChannel.CanTpTxNSdu[i].CanTpTxChannel;

							if (CfgPtr->CanTpChannel.CanTpTxNSdu[i].CanTpTxChannel < CANTP_NSDU_RUNTIME_LIST_SIZE)
							{
								runtimeData = &CanTpRunTimeData.runtimeDataList[CfgPtr->CanTpChannel.CanTpTxNSdu[i].CanTpTxChannel];
							}
							 else
							{
								runtimeData = &CanTpRunTimeData.runtimeDataList[CANTP_NSDU_RUNTIME_LIST_SIZE-1];
							}
							initTx15765RuntimeData( runtimeData );

				}

				else
				{
										/* For Rx */

				//	rxConfigParams = (CanTp_RxNSduType*)&CfgPtr->CanTpChannel.CanTpRxNSdu[i];
				//	RxChannel = CfgPtr->CanTpChannel.CanTpTxNSdu[i].CanTpRxChannel;

							if (CfgPtr->CanTpChannel.CanTpRxNSdu[i].CanTpRxChannel < CANTP_NSDU_RUNTIME_LIST_SIZE)
							{
								runtimeData = &CanTpRunTimeData.runtimeDataList[CfgPtr->CanTpChannel.CanTpRxNSdu[i].CanTpRxChannel];
							}
							else
							{
								runtimeData = &CanTpRunTimeData.runtimeDataList[CANTP_NSDU_RUNTIME_LIST_SIZE-1];
							}
							initRx15765RuntimeData( runtimeData );

				}
			}

		CanTpRunTimeData.internalState = CANTP_ON;    /* if the initfunc finished correcltly without errors ,then move into CANTP_ON state */

}




void CanTp_Shutdown(void)
{

	CanTpRunTimeData.internalState = CANTP_OFF;

}

static ISO15765FrameType getFrameType(const CanTp_AddressingFormatType *formatType,const PduInfoType *CanTpRxPduPtr)
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

	case ISO15765_TPCI_FC: 						// Some kind of flow control.
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

static void handleFlowControlFrame(const CanTp_TxNSduType *txConfig,CanTp_ChannelPrivateType *txRuntime, const PduInfoType *txPduData)
{

	int indexCount = 0;
	uint8 extendedAddress = 0;

	if ( txRuntime->iso15765.state == TX_WAIT_FLOW_CONTROL )
	{
		if (txConfig->CanTpTxAddressingFormat == CANTP_EXTENDED)
		{
			extendedAddress = txPduData->SduDataPtr[indexCount++];                     // code we7esh we hanshelha 3ashan mabyesta5demhash
		}

		// txPduData->SduDataPtr[indexCount++] = 1st byte (frame type + flow control flag)
		switch (txPduData->SduDataPtr[indexCount++] & ISO15765_TPCI_FS_MASK) // checking the flow control flag (Clear To Send=0 , Wait=1, Overflow/abort =2)
		{
		case ISO15765_FLOW_CONTROL_STATUS_CTS:
#if 1
		{	// This construction is added to make the hcs12 compiler happy.
			const uint8 bs = txPduData->SduDataPtr[indexCount++];
			txRuntime->iso15765.BS = bs;
			txRuntime->iso15765.nextFlowControlCount = bs;
		}
		txRuntime->iso15765.STmin = txPduData->SduDataPtr[indexCount++];
#else
		txRuntime->iso15765.BS = txPduData->SduDataPtr[indexCount++];
		txRuntime->iso15765.nextFlowControlCount = txRuntime->iso15765.BS;
		txRuntime->iso15765.STmin = txPduData->SduDataPtr[indexCount++];
#endif
		// change state and setup timout
		txRuntime->iso15765.stateTimeoutCount = CANTP_CONVERT_MS_TO_MAIN_CYCLES(txConfig->CanTpNcs);
		txRuntime->iso15765.state = TX_WAIT_TRANSMIT;
		break;

		case ISO15765_FLOW_CONTROL_STATUS_WAIT:
			txRuntime->iso15765.stateTimeoutCount = CANTP_CONVERT_MS_TO_MAIN_CYCLES(txConfig->CanTpNbs);  /*CanTp: 264*/
			txRuntime->iso15765.state = TX_WAIT_FLOW_CONTROL;
			break;

		case ISO15765_FLOW_CONTROL_STATUS_OVFLW:
			PduR_CanTpRxIndication(txConfig->CanTpRxFcNPdu.CanTpRxFcNPduId, NTFRSLT_E_NOT_OK);       // 27na benehbed ,,,, PduR_PduID
			txRuntime->iso15765.state = IDLE;
			txRuntime->mode = CANTP_TX_WAIT;
			break;
		}
	}
}


void CanTp_RxIndication(PduIdType CanTpRxPduId,const PduInfoType *CanTpRxPduPtr)
{

	const CanTp_RxNSduType *rxConfigParams; // Params reside in ROM.
	const CanTp_TxNSduType *txConfigParams;
	CanTp_AddressingFormatType addressingFormat; 								// Configured
	CanTp_ChannelPrivateType *runtimeParams = 0; // Params reside in RAM.
	ISO15765FrameType frameType;
	PduIdType CanTpTxNSduId, CanTpRxNSduId;

	//Check if PduId is valid
	if (CanTpRxPduId >= CANTP_RXID_LIST_SIZE)
	{
		return;
	}

	addressingFormat = CanTp_Config.CanTpChannel.CanTpTxNSdu[CanTpRxPduId].CanTpTxAddressingFormat;

	/* TODO John - Use a different indication of not set than 0xFFFF? */
	frameType = getFrameType(addressingFormat, CanTpRxPduPtr);

	if( frameType == FLOW_CONTROL_CTS_FRAME )
	{
		if( CanTp_Config.CanTpChannel.CanTpTxNSdu[CanTpRxPduId].CanTpReferringTxIndex != 0xFFFF )
		{
			CanTpTxNSduId = CanTpConfig.CanTpRxIdList[CanTpRxPduId].CanTpReferringTxIndex;
			//txConfigParams = &CanTpConfig.CanTpNSduList[CanTpTxNSduId].configData.CanTpTxNSdu;
			txConfigParams = CanTp_Config.CanTpChannel.CanTpTxNSdu[CanTpTxNSduId]
			runtimeParams = &CanTpRunTimeData.runtimeDataList[txConfigParams->CanTpTxChannel];
		}
		else
		{
			//Invalid FC received
			return;
		}
		rxConfigParams = NULL;
	}

	else
	{
		if( CanTp_Config.CanTpRxIdList[CanTpRxPduId].CanTpNSduIndex != 0xFFFF )
		{
			CanTpRxNSduId = CanTpConfig.CanTpRxIdList[CanTpRxPduId].CanTpNSduIndex;
			rxConfigParams = &CanTpConfig.CanTpNSduList[CanTpRxNSduId].configData.CanTpRxNSdu;
			runtimeParams = &CanTpRunTimeData.runtimeDataList[rxConfigParams->CanTpRxChannel];
		}
		else {
			//Invalid Frame received
			return;
		}
		txConfigParams = NULL;
	}



	switch (frameType)
	{
	case SINGLE_FRAME:
	{
		if (rxConfigParams != NULL)
		{
			handleSingleFrame(rxConfigParams, runtimeParams, CanTpRxPduPtr);
		}

		break;
	}

	case FIRST_FRAME:
	{
		if (rxConfigParams != NULL)
		{
			handleFirstFrame(rxConfigParams, runtimeParams, CanTpRxPduPtr);
		}
		break;
	}

	case CONSECUTIVE_FRAME:
	{
		if (rxConfigParams != NULL)
		{
			handleConsecutiveFrame(rxConfigParams, runtimeParams, CanTpRxPduPtr);
		}
		break;
	}

	case FLOW_CONTROL_CTS_FRAME:
	{
		if (txConfigParams != NULL)
		{
			handleFlowControlFrame(txConfigParams, runtimeParams, CanTpRxPduPtr);
		}
		break;
	}
	case INVALID_FRAME:
	{
		break;
	}

	default:
		break;
	}
}



static BufReq_ReturnType copySegmentToPduRRxBuffer(const CanTp_RxNSduType *rxConfig,CanTp_ChannelPrivateType *rxRuntime, uint8 *segment,PduLengthType segmentSize,
		PduLengthType *bytesWrittenSuccessfully)

{

	BufReq_ReturnType ret = BUFREQ_NOT_OK;
	bool endLoop = FALSE;
	*bytesWrittenSuccessfully = 0;

	while ((*bytesWrittenSuccessfully < segmentSize) && (!endLoop))
	{
		// Copy the data that resides in the buffer.
		if (rxRuntime->pdurBuffer != NULL)
		{
			while ((*bytesWrittenSuccessfully < segmentSize ) && (rxRuntime->pdurBuffer->SduLength > rxRuntime->pdurBufferCount))
			{
				rxRuntime->pdurBuffer->SduDataPtr[rxRuntime->pdurBufferCount++] = segment[(*bytesWrittenSuccessfully)++];
			}
		}
		if (*bytesWrittenSuccessfully < segmentSize )
		{
			// We need to request a new buffer from the SDUR.
			// TODO: We should do a timeout here.
			ret = PduR_CanTpProvideRxBuffer(rxConfig->CanTpRxNPdu.CanTpRxNPduId, rxRuntime->transferTotal, &rxRuntime->pdurBuffer);

			if (ret == BUFREQ_OK)
			{
				rxRuntime->pdurBufferCount = 0;		 			// The buffer is emptied.
			}
			else if (ret == BUFREQ_BUSY)
			{
				rxRuntime->transferCount += *bytesWrittenSuccessfully;
				endLoop = TRUE;
			}
			else
			{
				endLoop = TRUE;									 // Let calling function handle this error.
			}
		}

		else
		{
			rxRuntime->transferCount += segmentSize; 			//== bytesWrittenSuccessfully
			ret = BUFREQ_OK;
			endLoop = TRUE;
		}
	}
	return ret;
}


/* this function coping data and length to tuntime if segementsize < MAX_SEGMENT_DATA_SIZE */

static bool copySegmentToLocalRxBuffer(CanTp_ChannelPrivateType *rxRuntime, uint8 *segment,PduLengthType segmentSize)
{
	bool ret = FALSE;

	if ( segmentSize < MAX_SEGMENT_DATA_SIZE )
	{
		uint8 i;
		for (i=0; i < segmentSize; i++)
		{
			rxRuntime->canFrameBuffer.data[i] = segment[i];
		}

		rxRuntime->canFrameBuffer.byteCount = segmentSize;
		ret = TRUE;
	}
	return ret;
}


static PduLengthType getPduLength(const CanTp_AddressingFormatType *formatType,const ISO15765FrameType iso15765Frame, const PduInfoType *CanTpRxPduPtr)
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
		res = 0;									 // TODO: maybe we should have an error code here.
		break;
	}
	return res;
}




static void handleSingleFrame(const CanTp_RxNSduType *rxConfig,CanTp_ChannelPrivateType *rxRuntime, const PduInfoType *rxPduData)
{
	BufReq_ReturnType ret;
	PduLengthType pduLength;
	uint8 *data = NULL;
	PduLengthType bytesWrittenToSduRBuffer;


	if (rxRuntime->iso15765.state != IDLE)
	{
		PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_E_NOT_OK);  // Abort current reception, we need to tell the current receiver it has been aborted.
	}

	(void) initRx15765RuntimeData(rxRuntime);
	pduLength = getPduLength(&rxConfig->CanTpRxAddressingFormat, SINGLE_FRAME, rxPduData);                    ////////////////////////////////////////



	if (rxConfig->CanTpRxAddressingFormat == CANTP_STANDARD)
	{
		data = &rxPduData->SduDataPtr[1];
	}
	else
	{
		data = &rxPduData->SduDataPtr[2];
	}

	rxRuntime->transferTotal = pduLength;
	rxRuntime->iso15765.state = SF_OR_FF_RECEIVED_WAITING_PDUR_BUFFER;
	rxRuntime->mode = CANTP_RX_PROCESSING;
	rxRuntime->iso15765.stateTimeoutCount = CANTP_CONVERT_MS_TO_MAIN_CYCLES(rxConfig->CanTpNbr);

	ret = copySegmentToPduRRxBuffer(rxConfig, rxRuntime, data, pduLength, &bytesWrittenToSduRBuffer);        /////////////////////////////////////

	if (ret == BUFREQ_OK)
	{
		PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_OK);
		rxRuntime->iso15765.state = IDLE;
		rxRuntime->mode = CANTP_RX_WAIT;

	}
	else if (ret == BUFREQ_BUSY)
	{
		if (rxConfig->CanTpRxAddressingFormat == CANTP_STANDARD)
		{
			data = &rxPduData->SduDataPtr[1];
		}
		else
		{
			data = &rxPduData->SduDataPtr[2];
		}
		(void)copySegmentToLocalRxBuffer(rxRuntime, data, pduLength ); 									 ///////////////////////////////////////////
		rxRuntime->iso15765.state = RX_WAIT_SDU_BUFFER;
		rxRuntime->mode = CANTP_RX_PROCESSING;
	}
	else
	{
		PduR_CanTpRxIndication(rxConfig->CanTpRxNPdu.CanTpRxNPduId, NTFRSLT_E_NO_BUFFER);
		rxRuntime->iso15765.state = IDLE;
		rxRuntime->mode = CANTP_RX_WAIT;
	}
}








































void CanTp_MainFunction(void)
{
	BufReq_ReturnType ret;         		    /* enum = {BUFREQ_OK ,BUFREQ_NOT_OK,BUFREQ_BUSY,BUFREQ_OVFL }*/

	PduLengthType bytesWrittenToSduRBuffer;

	CanTp_ChannelPrivateType *txRuntimeListItem = NULL;
	CanTp_ChannelPrivateType *rxRuntimeListItem = NULL;

	const CanTp_TxNSduType *txConfigListItem = NULL;
	const CanTp_RxNSduType *rxConfigListItem = NULL;


	uint8 i = 0;
	for( i=0; i < CANTP_NSDU_CONFIG_LIST_SIZE; i++ )
	{
			/* in case of TX */

		if ( CanTp_Config.CanTpChannel.direction == IS015765_TRANSMIT )         // lsa htt3dl ????????????????????        3dltha ^^
		{
			txConfigListItem = (CanTp_TxNSduType*)&CanTp_Config.CanTpChannel.CanTpTxNSdu[i];
			txRuntimeListItem = &CanTpRunTimeData.runtimeDataList[txConfigListItem->CanTpTxChannel];

			switch (txRuntimeListItem->iso15765.state)
			{

			case TX_WAIT_STMIN:
				TIMER_DECREMENT(txRuntimeListItem->iso15765.stateTimeoutCount); 		// Make sure that STmin timer has expired.
				if (txRuntimeListItem->iso15765.stateTimeoutCount != 0)
				{
					break;
				}

				txRuntimeListItem->iso15765.state = TX_WAIT_TRANSMIT;


			case TX_WAIT_TRANSMIT:
			{
				ret = sendNextTxFrame(txConfigListItem, txRuntimeListItem);

				if ( ret == BUFREQ_OK )
				{
					// successfully sent frame
				}

				else if( ret == BUFREQ_BUSY )
				{
					// check N_Cs timeout
					TIMER_DECREMENT(txRuntimeListItem->iso15765.stateTimeoutCount);
					if (txRuntimeListItem->iso15765.stateTimeoutCount == 0)
					{
						txRuntimeListItem->iso15765.state = IDLE;
						txRuntimeListItem->mode = CANTP_TX_WAIT;
						//PduR_CanTpTxConfirmation(txConfigListItem->PduR_PduId, NTFRSLT_E_NOT_OK);    			 // it is not important in the core Now
					}
					else
					{
						// For MISRA Rules only as i remember
					}
				}

				else
				{
					txRuntimeListItem->iso15765.state = IDLE;
					txRuntimeListItem->mode = CANTP_TX_WAIT;
					//PduR_CanTpTxConfirmation(txConfigListItem->PduR_PduId, NTFRSLT_E_NOT_OK); 				 // it is not important in the core Now
				}
				break;
			}

			case TX_WAIT_FLOW_CONTROL:

				TIMER_DECREMENT(txRuntimeListItem->iso15765.stateTimeoutCount);
				if (txRuntimeListItem->iso15765.stateTimeoutCount == 0)
				{
					txRuntimeListItem->iso15765.state = IDLE;
					txRuntimeListItem->mode = CANTP_TX_WAIT;
					//PduR_CanTpTxConfirmation(txConfigListItem->PduR_PduId, NTFRSLT_E_NOT_OK); 			    // it is not important in the core Now
				}
				break;

			case TX_WAIT_TX_CONFIRMATION:
				TIMER_DECREMENT(txRuntimeListItem->iso15765.stateTimeoutCount);
				if (txRuntimeListItem->iso15765.stateTimeoutCount == 0)
				{
					txRuntimeListItem->iso15765.state = IDLE;
					txRuntimeListItem->mode = CANTP_TX_WAIT;
					//PduR_CanTpTxConfirmation(txConfigListItem->PduR_PduId, NTFRSLT_E_NOT_OK);
				}
				break;

			default:
				break;

			}
		}



			/* in case of RX */

		else
		{
			rxConfigListItem =(CanTp_RxNSduType*)&CanTp_Config.CanTpChannel.CanTpRxNSdu[i];
			rxRuntimeListItem = &CanTpRunTimeData.runtimeDataList [ rxConfigListItem->CanTpRxChannel ];

			switch (rxRuntimeListItem->iso15765.state)
			{
			case RX_WAIT_CONSECUTIVE_FRAME:
			{
				TIMER_DECREMENT (rxRuntimeListItem->iso15765.stateTimeoutCount);

				if (rxRuntimeListItem->iso15765.stateTimeoutCount == 0)
				{
					//PduR_CanTpRxIndication(rxConfigListItem->PduR_PduId, NTFRSLT_E_NOT_OK);
					rxRuntimeListItem->iso15765.state = IDLE;
					rxRuntimeListItem->mode = CANTP_RX_WAIT;
				}
				break;
			}

			case RX_WAIT_SDU_BUFFER:
			{
				TIMER_DECREMENT (rxRuntimeListItem->iso15765.stateTimeoutCount);
				/* We end up here if we have requested a buffer from the
				 * PDUR but the response have been BUSY. We assume
				 * we have data in our local buffer and we are expected
				 * to send a flow-control clear to send (CTS).
				 */
				if (rxRuntimeListItem->iso15765.stateTimeoutCount == 0)
				{
					//PduR_CanTpRxIndication(rxConfigListItem->PduR_PduId, NTFRSLT_E_NOT_OK);			  /* CanTp_00214 */
					rxRuntimeListItem->iso15765.state = IDLE;
					rxRuntimeListItem->mode = CANTP_RX_WAIT;
				}


				else			//	stateTimeoutCount != 0
				{
					PduLengthType bytesRemaining = 0;

					 /* copies from local buffer to PDUR buffer. */
					ret = copySegmentToPduRRxBuffer(rxConfigListItem,rxRuntimeListItem,rxRuntimeListItem->canFrameBuffer.data,rxRuntimeListItem->canFrameBuffer.byteCount
							,&bytesWrittenToSduRBuffer);
					bytesRemaining = rxRuntimeListItem->transferTotal -  rxRuntimeListItem->transferCount;
					if (bytesRemaining > 0)
					{
						sendFlowControlFrame( rxConfigListItem, rxRuntimeListItem, ret ); 			/* (Busy or CTS) */
					}

					if (ret == BUFREQ_OK)
					{
						if ( bytesRemaining > 0 )
						{
							rxRuntimeListItem->iso15765.stateTimeoutCount = CANTP_CONVERT_MS_TO_MAIN_CYCLES(rxConfigListItem->CanTpNcr);  //UH
							rxRuntimeListItem->iso15765.state = RX_WAIT_CONSECUTIVE_FRAME;
						}
						else
						{
							//PduR_CanTpRxIndication(rxConfigListItem->PduR_PduId, NTFRSLT_OK);			  /* CanTp_00214 */
							rxRuntimeListItem->iso15765.state = IDLE;
							rxRuntimeListItem->mode = CANTP_RX_WAIT;
						}
					}
					else if (ret == BUFREQ_NOT_OK )
					{
						//PduR_CanTpRxIndication(rxConfigListItem->PduR_PduId, NTFRSLT_E_NOT_OK);        /* CanTp_00214 */
						rxRuntimeListItem->iso15765.state = IDLE;
						rxRuntimeListItem->mode = CANTP_RX_WAIT;
					}
					else if ( ret == BUFREQ_BUSY )
					{

					}
				}
				break;
			}
			default:
				break;
			}
		}
	}
}





int main()
{

	CanTp_Init(&CanTp_Config);

	return 0 ;

}
