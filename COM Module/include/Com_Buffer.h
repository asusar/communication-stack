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

#ifndef INCLUDE_COM_BUFFER_H_
#define INCLUDE_COM_BUFFER_H_


//#define isBufferLocked(IPdubufStateptr) ((boolean)*(IPdubufStateptr).Locked)

#define UNLOCKBUFFER(IPdubufStateptr) \
         *IPdubufStateptr.Locked=FALSE;\
         *IPdubufStateptr.CurrentPosition=0;

#define LOCKBUFFER(IPdubufStateptr) \
		*IPdubufStateptr.Locked=TRUE;

void Com_PackSignalsToPdu(uint16 ComIPuId);

void Com_UnPackSignalsFromPdu(uint16 ComIPuId);

void Com_WriteSignalDataToShadowBuffer(Com_SignalIdType SignaGlId,Com_SignalIdType GSignalid,const void *SignalDataPtr);

void Com_CopySignalGroupDataFromShadowBufferToPdu(const Com_SignalGroupIdTypeType signalGroupId);

void Com_CopySignalGroupDataFromPduToShadowBuffer(const Com_SignalGroupIdType signalGroupId);

void Com_WriteSignalDataToPduBuffer(const uint16 signalId, const void *signalData);

void Com_ReadSignalDataFromPduBuffer(const uint16 signalId, void *signalData);

void Com_WriteSignalDataToSignalBuffer (const uint16 signalId, const void * signalData);

void Com_ReadSignalDataFromSignalBuffer (const uint16 signalId,  void * signalData);

//void inline unlockBuffer(PduIdType id)
//{
//	Com_Asu_IPdu_type *Asu_IPdu = GET_AsuIPdu(id);
//    Asu_IPdu->PduBufferState.Locked=FALSE;
//    Asu_IPdu->PduBufferState.CurrentPosition=0;
//}

//void inline lockBuffer(PduIdType id)
//{
//	Com_Asu_IPdu_type *Asu_IPdu = GET_AsuIPdu(id);
//	Asu_IPdu->PduBufferState.Locked=TRUE;
//}




#endif /* INCLUDE_COM_BUFFER_H_ */
