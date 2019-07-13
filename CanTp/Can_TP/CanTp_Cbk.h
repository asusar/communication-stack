#ifndef CanTp_Cbk_H_
#define CanTp_Cbk_H_




void CanTp_RxIndication( PduIdType RxPduId, const PduInfoType* PduInfoPtr );

void CanTp_TxConfirmation( PduIdType TxPduId, Std_ReturnType result );




#endif
