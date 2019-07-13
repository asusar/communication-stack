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

#ifndef COM_ASU_TYPES_H_
#define COM_ASU_TYPES_H_

#include "Com_Types.h"
#include "ComStack_Types.h"


typedef struct {

	uint32 Com_Asu_DeadlineCounter;
	uint8 ComSignalUpdated;
} Com_Asu_Signal_type;


typedef struct {
	uint16  ComTxIPduNumberOfRepetitionsLeft;
	uint16 ComTxModeRepetitionPeriodTimer;
	uint16 ComTxModeTimePeriodTimer;
} Com_Asu_TxIPduTimer_type;

typedef struct
{
    PduLengthType CurrentPosition;
    boolean Locked;
}PduBufferState_type;


typedef struct {

	Com_Asu_TxIPduTimer_type Com_Asu_TxIPduTimers;

	/* to check if the signal updated or not */
	boolean Com_Asu_IpduStarted;

	boolean Com_Asu_Pdu_changed;

	/* in case direct or mixed mode.
	 * this flag indicates whether this is the first transmission of the IPDU or not
	 */
	boolean Com_Asu_First_Repetition;
	uint16 Com_Asu_DynSignalLength;
	uint16 Com_Asu_DeferredDynSignalLength;
	uint64 Deffert;
	PduBufferState_type PduBufferState;
} Com_Asu_IPdu_type;




typedef struct {
	void *Com_Asu_ShadowBuffer;
	uint8 ComSignalUpdated;
	uint8 Com_Asu_EOL;
} Com_Asu_SignalGroup_type;

typedef struct {
	Com_Asu_IPdu_type *ComIPdu; // Only used in PduIdCheck()
	Com_Asu_Signal_type *ComSignal;
	Com_Asu_SignalGroup_type *ComSignalGroup;
} Com_Asu_Config_type;


#endif
