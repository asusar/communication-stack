///*
// * PduR.c
// *
// *  Created on: Apr 28, 2019
// *      Author: moustafa ahmed
// */
//
#include  "include/PduR_cfg.h"
#include  "include/PduR.h"
#include  "include/PduR_helper.h"


Std_ReturnType PduR_ComTransmit( PduIdType TxPduId, const PduInfoType* PduInfoPtr )
{
    static PduInfoType info;
    info.SduLength = PduInfoPtr->SduLength;
    info.SduDataPtr = PduInfoPtr->SduDataPtr;

    uint8_t id =  get_ID(TxPduId,Com);
    type_t type =get_type(TxPduId,Com);
    if(type== CanIF)
    {
       return CanIf_Transmit(id, PduInfoPtr);
    }
    else if(type==canTP)
    {
     return CanTp_Transmit( id,  PduInfoPtr );
    }
//    Com_RxIndication(1, &info);
}
void PduR_CanIfRxIndication( PduIdType RxPduId, const PduInfoType* PduInfoPtr )
{
        uint8_t id= get_ID( RxPduId , CanIF);
        Com_RxIndication( id, PduInfoPtr )  ;
}

BufReq_ReturnType PduR_CanTpCopyRxData( PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr )
{
         uint8_t ID= get_ID( id , CanTp_COM);
         return  Com_CopyRxData( ID, info, bufferSizePtr );
}

void PduR_CanTpRxIndication( PduIdType id, Std_ReturnType result )    //WHEN COPY IS DONE
{
         uint8_t ID= get_ID(  id , CanTp_COM);
         Com_TpRxIndication(  id,  result );
}

BufReq_ReturnType PduR_CanTpStartOfReception( PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr )
{
        uint8_t ID= get_ID( id , CanTp_COM);
        return Com_StartOfReception( ID, info,TpSduLength, bufferSizePtr );
}

BufReq_ReturnType PduR_CanTpCopyTxData( PduIdType id,  PduInfoType* info, const RetryInfoType* retry, PduLengthType* availableDataPtr )
{
       uint8_t ID= get_ID( id , CanTp_TXCopy);
       return Com_CopyTxData( ID, info,  retry, availableDataPtr );
}

void  PduR_CanTpTxConfirmation( PduIdType TxPduId, Std_ReturnType result )
        {
    uint8_t ID = get_ID( TxPduId , CanTp_TXCopy);
    return Com_TpTxConfirmation( ID ,result );
        }
