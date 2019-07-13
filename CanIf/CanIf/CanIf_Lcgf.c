/*
 * Copyright (c) 2018-2019 Faculty of Engineering Ain Shams University Dr.Sherif Hammad Email: Sherif.hammad@eng.asu.edu.eg Eng.Mohamed abdelhay Email: mhmd.a.elhay@gmail.com.
 *
 * This file is part of ASUSAR
 * (see https://github.com/asusar/communication-stack).
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
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
#include "Can_Driver/Can_Cfg.h"
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
