/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/
#ifndef CANIF_H_
#define CANIF_H_
#include "Modules.h"
#if defined(USE_PDUR)
#include "PduR.h"
#endif

#if defined(USE_COM)
#include "Com.h"
#endif

#define CANIF_TESTING_TRANSMIT_NADAANDAHMED 1
#define CANIF_VENDOR_ID          (VENDOR_ID_ARCCORE)
#define CANIF_MODULE_ID          (MODULE_ID_CANIF)
#define CANIF_AR_MAJOR_VERSION   3
#define CANIF_AR_MINOR_VERSION   1
#define CANIF_AR_PATCH_VERSION   5

#define CANIF_SW_MAJOR_VERSION   1
#define CANIF_SW_MINOR_VERSION   3
#define CANIF_SW_PATCH_VERSION   0

/*Configuration Macros*/

/*From the configuration tool as the sum of all the buffers*/
#define CANIF_BUFFER_POOL_SIZE 40

#if defined(USE_DET)
#include "Det.h"
#endif
#include "CanIf_Types.h"
#include "CanIf_SpecialPdus.h"
#include "CanIf_Cfg.h"

#include "CanIf_ConfigTypes.h"
extern CanIf_ConfigType CanIf_Config;
extern CanIf_TxBuffPduInfo_t BuffPool[CANIF_BUFFER_POOL_SIZE];



/* Service IDs */
#define CANIF_INIT_ID                0x01
#define CANIF_INIT_CONTROLLER_ID     0x02
#define CANIF_SET_CONTROLLER_MODE_ID 0x03
#define CANIF_GET_CONTROLLER_MODE_ID 0x04
#define CANIF_TRANSMIT_ID            0x05
#define CANIF_READTXPDUDATA_ID       0x06
#define CANIF_READTXNOTIFSTATUS_ID   0x07
#define CANIF_READRXNOTIFSTATUS_ID   0x08
#define CANIF_SETPDUMODE_ID          0x09
#define CANIF_GETPDUMODE_ID          0x0A
#define CANIF_SETDYNAMICTX_ID        0x0C
#define CANIF_SET_TRANSCEIVERMODE_ID     0x0D
#define CANIF_GET_TRANSCEIVERMODE_ID     0x0E
#define CANIF_GET_TRCVMODEREASON_ID      0x0F
#define CANIF_SET_TRANSCEIVERWAKEMODE_ID 0x10
#define CANIF_CHECKWAKEUP_ID          0x11
#define CANIF_CHECKVALIDATION_ID      0x12
#define CANIF_TXCONFIRMATION_ID       0x13
#define CANIF_RXINDICATION_ID         0x14
#define CANIF_CANCELTXCONFIRMATION_ID 0x15
#define CANIF_CONTROLLER_BUSOFF_ID    0x16

#define CANIF_SETWAKEUPEVENT_ID       0x40
#define CANIF_ARCERROR_ID           0x41

void CanIf_Init(const CanIf_ConfigType *ConfigPtr);

#if (CANIF_UNIT_TESTING==STD_ON)
void CanIf_UnInit (void);
#endif

void CanIf_InitController(uint8  Controller,
	    uint8  ConfigurationIndex);

Std_ReturnType CanIf_SetControllerMode(uint8 Controller,
		
Can_ControllerStateType ControllerMode);

Std_ReturnType CanIf_GetControllerMode(uint8 Controller,
		
Can_ControllerStateType *ControllerModePtr);

Std_ReturnType CanIf_Transmit(uint32 CanTxPduId,
		const PduInfoType *PduInfoPtr);

#if ( CANIF_READRXPDU_DATA_API == STD_ON )
Std_ReturnType CanIf_ReadRxPduData(uint32 CanRxPduId,
		PduInfoType *PduInfoPtr);
#endif

#if ( CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON )
CanIf_NotifStatusType CanIf_ReadTxNotifStatus(uint32 CanTxPduId);
#endif

#if ( CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON )
CanIf_NotifStatusType CanIf_ReadRxNotifStatus(uint32 CanRxPduId);
#endif

Std_ReturnType CanIf_SetPduMode( uint8 Controller, CanIf_ChannelSetModeType PduModeRequest );
Std_ReturnType CanIf_GetPduMode( uint8 Controller, CanIf_ChannelGetModeType *PduModePtr );

#if ( CANIF_ARC_RUNTIME_PDU_CONFIGURATION == STD_ON )
void CanIf_SetDynamicTxId( uint32 CanTxPduId, Can_IdType CanId );
CanIf_TxPduConfigType * CanIf_FindTxPduEntry(uint32 id);
CanIf_RxPduConfigType * CanIf_FindRxPduEntry(uint32 id);
const CanIf_HrhConfigType* CanIf_Arc_GetReceiveHandler(CanIf_Arc_ChannelIdType Channel);
const CanIf_HthConfigType* CanIf_Arc_GetTransmitHandler(CanIf_Arc_ChannelIdType Channel);
#endif

#if ( CANIF_TRANSCEIVER_API == STD_ON )
Std_ReturnType CanIf_SetTransceiverMode( uint8 Transceiver, CanIf_TransceiverModeType TransceiverMode );
Std_ReturnType CanIf_GetTransceiverMode( uint8 Transceiver, CanIf_TransceiverModeType *TransceiverModePtr );
Std_ReturnType CanIf_GetTrcvWakeupReason( uint8 Transceiver, CanIf_TrcvWakeupReasonType *TrcvWuReasonPtr );
Std_ReturnType CanIf_SetTransceiverWakeupMode( uint8 Transceiver, CanIf_TrcvWakeupModeType *TrcvWakeupMode );
#endif

#if ( CANIF_WAKEUP_EVENT_API == STD_ON )
Std_ReturnType CanIf_CheckWakeup( EcuM_WakeupSourceType WakeupSource );
Std_ReturnType CanIf_CheckValidation( EcuM_WakeupSourceType WakeupSource );
#endif

#if  ( CANIF_DEV_ERROR_DETECT == STD_ON )

#endif

#if ( CANIF_VERSION_INFO_API == STD_ON )
#define CanIf_GetVersionInfo(_vi) (STD_GET_VERSION_INFO((_vi),(CANIF)))
#endif

uint8 CanIf_Arc_GetChannelDefaultConfIndex(CanIf_Arc_ChannelIdType Channel);

CanControllerIdType ARC_GET_CHANNEL_CONTROLLER(uint8 channel);
void CanIf_PreInit_InitController(uint8 Controller, uint8 ConfigurationIndex);



//#if (CANIF_ARC_RUNTIME_PDU_CONFIGURATION ==STD_ON)
//static CanIf_Arc_ChannelIdType CanIf_Arc_FindHrhChannel( Can_Arc_HRHType hrh );
//#else
//static CanIf_Arc_ChannelIdType CanIf_Arc_FindHrhChannel( Can_Arc_HRHType hrh );
//#endif

static FUNC(Std_ReturnType,CANIF_CODE)CanIf_BufferPdu
(
 VAR(uint32,AUTOMATIC) BuffTxPduId,
 P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr
);

#endif /*CANIF_H_*/
