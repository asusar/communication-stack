#include "PduR_CanIf.h"
#include "CanIf.h"

#if CANIF_UNIT_TESTING == STD_ON
#include "txConfirmation_unitTest.h"
#endif

void PduR_CanIfRxIndication(uint32 CanRxPduId,const PduInfoType* PduInfoPtr){
    printf("hello from PduR_CanIfRxIndication : %d" , CanRxPduId);
}
#if CANIF_UNIT_TESTING == STD_ON
void PduR_CanIfTxConfirmation(uint32 CanTxPduId){
	CanIfUserTxConfirmationStubFn();
}
#else
void PduR_CanIfTxConfirmation(uint32 CanTxPduId){}
#endif
