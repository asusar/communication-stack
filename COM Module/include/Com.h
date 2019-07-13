
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
 
#ifndef COM_H_
#define COM_H_


#include "ComStack_Types.h"
#include "Com_Cfg.h"
#include "Com_helper.h"
#include "Com_Cbk.h"
#include "PduR/include/PduR_Com.h"
#include "PduR/include/PduR.h"

//#include "Com_Types.h"  /* to be changed to ComStack_Types.h */

/************************************************************************
 *                          Preprocessor                                *
 ************************************************************************/

#define COM_BUSY 0x81



/************************************************************************
 *                      Functions Prototypes                            *
 ************************************************************************/

/*initializes internal and external interfaces and variables of the COM module */
void Com_Init( const ComConfig_type* config);
 
/* Processing of the AUTOSAR COM module's receive activities (PDU To Signal) */
void Com_MainFunctionRx(void);

/* Processing of the AUTOSAR COM module's transmission activities (Signal To PDU)*/
void Com_MainFunctionTx(void);

/* Updates the signal object identified by SignalId with the signal referenced by the SignalDataPtr parameter */
uint8 Com_SendSignal( Com_SignalIdType SignalId, const void* SignalDataPtr );

/* Copies the data of the signal identified by SignalId to the location specified by SignalDataPtr */
uint8 Com_ReceiveSignal( Com_SignalIdType SignalId, void* SignalDataPtr );
/* Copies the signal Group content from the i-pdu to the shadow buffer */
uint8 Com_ReceiveSignalGroup( Com_SignalGroupIdType SignalGroupId );
/* Copies the content of the shadow buffer to the specified i-pdu */
uint8 Com_SendSignalGroup( Com_SignalGroupIdType SignalGroupId );

/* the I-PDU with the given ID is triggered for transmission */
Std_ReturnType Com_TriggerIPDUSend( PduIdType PduId );

/* Cbk function, indation from the PduRouter of recieving Pdu */
//process signals if the signal processing mode is IMMEDIATE -> notify the signal callback , else -> mark signal as updated
static void Com_RxProcessSignals(PduIdType ComRxPduId);

#endif

