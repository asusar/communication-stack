#ifndef CANTP_HELPER_FUNCTIONS_H_
#define CANTP_HELPER_FUNCTIONS_H_

#include "CanTp_Types.h"
#include "CanTpRuntime.h"



Std_ReturnType CanIf_TransmitForTest(PduIdType CanTxPduId,const PduInfoType* PduInfoPtr);
//BufReq_ReturnType PduR_CanTpCopyTxData(PduIdType TxPduId , PduInfoType* PduInfoPtr , uint8 Retry , PduLengthType* availableDataSize);



/**************************************************************** Helper Functions not in sws ***************************************************************************/
Std_ReturnType canTansmitPaddingHelper(const CanTp_TxNSduType *txConfig, CanTp_ChannelPrivateType *txRuntime,PduInfoType *PduInfoPtr);
Std_ReturnType canReceivePaddingHelper(const CanTp_RxNSduType *rxConfig, CanTp_ChannelPrivateType *rxRuntime, PduInfoType *PduInfoPtr);
BufReq_ReturnType copySegmentToPduRRxBuffer(const CanTp_RxNSduType *rxConfig,CanTp_ChannelPrivateType *rxRuntime,PduInfoType *info);
boolean copySegmentToLocalRxBuffer(CanTp_ChannelPrivateType *rxRuntime, uint8 *segment,PduLengthType segmentSize);
ISO15765FrameType getFrameType(const CanTp_AddressingFormatType *formatType,const PduInfoType *CanTpRxPduPtr);
PduLengthType getPduLength(const CanTp_AddressingFormatType *formatType,const ISO15765FrameType iso15765Frame, const PduInfoType *CanTpRxPduPtr);
ISO15765FrameType calcRequiredProtocolFrameType(const CanTp_TxNSduType *txConfig, CanTp_ChannelPrivateType *txRuntime);



/*************************************************** Handling All Frames ***********************************************************************************************/
void handleSingleFrame(const CanTp_RxNSduType *rxConfig , CanTp_ChannelPrivateType *rxRuntime ,const PduInfoType *rxPduData);
void handleFirstFrame (const CanTp_RxNSduType *rxConfig , CanTp_ChannelPrivateType *rxRuntime ,const  PduInfoType *rxPduData);
void handleFlowControlFrame(const CanTp_TxNSduType *txConfig,CanTp_ChannelPrivateType *txRuntime, const PduInfoType *txPduData);
void handleConsecutiveFrame(const CanTp_RxNSduType *rxConfig,CanTp_ChannelPrivateType *rxRuntime, const PduInfoType *rxPduData);
void handleNextTxFrameSent(const CanTp_TxNSduType *txConfig, CanTp_ChannelPrivateType *txRuntime);



/*************************************************** Sending Frames *****************************************************************************************************/
void sendFlowControlFrame(const CanTp_RxNSduType *rxConfig, CanTp_ChannelPrivateType *rxRuntime, BufReq_ReturnType flowStatus);
BufReq_ReturnType sendNextTxFrame(const CanTp_TxNSduType *txConfig, CanTp_ChannelPrivateType *txRuntime);


/* this function coping data and length to Rx_runtime.canFrameBufferData if segementsize < MAX_SEGMENT_DATA_SIZE and return True if copying Done */

/* This Fuction is used to get the length of the PDU from N_PCI */





#endif /* CANTP_HELPER_FUNCTIONS_H_ */
