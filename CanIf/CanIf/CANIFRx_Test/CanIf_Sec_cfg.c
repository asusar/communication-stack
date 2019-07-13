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
#include "AVECORE_CANIF.h"

extern const CanIf_HrhConfigType CanIf_hrhConfigTypeInstance[];

CanIF_RxPDUCbkConfig CanIF_RxPDUCbkConfig_a[1]={
		{		CANIF_USER_TYPE_CAN_SPECIAL
				,
				CanIfUserRxIndication
		}

};

CanIF_TxPDUCbkConfig CanIF_TxPDUCbkConfig_a[1]={
		{		CANIF_USER_TYPE_CAN_SPECIAL
				,
				CanIfUserTxConfirmation
		}

};


Can_ControllerConfigType Can_controllerConfigTypeInstace = {CAN_ARC_PROCESS_TYPE_INTERRUPT,TRUE,9600,CAN_CTRL_1,4,1,1,2,CAN_ARC_PROCESS_TYPE_INTERRUPT
		,CAN_ARC_PROCESS_TYPE_INTERRUPT,CAN_ARC_PROCESS_TYPE_INTERRUPT};

CanIf_ControllerConfigType CanIf_controllerConfigTypeInstance[3] = {
		{CANIF_WAKEUP_SUPPORT_NO_WAKEUP,CANIF_Channel_1}
		,{CANIF_WAKEUP_SUPPORT_NO_WAKEUP,CANIF_Channel_1}
		,{CANIF_WAKEUP_SUPPORT_NO_WAKEUP,CANIF_Channel_1}
};

/** Reference to controller Id to which the HTH belongs to. A controller
 *  can contain one or more HTHs */

VAR(CanIf_Arc_ChannelIdType,AUTOMATIC) CanIfCanControllerIdRefHth[]=
{
		CANIF_Channel_1,CANIF_Channel_1,CANIF_Channel_1,CANIF_Channel_1,CANIF_Channel_1
};


CanIf_HrhRangeConfigType CanIf_hrhRangeConfigTypeInstance = {1,900};

/** The parameter refers to a particular HRH object in the CAN Driver Module
 *  configuration. The HRH id is unique in a given CAN Driver. The HRH Ids
 *  are defined in the CAN Driver Module and hence it is derived from CAN
 *  Driver Configuration. */
VAR(CanIf_Arc_ChannelIdType,AUTOMATIC) CanIfCanControllerIdRefHrh[]=
{
		CANIF_Channel_1,CANIF_Channel_1,CANIF_Channel_1,CANIF_Channel_1,CANIF_Channel_1
};


/*array of all the buffers*/
CanIf_TxBufferCfg_t TxBufferCfg[]={
		{&BuffPool[0],0,8},
		{&BuffPool[8],1,8},
		{&BuffPool[16],2,8},
		{&BuffPool[24],3,8},
		{&BuffPool[32],4,8}
};




CanIf_RxPduConfigType CanIf_rxPduConfigTypeInstance[5] = {
		{0,10,8,CANIF_CAN_ID_TYPE_11,0,&(CanIf_hrhConfigTypeInstance[0]),0}
		,{1,11,8,CANIF_CAN_ID_TYPE_11,0,&(CanIf_hrhConfigTypeInstance[1]),0},
		{2,12,8,CANIF_CAN_ID_TYPE_11,0,&(CanIf_hrhConfigTypeInstance[2]),0},
		{3,13,8,CANIF_CAN_ID_TYPE_11,0,&(CanIf_hrhConfigTypeInstance[3]),0},
		{4,14,8,CANIF_CAN_ID_TYPE_11,0,&(CanIf_hrhConfigTypeInstance[4]),0}
};


CanIf_TxPduConfigType CanIf_txPduConfigTypeInstance[5] = {
		{5,15,8,CANIF_PDU_TYPE_STATIC,CANIF_CAN_ID_TYPE_11,0,&(TxBufferCfg[1]),NULL},
		{6,16,8,CANIF_PDU_TYPE_STATIC,CANIF_CAN_ID_TYPE_11,0,&(TxBufferCfg[1]),NULL},
		{7,17,8,CANIF_PDU_TYPE_STATIC,CANIF_CAN_ID_TYPE_11,0,&(TxBufferCfg[2]),NULL},
		{8,18,8,CANIF_PDU_TYPE_STATIC,CANIF_CAN_ID_TYPE_11,0,&(TxBufferCfg[3]),NULL},
		{9,19,8,CANIF_PDU_TYPE_STATIC,CANIF_CAN_ID_TYPE_11,0,&(TxBufferCfg[4]),NULL}
};

CanIf_InitConfigType CanIf_initConfigTypeInstace = {0,5,5,0,CanIfCanControllerIdRefHrh,CanIfCanControllerIdRefHth,CanIf_rxPduConfigTypeInstance,CanIf_txPduConfigTypeInstance,};

CanIf_TransceiverConfigType CanIf_transceiverConfigTypeInstance = {0};
CanControllerIdType canControllerIdType[3] = {0,1,2};

uint8 Configuration_arr[1] = {0};

const CanIf_ConfigType CanIf_configTypeInstance = {CanIf_controllerConfigTypeInstance,&CanIf_initConfigTypeInstace
		,&CanIf_transceiverConfigTypeInstance,canControllerIdType,Configuration_arr};
