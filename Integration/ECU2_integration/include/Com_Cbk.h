/*
 * Com_Cbk.h
 *
 *  Created on: Apr 28, 2019
 *      Author: lenovo
 */

#ifndef COM_CBK_H_
#define COM_CBK_H_


void Com_RxIndication( PduIdType RxPduId, const PduInfoType* PduInfoPtr ) ;
void Com_TpRxIndication( PduIdType id, Std_ReturnType result );
void Com_TxConfirmation( PduIdType TxPduId, Std_ReturnType result );
void Com_TpTxConfirmation( PduIdType id, Std_ReturnType result );
BufReq_ReturnType Com_StartOfReception( PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr ) ;
BufReq_ReturnType Com_CopyRxData( PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr ) ;
BufReq_ReturnType Com_CopyTxData( PduIdType id, const PduInfoType* info, const RetryInfoType* retry, PduLengthType* availableDataPtr );


#endif /* COM_CBK_H_ */
