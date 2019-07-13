
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
#ifndef COM_HELPHER_H_
#define COM_HELPER_H_

// set bit in specific bit
#define SETBIT(dest,bit)	( *( (uint8 *)dest    + (bit / 8) ) |= (uint8)(1u << (bit % 8)) )

// clear bit in specific bit
#define CLEARBIT(dest,bit)	( *( (uint8 *)dest    + (bit / 8) ) &= (uint8)~(uint8)(1u << (bit % 8)) )

// get bit value
#define CHECKBIT(source,bit)	( *( (uint8 *)source  + (bit / 8) ) &  (uint8)(1u << (bit % 8)) )

// Signal group helper macros //

//check signal type returns 1 if it's ordinary signal and 0 if it's group signal
#define GET_SIGNAL_TYPE(SignalID)\
    (if(SignalID<COM_NUM_OF_SIGNAL))

#define GET_GROUPSIGNAL(SignalGroupId,GroupSignalId)\
    ((&(ComConfig->ComSignalGroup[SignalGroupId]->ComGroupSignal[GroupSignalId])))


#define GET_SIGNALGROUP(id)\
    ((&(ComConfig->ComSignalGroup[id])))

#define GET_ASUSIGNALGROUP(id)\
    (&(Com_Asu_Config->ComSignalGroup[id]))

// Signal group helper macros //

#define GET_Signal(SignalId) \
	(&(ComConfig->ComSignal[SignalId]))


#define GET_IPdu(IPduId) \
	(&(ComConfig->ComIPdu[IPduId]))


#define GET_AsuIPdu(IPduId) \
	(&(Com_Asu_Config->ComIPdu[IPduId]))

#define GET_AsuSignal(SignalId)\
	(&(Com_Asu_Config->ComSignal[SignalId]))

boolean validateSignalID (Com_SignalIdType SignalId);

#define timerDec(timer) \
	if (timer > 0) { \
		timer = timer - ComConfig->ComTimeBase.ComTxTimeBase; \
	}

uint64 power(uint8 x,uint8 y);
boolean compare_float(uint64 f1, uint64 f2);

#endif
