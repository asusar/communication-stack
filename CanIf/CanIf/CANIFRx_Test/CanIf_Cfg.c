
#include "CanIf.h"
#if defined(USE_CANTP)
#include "CanTp.h"
#include "CanTp_Cbk.h"
#endif
#if defined(USE_J1939TP)
#include "J1939Tp.h"
#include "J1939Tp_Cbk.h"
#endif
/* #if defined(USE_PDUR) */
#include "PduR.h"
#include "PduR_CanIf.h"
#include "PduR_PbCfg.h"
/*#endif */
#if defined(USE_CANNM)
#include "CanNm_Cbk.h"
#endif
#include <stdlib.h>
#include "Can_Cfg.h"

/* Imported structs from Can_Lcfg.c */
/* extern const Can_ControllerConfigType CanControllerConfigData[]; */

extern const Can_ConfigSetType CanConfigSetData;

/* Contains the mapping from CanIf-specific Channels to Can Controllers */
const CanControllerIdType CanIf_Arc_ChannelToControllerMap[CANIF_CHANNEL_CNT] = {
	DCAN1, /* Channel_1 */
};

const uint8 CanIf_Arc_ChannelDefaultConfIndex[CANIF_CHANNEL_CNT] = {
	CANIF_Channel_1_CONFIG_0,
};

/* Container that gets slamed into CanIf_InitController() */
/* Inits ALL controllers */
/* Multiplicity 1..* */
const CanIf_ControllerConfigType CanIfControllerConfig[] = {
	// This is the ConfigurationIndex in CanIf_InitController()
	{
		.WakeupSupport = CANIF_WAKEUP_SUPPORT_NO_WAKEUP,
		.CanIfControllerIdRef = CANIF_Channel_1,
		//.CanIfDriverNameRef = "FLEXCAN",  /* Not used */
		//.CanIfInitControllerRef = &CanControllerConfigData[0],
	},

};


/* Data for init configuration CanIfInitConfiguration */



const CanIf_HthConfigType CanIfHthConfigData_Hoh_1[] =
{

  {
    .CanIfHthType = CAN_ARC_HANDLE_TYPE_BASIC,
    .CanIfHthIdSymRef = HWObj_2,
    .CanIf_Arc_EOL_Mod = (uint8)1,
  },
};

const CanIf_HrhConfigType CanIfHrhConfigData_Hoh_1[] =
{

  {
    .CanIfHrhType = CAN_ARC_HANDLE_TYPE_BASIC,
    .CanIfSoftwareFilterHrh = (uint8) TRUE,
    .CanIfCanControllerHrhIdRef = CANIF_Channel_1,
    .CanIf_Arc_EOL =(uint8) 1,
  },
};



CanIf_TxBufferCfg_t TxBufferCfg1[]={
		{&BuffPool[0],0,8},
};

const CanIf_TxPduConfigType CanIfTxPduConfigData[] = {  //1stMina
  {
    .CanIfTxPduId = (uint32) PDUR_REVERSE_PDU_ID_TX_PDU,
    .CanIfCanTxPduIdCanId = (uint32)1,
    .CanIfCanTxPduIdDlc = (uint8) 8,
    .CanIfCanTxPduType = CANIF_PDU_TYPE_STATIC,
#if ( CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON )
    .CanIfReadTxPduNotifyStatus = false,
#endif
    .CanIfTxPduIdCanIdType = CANIF_CAN_ID_TYPE_11,
   // .CanIfUserTxConfirmation = (void (*)(PduIdType x) ) &PduR_CanIfTxConfirmation,
    .CanIfUserTxIndex=0,
	.CanIfTxBufferRef = &TxBufferCfg1[0],
    .PduIdRef = (void *)NULL,
  },
  {
    .CanIfTxPduId =(uint32) PDUR_REVERSE_PDU_ID_FreqInd,
    .CanIfCanTxPduIdCanId = (uint32) 258,
    .CanIfCanTxPduIdDlc =(uint8) 8,
    .CanIfCanTxPduType = CANIF_PDU_TYPE_STATIC,
#if ( CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON )
    .CanIfReadTxPduNotifyStatus = false,
#endif
    .CanIfTxPduIdCanIdType = CANIF_CAN_ID_TYPE_11,
    //.CanIfUserTxConfirmation = (void (*)(PduIdType x)) &PduR_CanIfTxConfirmation,
    .CanIfUserTxIndex=0,
	.CanIfTxBufferRef = &TxBufferCfg1[0],
    .PduIdRef = (void *)NULL,
  },
};

const CanIf_RxPduConfigType CanIfRxPduConfigData[] = {
  {
    .CanIfCanRxPduId = (uint32) PDUR_PDU_ID_RX_PDU,
    .CanIfCanRxPduCanId =(uint32) 1,
    .CanIfCanRxPduDlc = (uint8) 8,
#if ( CANIF_CANPDUID_READDATA_API == STD_ON )
    .CanIfReadRxPduData = false,
#endif
#if ( CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON )
    .CanIfReadRxPduNotifyStatus = false,
#endif

    .CanIfCanRxPduHrhRef = &CanIfHrhConfigData_Hoh_1[0],
    .CanIfRxPduIdCanIdType = CANIF_CAN_ID_TYPE_11,
	.CanIfRxPduCallBackInd=0,
    //.CanIfSoftwareFilterType = CANIF_SOFTFILTER_TYPE_MASK, Private for all
    .CanIfCanRxPduCanIdMask = (uint32)0xFFF,
    .PduIdRef_Mod = (void*) NULL,
  },
  {
    .CanIfCanRxPduId = (uint32) PDUR_PDU_ID_FreqReq,
    .CanIfCanRxPduCanId = (uint32) 256,
    .CanIfCanRxPduDlc = (uint8)8,
#if ( CANIF_CANPDUID_READDATA_API == STD_ON )
    .CanIfReadRxPduData = false,
#endif
#if ( CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON )
    .CanIfReadRxPduNotifyStatus = false,
#endif
    .CanIfCanRxPduHrhRef = &CanIfHrhConfigData_Hoh_1[0],
    .CanIfRxPduIdCanIdType = CANIF_CAN_ID_TYPE_11,
    .CanIfRxPduCallBackInd=0,
    //.CanIfSoftwareFilterType = CANIF_SOFTFILTER_TYPE_MASK,
    .CanIfCanRxPduCanIdMask = (uint32)0xFFF,
    .PduIdRef_Mod =(void*) NULL,
  },
};

/* This container contains the init parameters of the CAN */
/* Multiplicity 1..* */
const CanIf_InitConfigType CanIfInitConfig =
{
  .CanIfConfigSet = (uint32) 0, /* Not used   */
  .CanIfNumberOfCanRxPduIds = (uint32)2,
  .CanIfNumberOfCanTXPduIds = (uint32)2,
  .CanIfNumberOfDynamicCanTXPduIds =(uint32) 0, /* Not used */

  /* Containers */
  .CanIfRxPduConfigPtr = CanIfRxPduConfigData,
  .CanIfTxPduConfigPtr = CanIfTxPduConfigData,
};

	/* This container includes all necessary configuration sub-containers */
/* according the CAN Interface configuration structure. */
CanIf_ConfigType CanIf_Config =
{
  .ControllerConfig = CanIfControllerConfig,
 /* .DispatchConfig = &CanIfDispatchConfig,*/
  .InitConfig = &CanIfInitConfig,
  .TransceiverConfig = (const CanIf_TransceiverConfigType *)NULL, /* Not used */
  .Arc_ChannelToControllerMap = CanIf_Arc_ChannelToControllerMap,
  .Arc_ChannelDefaultConfIndex = CanIf_Arc_ChannelDefaultConfIndex,
};

#if CANIF_UNIT_TESTING == STD_ON


const CanIf_TxPduConfigType CanIfTxPduConfigData_Test[] = {
  {
    .CanIfTxPduId = (uint32) PDUR_REVERSE_PDU_ID_FreqInd,
    .CanIfCanTxPduIdCanId = (uint32)0,
    .CanIfCanTxPduIdDlc = (uint8) 8,
    .CanIfCanTxPduType = CANIF_PDU_TYPE_STATIC,
#if ( CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON )
    .CanIfReadTxPduNotifyStatus = false,
#endif
    .CanIfTxPduIdCanIdType = CANIF_CAN_ID_TYPE_11,
   // .CanIfUserTxConfirmation = (void (*)(PduIdType x) ) &PduR_CanIfTxConfirmation,
	.CanIfTxBufferRef = &TxBufferCfg1[0],
    .PduIdRef = (void *)NULL,
  },
  {
    .CanIfTxPduId =(uint32) PDUR_REVERSE_PDU_ID_TX_PDU,
    .CanIfCanTxPduIdCanId = (uint32) 1,
    .CanIfCanTxPduIdDlc =(uint8) 8,
    .CanIfCanTxPduType = CANIF_PDU_TYPE_STATIC,
#if ( CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON )
    .CanIfReadTxPduNotifyStatus = false,
#endif
    .CanIfTxPduIdCanIdType = CANIF_CAN_ID_TYPE_11,
    //.CanIfUserTxConfirmation = (void (*)(PduIdType x)) NULL, MentorTx
	.CanIfUserTxIndex=0,
	.CanIfTxBufferRef = &TxBufferCfg1[0],
    .PduIdRef = (void *)NULL,
  },
};

/* This container contains the init parameters of the CAN */
/* Multiplicity 1..* */
const CanIf_InitConfigType CanIfInitConfig_Test =
{
  .CanIfConfigSet = (uint32) 0, /* Not used   */
  .CanIfNumberOfCanRxPduIds = (uint32)2,
  .CanIfNumberOfCanTXPduIds = (uint32)2,
  .CanIfNumberOfDynamicCanTXPduIds =(uint32) 0, /* Not used */

  /* Containers */
  .CanIfRxPduConfigPtr = CanIfRxPduConfigData,
  .CanIfTxPduConfigPtr = CanIfTxPduConfigData_Test,
};

/* This container includes all necessary configuration sub-containers */
/* according the CAN Interface configuration structure. */
CanIf_ConfigType CanIf_Config_Test =
{
.ControllerConfig = CanIfControllerConfig,
/*.DispatchConfig = &CanIfDispatchConfig,*/
.InitConfig = &CanIfInitConfig_Test,
.TransceiverConfig = (const CanIf_TransceiverConfigType *)NULL, /* Not used */
.Arc_ChannelToControllerMap = CanIf_Arc_ChannelToControllerMap,
.Arc_ChannelDefaultConfIndex = CanIf_Arc_ChannelDefaultConfIndex,
};
#endif
