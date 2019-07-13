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

#include "include/Std_Types.h"
#include "include/Com_Asu_Types.h"
#include "include/Com_Types.h"
#include "include/Com_helper.h"
#include "include/Com_Cfg.h"
#include "include/Com_Buffer.h"


extern const ComConfig_type * ComConfig;

/* Com_Asu_Config declaration*/
extern Com_Asu_Config_type ComAsuConfiguration;
static Com_Asu_Config_type * Com_Asu_Config = &ComAsuConfiguration;

void Com_WriteSignalDataToShadowBuffer(Com_SignalIdType SignaGlId,Com_SignalIdType GSignalId,const void *GSignalDataPtr)
{
    uint32 bitPosition;
    uint8 data;
    uint8 mask;
    uint8 shadowMask;
    uint8 GsignalMask;
    uint8 *shadowBufferBytes = NULL;
    uint8 *shadowBeforChange = NULL;
    uint8 *dataBytes = NULL;
    uint8 GsignalLength;
    uint8 BitOffsetInByte;
    uint8 shadowStartByte;
    uint8 i;


    const ComGroupSignal_Type *GroupSignal=GET_GROUPSIGNAL(SignalGId,GSignalId);
    const ComSignalGroup_Type *SignalGroup = GET_SIGNALGROUP(SignaGlId);
    void *const shadowbuff=SignalGroup->Com_Asu_ShadowBuffer;


    bitPosition = GroupSignal->ComBitPosition;
    BitOffsetInByte = bitPosition%8;
    shadowStartByte = bitPosition / 8;
    shadowBufferBytes = (uint8 *)shadowbuff;
    dataBytes = (uint8 *) GSignalDataPtr;
    GsignalLength = GroupSignal->ComBitSize/8;
    shadowBeforChange = shadowBufferBytes;


    shadowBufferBytes += shadowStartByte;
    for(i = 0; i<=GsignalLength; i++)
    {
        shadowMask = 255;
        GsignalMask = 255;
        if( i == 0)
        {
            shadowMask = mask >> (8 - BitOffsetInByte);
            GsignalMask = GsignalMask >> BitOffsetInByte;
            *shadowBufferBytes = (* shadowBufferBytes) & shadowMask;
            data = (* dataBytes) & GsignalMask;
            data = data << BitOffsetInByte;
            *shadowBufferBytes = (* shadowBufferBytes) | data;
            shadowBufferBytes ++;
        }
        else if(i==GsignalLength)
        {
            shadowMask = mask << BitOffsetInByte;
            GsignalMask = GsignalMask << (8 - BitOffsetInByte);
            *shadowBufferBytes = (* shadowBufferBytes) & shadowMask;
            data = (* dataBytes) & GsignalMask;
            data = data >> (8 - BitOffsetInByte);
            *shadowBufferBytes = (* shadowBufferBytes) | data;
        }
        else
        {
            shadowMask = mask << BitOffsetInByte;
            GsignalMask = GsignalMask << (8 - BitOffsetInByte);
            *shadowBufferBytes = (* shadowBufferBytes) & shadowMask;
            data = (* dataBytes) & GsignalMask;
            data = data >> (8 - BitOffsetInByte);
            *shadowBufferBytes = (* shadowBufferBytes) | data;

            dataBytes++;

            shadowMask = 255;
            GsignalMask = 255;
            shadowMask = mask >> (8 - BitOffsetInByte);
            GsignalMask = GsignalMask >> BitOffsetInByte;
            *shadowBufferBytes = (* shadowBufferBytes) & shadowMask;
            data = (* dataBytes) & GsignalMask;
            data = data << BitOffsetInByte;
            *shadowBufferBytes = (* shadowBufferBytes) | data;
            shadowBufferBytes ++;

        }

    }

}

void Com_CopySignalGroupDataFromShadowBufferToPdu(const Com_SignalGroupIdTypeType signalGroupId)
{

    const ComSignalGroup_Type * SignalGroup=GET_SIGNALGROUP(signalGroupId);
    const ComIPdu_type *IPdu=GET_IPdu(SignalGroup->ComIPduHandleId);

    const uint8* mask;
    uint8 *pduDataPtr = 0;
    if (IPdu->ComIPduSignalProcessing == DEFERRED && IPdu->ComIPduDirection == RECEIVE) {
        pduDataPtr = IPdu->ComIPduDeferredDataPtr;
    } else {
        pduDataPtr = IPdu->ComIPduDataPtr;
    }
    // straight copy
    uint8 *buf = (uint8 *)SignalGroup->Com_Asu_ShadowBuffer;
        for(int i= 0; i < IPdu->ComIPduSize; i++){
            *pduDataPtr = (~mask[i] & *pduDataPtr) |
                          (mask[i] & *buf);
            buf++;
            pduDataPtr++;
        }

}

void Com_CopySignalGroupDataFromPduToShadowBuffer(const Com_SignalGroupIdType signalGroupId) {

    // Get PDU
    const ComSignalGroup_Type * SignalGroup = GET_SIGNALGROUP(signalGroupId);
    const ComIPdu_type *IPdu = GET_IPdu(SignalGroup->ComIPduHandleId);
    const uint8* mask;
    const uint8 *pduDataPtr = 0;
    if (IPdu->ComIPduSignalProcessing == DEFERRED && IPdu->ComIPduDirection == RECEIVE) {
        pduDataPtr = IPdu->ComIPduDeferredDataPtr;
    } else {
        pduDataPtr = IPdu->ComIPduDataPtr;
    }

    //straight copy with  mask
    uint8 *buf = (uint8 *)SignalGroup->Com_Asu_ShadowBuffer;
    for(int i= 0; i < IPdu->ComIPduSize; i++){
        *buf++ = mask[i] & *pduDataPtr++;
    }
}
void Com_PackSignalsToPdu(uint16 ComIPuId)
{
	uint8 signalID = 0;
	const ComIPdu_type *IPdu = GET_IPdu(ComIPuId);
	for ( signalID = 0; (IPdu->ComIPduSignalRef[signalID] != NULL); signalID++)
	{
		Com_WriteSignalDataToPduBuffer(IPdu->ComIPduSignalRef[signalID]->ComHandleId, IPdu->ComIPduSignalRef[signalID]->ComSignalDataPtr);
	}
}


void Com_UnPackSignalsFromPdu(uint16 ComIPuId)
{
	uint8 signalID = 0;
	const ComSignal_type * signal = NULL;
	const Com_Asu_Signal_type * Asu_Signal = NULL;
	const ComIPdu_type *IPdu = GET_IPdu(ComIPuId);

	for ( signalID = 0; (IPdu->ComIPduSignalRef[signalID] != NULL); signalID++)
	{
		signal = IPdu->ComIPduSignalRef[signalID];
		Asu_Signal = GET_AsuSignal(signal->ComHandleId);

		if(Asu_Signal->ComSignalUpdated)
		{
			Com_ReadSignalDataFromPduBuffer(IPdu->ComIPduSignalRef[signalID]->ComHandleId,IPdu->ComIPduSignalRef[signalID]->ComSignalDataPtr);
		}
	}
}


void Com_WriteSignalDataToPduBuffer(const uint16 signalId, const void *signalData)
{
	uint32 bitPosition;
	uint8 data;
	uint8 mask;
	uint8 pduMask;
	uint8 signalMask;
	uint8 *pduBufferBytes = NULL;
	uint8 *pduBeforChange = NULL;
	uint8 *dataBytes = NULL;
	uint8 signalLength;
	uint8 BitOffsetInByte;
	uint8 pduStartByte;
	uint8 i;
	Com_Asu_IPdu_type *Asu_IPdu = NULL;



	const ComSignal_type * Signal =  GET_Signal(signalId);
	// Get PDU
	const ComIPdu_type *IPdu = GET_IPdu(Signal->ComIPduHandleId);
	void * const pduBuffer = IPdu->ComIPduDataPtr;

	bitPosition = Signal->ComBitPosition;
	BitOffsetInByte = bitPosition%8;
	pduStartByte = bitPosition / 8;
	pduBufferBytes = (uint8 *)pduBuffer;
	dataBytes = (uint8 *) signalData;
	signalLength = Signal->ComBitSize/8;
	pduBeforChange = pduBufferBytes;

	pduBufferBytes += pduStartByte;
	for(i = 0; i<=signalLength; i++)
	{
	    pduMask = 255;
	    signalMask = 255;
        if( i == 0)
        {
            pduMask = mask >> (8 - BitOffsetInByte);
            signalMask = signalMask >> BitOffsetInByte;
            *pduBufferBytes = (* pduBufferBytes) & pduMask;
            data = (* dataBytes) & signalMask;
            data = data << BitOffsetInByte;
            *pduBufferBytes = (* pduBufferBytes) | data;
            pduBufferBytes ++;
        }
        else if(i==signalLength)
        {
            pduMask = mask << BitOffsetInByte;
            signalMask = signalMask << (8 - BitOffsetInByte);
            *pduBufferBytes = (* pduBufferBytes) & pduMask;
            data = (* dataBytes) & signalMask;
            data = data >> (8 - BitOffsetInByte);
            *pduBufferBytes = (* pduBufferBytes) | data;
        }
        else
        {
            pduMask = mask << BitOffsetInByte;
            signalMask = signalMask << (8 - BitOffsetInByte);
            *pduBufferBytes = (* pduBufferBytes) & pduMask;
            data = (* dataBytes) & signalMask;
            data = data >> (8 - BitOffsetInByte);
            *pduBufferBytes = (* pduBufferBytes) | data;

            dataBytes++;

            pduMask = 255;
            signalMask = 255;
            pduMask = mask >> (8 - BitOffsetInByte);
            signalMask = signalMask >> BitOffsetInByte;
            *pduBufferBytes = (* pduBufferBytes) & pduMask;
            data = (* dataBytes) & signalMask;
            data = data << BitOffsetInByte;
            *pduBufferBytes = (* pduBufferBytes) | data;
            pduBufferBytes ++;

        }

	}



//	data = *(const uint64 *)signalData;
//	mask = power(2,Signal->ComBitSize) - 1;
//	data = data & mask ;
//	data = data << BitOffsetInByte;

	//wrong example we forget to edit it see the documentation
	/* example
	 * if i want to write uint8 from bitposition = 9
	 * BitOffsetInByte will be 1
	 * we make a mask = 0000000000000000011111111111111111111111111111111111111111111111
	 * then shift it by 9 (bitposition) + 8 (length of data)
	 * so it will be 1111111111111111111111111111111111111111111111100000000000000000
	 * then or the mask with ones = 9 (bitposition)  --> 111111111
	 * so the mask will be  1111111111111111111111111111111111111111111111100000000111111111
	 */

//	mask = power (2,64) - 1;
//	mask = mask <<( BitOffsetInByte + Signal->ComBitSize );
//	mask = mask | ( power(2,BitOffsetInByte) - 1);
//	uint8 * ptr = (pduBufferBytes + pduStartByte);
//	uint64 * ptr64 = (uint64 *) ptr;
//	uint64 odata = *(uint64 *) ptr64;
//	odata = odata & mask;
//	* ptr64 = odata;
//	//*(uint64 *)(pduBufferBytes + pduStartByte) = (*(uint64 *)(pduBufferBytes + pduStartByte))& mask;
//	*(uint64 *)(pduBufferBytes + pduStartByte) = (*(uint64 *)(pduBufferBytes + pduStartByte))| data;
//	if(*(uint64 *)(pduBufferBytes + pduStartByte) != *(uint64 *)(pduBeforChange + pduStartByte))
//	{
//		Asu_IPdu = GET_AsuIPdu(Signal->ComIPduHandleId);
//		Asu_IPdu->Com_Asu_Pdu_changed = TRUE;
//	}

}



void Com_ReadSignalDataFromPduBuffer(const uint16 signalId, void *signalData)
{
	uint8 signalLength;
	uint32 bitPosition;
	uint64 data;
	uint8 numOfBits;
	uint8 BitOffsetInByte;
	uint8 pduStartByte;
	uint64 mask;
	const uint8 *pduBufferBytes = NULL;
	uint8 * signalDataBytes = NULL;

	const ComSignal_type * Signal = GET_Signal(signalId);
	const ComIPdu_type *IPdu = GET_IPdu(Signal->ComIPduHandleId);
	const void * pduBuffer = IPdu->ComIPduDataPtr;

	bitPosition = Signal->ComBitPosition;
	signalLength = Signal->ComBitSize / 8;
	BitOffsetInByte = bitPosition % 8;
	pduStartByte = bitPosition / 8;

	signalDataBytes = (uint8 *) signalData;

	pduBufferBytes = (const uint8 *)pduBuffer;

	numOfBits = Signal->ComBitSize;
	mask = power (2,numOfBits) - 1;
	mask = mask << BitOffsetInByte;

	data = (* (uint64 *)(pduBufferBytes + pduStartByte)) & mask;
	data = data >> BitOffsetInByte;

	memcpy(signalDataBytes, &data, signalLength);


}



void Com_WriteSignalDataToSignalBuffer (const uint16 signalId, const void * signalData)
{
	const ComSignal_type * Signal =  GET_Signal(signalId);
	memcpy(Signal->ComSignalDataPtr, signalData, Signal->ComBitSize/8);
}


void Com_ReadSignalDataFromSignalBuffer (const uint16 signalId,  void * signalData)
{
	const ComSignal_type * Signal =  GET_Signal(signalId);
	memcpy(signalData, Signal->ComSignalDataPtr, Signal->ComBitSize/8);
}



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



