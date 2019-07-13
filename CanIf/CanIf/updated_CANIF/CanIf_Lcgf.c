/*
 * CanIf_Lcgf.c
 *
 *  Created on: Nov 15, 2017
 *      Author: Ahmed.Abdelmoniem
 */

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
#include "E:\merged_partition_content\MCT\GradProject\Final Phase testing and integration\Integration-20190619T083804Z-001\Integration\Can_Driver/Can_Cfg.h"
#include "AVECORE_CANIF.h" // upper layer function place

extern CanIf_HrhRangeConfigType CanIf_hrhRangeConfigTypeInstance;

//const CanIf_DispatchConfigType CanIf_DispatchConfigInstance = {CanIfBusOffNotification,CanIfCtrlModeIndication
//		,CanIfTrcvModeIndication,NULL};

const CanIf_HthConfigType CanIf_hthConfigTypeInstance[] = {
		{CAN_ARC_HANDLE_TYPE_BASIC,HWObj_6,FALSE},
		{CAN_ARC_HANDLE_TYPE_BASIC,HWObj_7,FALSE},
		{CAN_ARC_HANDLE_TYPE_BASIC,HWObj_8,FALSE},
		{CAN_ARC_HANDLE_TYPE_BASIC,HWObj_9,FALSE},
		{CAN_ARC_HANDLE_TYPE_BASIC,HWObj_10,TRUE}
};

CanIf_HrhConfigType CanIf_hrhConfigTypeInstance[] = {
		{CAN_ARC_HANDLE_TYPE_BASIC,TRUE,HWObj_1,&CanIf_hrhRangeConfigTypeInstance,FALSE},
		{CAN_ARC_HANDLE_TYPE_BASIC,TRUE,HWObj_2,&CanIf_hrhRangeConfigTypeInstance,FALSE},
		{CAN_ARC_HANDLE_TYPE_BASIC,TRUE,HWObj_3,&CanIf_hrhRangeConfigTypeInstance,FALSE},
		{CAN_ARC_HANDLE_TYPE_BASIC,TRUE,HWObj_4,&CanIf_hrhRangeConfigTypeInstance,FALSE},
		{CAN_ARC_HANDLE_TYPE_BASIC,TRUE,HWObj_5,&CanIf_hrhRangeConfigTypeInstance,TRUE}
};


CanIf_TxBuffPduInfo_t buffer_a[BUFFER_MAX];
