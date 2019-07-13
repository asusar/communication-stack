#ifndef CANIF_CBK_H_
#define CANIF_CBK_H_

#include "CanIf_Cfg.h"

#define CANIF_TRANSMIT_CANCELLATION   (STD_OFF) /* This macros is defined to resolve misra warning*/

void CanIf_TxConfirmation( uint32 canTxPduId );
void CanIf_RxIndication( uint8 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr );
//void CanIf_RxIndication( const Can_HwType* Mailbox,const PduInfoType* PduInfoPtr);
#if ( CANIF_TRANSMIT_CANCELLATION == STD_ON )
void CanIf_CancelTxConfirmation( const Can_PduType *PduInfoPtr );
#endif

void CanIf_ControllerBusOff( uint8 Controller );
void CanIf_SetWakeupEvent( uint8 Controller );

/* ArcCore extensions */
void CanIf_Arc_Error( uint8 Controller, Can_Arc_ErrorType Error );

FUNC(void,CANIF_CODE) CanIf_ControllerModeIndication
(
	VAR(CanIf_Arc_ChannelIdType,AUTOMATIC) channel_CanIf_SetControllerMode,
	VAR(
Can_ControllerStateType, AUTOMATIC) ControllerMode
);

#endif /*CANIF_CBK_H_*/
