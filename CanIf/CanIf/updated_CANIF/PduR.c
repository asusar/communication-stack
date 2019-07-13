#include "PduR.h"

Std_ReturnType PduR_CancelTransmitRequest(
		PduR_CancelReasonType PduCancelReason, uint32 PduId){return PDU_CNLDO;}
void PduR_ChangeParameterRequest(PduR_ParameterValueType PduParameterValue,
		uint32 PduId){}
		
void PduR_Init(const PduR_PBConfigType* ConfigPtr){}
void PduR_GetVersionInfo(Std_VersionInfoType* versionInfo){}
uint32 PduR_GetConfigurationId(void){return 0;}

void PduR_BufferInc(PduRTxBuffer_type *Buffer, uint8 **ptr){}
void PduR_BufferQueue(PduRTxBuffer_type *Buffer, const uint8 * SduPtr){}
void PduR_BufferDeQueue(PduRTxBuffer_type *Buffer, uint8 *SduPtr){}
void PduR_BufferFlush(PduRTxBuffer_type *Buffer){}
uint8 PduR_BufferIsFull(PduRTxBuffer_type *Buffer){return 0;}
void PduR_LoIfRxIndication(uint32 PduId, const uint8* SduPtr){}
void PduR_LoIfTxConfirmation(uint32 PduId){}
void PduR_LoIfTriggerTransmit(uint32 PduId, uint8* SduPtr){}

