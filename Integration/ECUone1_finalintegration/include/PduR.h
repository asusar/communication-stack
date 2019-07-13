/*
 * PduR.h
 *
 *  Created on: Apr 28, 2019
 *      Author: lenovo
 */
#include "stdint.h"

#ifndef PDUR_H_
#define PDUR_H_


# define canif_routes_no 4
# define com_routes_no 4
# define cantp_routes_no 4

#include  "ComStack_Types.h"
#include  "Std_Types.h"
#include  "CanIf.h"
#include  "CanTp.h"
#include  "Com_Cbk.h"



Std_ReturnType PduR_ComTransmit( PduIdType TxPduId, const PduInfoType* PduInfoPtr );
void PduR_CanIfRxIndication( PduIdType RxPduId, const PduInfoType* PduInfoPtr );
BufReq_ReturnType PduR_CanTpCopyRxData( PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr );
void PduR_CanTpRxIndication( PduIdType id, Std_ReturnType result );    //WHEN COPY IS DONE
BufReq_ReturnType PduR_CanTpStartOfReception( PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType PduR_CanTpCopyTxData( PduIdType id,  PduInfoType* info, const RetryInfoType* retry, PduLengthType* availableDataPtr );
Std_ReturnType PduR_ComTransmit( PduIdType TxPduId, const PduInfoType* PduInfoPtr );
void  PduR_ComTxConfirmation( PduIdType TxPduId, Std_ReturnType result );

typedef enum
{
    CanIF,
    canTP,
    Com,
    CanTp_COM,
    CanTp_TXCopy,
    drirect
}type_t;


#endif /* PDUR_H_ */





