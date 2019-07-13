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
#include "PduR.h"

Std_ReturnType PduR_CancelTransmitRequest(
		PduR_CancelReasonType PduCancelReason, uint32 PduId){return PDU_CNLDO;}
void PduR_ChangeParameterRequest(PduR_ParameterValueType PduParameterValue,
		uint32 PduId){}
		
void PduR_Init(const PduR_PBConfigType* ConfigPtr){}
void PduR_GetVersionInfo(Std_VersionInfoType* versionInfo){}
uint32 PduR_GetConfigurationId(void){return 0;}

void PduR_BufferInc(PduRTxBuffer_type *Buffer, uint8 **ptr){}
void PduR_BufferQueue(PduRTxBuffer_type *Buffer, const uint8 * SduPtr){}
void PduR_BufferDeQueue(PduRTxBuffer_type *Buffer, uint8 *SduPtr){}
void PduR_BufferFlush(PduRTxBuffer_type *Buffer){}
uint8 PduR_BufferIsFull(PduRTxBuffer_type *Buffer){return 0;}
void PduR_LoIfRxIndication(uint32 PduId, const uint8* SduPtr){}
void PduR_LoIfTxConfirmation(uint32 PduId){}
void PduR_LoIfTriggerTransmit(uint32 PduId, uint8* SduPtr){}

