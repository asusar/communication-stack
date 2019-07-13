
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
#include "include/Com_Types.h"
#include "include/Com_Cfg.h"

/* signals Buffer */
uint8 ComSignalBuffer_1 [2];
uint8 ComSignalBuffer_2 [1];
uint8 ComSignalBuffer_3 [4];
uint8 ComSignalBuffer_4 [2];
uint8 ComSignalBuffer_5 [1];
uint8 ComSignalBuffer_6 [4];
uint8 ComSignalBuffer_7 [1];
uint8 ComSignalBuffer_8 [4];

/* Com Group Signal Buffer  */
uint8 ComGSignalBuffer_0 [1];
uint8 ComGSignalBuffer_1 [2];
uint8 ComGSignalBuffer_2 [4];
uint8 ComGSignalBuffer_3 [4];

/* shadow buffers */
uint8 ComShadowBuffer_0 [1];
uint8 ComShadowBuffer_1 [4];
uint8 ComShadowBuffer_2 [2];





//

const ComGroupSignal_Type ComGSignals[]=
{
 {    // Group signal 1
       .ComBitPosition= 0,
       .ComHandleId= 0 ,
       .ComBitSize= 16,
       .ComSignalGroupId=0,
       .ComSignalType = UINT16,
       .ComTransferProperty = TRIGGERED_ON_CHANGE,
       .ComSignalDataPtr=ComGSignalBuffer_0
   },
   //group signal 2
   {
    .ComHandleId=1,
    .ComBitPosition=0,
    .ComSignalGroupId=0,
    .ComBitSize=8,
    .ComSignalType=UINT8,
    .ComTransferProperty=TRIGGERED_ON_CHANGE,
    .ComSignalDataPtr=ComGSignalBuffer_1
   },
   //group signal 3
   {
    .ComHandleId=2,
    .ComBitPosition=0,
    .ComSignalGroupId=1,
    .ComBitSize=8,
    .ComSignalType=UINT8,
    .ComTransferProperty=TRIGGERED_ON_CHANGE,
    .ComSignalDataPtr=ComGSignalBuffer_2
   },
   //group signal 4
   {
    .ComHandleId=3,
    .ComBitPosition=0,
    .ComSignalGroupId=1,
    .ComBitSize=8,
    .ComSignalType=UINT8,
    .ComTransferProperty=PENDING,
    .ComSignalDataPtr=ComGSignalBuffer_3
   }
};


const ComSignal_type ComSignal[] = 
{

    {	//signal1
        .ComBitPosition= 17,
        .ComUpdateBitPosition= 25,
        .ComHandleId= 1 ,
        .ComBitSize= 8,
        .ComSignalType = BOOLEAN,
        .ComTransferProperty = TRIGGERED_ON_CHANGE,
        .ComIPduHandleId=0,
		.ComNotification=NULL,
		.ComSignalDataPtr = ComSignalBuffer_1
    },
    {	//signal2
        .ComBitPosition= 26,
        .ComUpdateBitPosition= 58 ,
        .ComHandleId= 2 ,
        .ComBitSize= 32,
        .ComSignalType = UINT32,
        .ComTransferProperty = TRIGGERED_ON_CHANGE,
        .ComIPduHandleId=0,
		.ComNotification=NULL,
		.ComSignalDataPtr = ComSignalBuffer_2
    },
    {   //signal0
        .ComBitPosition= 0,
        .ComUpdateBitPosition= 16 ,
        .ComHandleId= 3 ,
        .ComBitSize= 16,
        .ComSignalType = UINT16,
        .ComTransferProperty = TRIGGERED_ON_CHANGE,
        .ComIPduHandleId=1,
        .ComSignalDataPtr = ComSignalBuffer_3
    },
    {   //signal1
        .ComBitPosition= 17,
        .ComUpdateBitPosition= 25,
        .ComHandleId= 4 ,
        .ComBitSize= 8,
        .ComSignalType = BOOLEAN,
        .ComTransferProperty = TRIGGERED_ON_CHANGE,
        .ComIPduHandleId=1,
        .ComNotification=NULL,
        .ComSignalDataPtr = ComSignalBuffer_4
    },
    {   //signal2
        .ComBitPosition= 26,
        .ComUpdateBitPosition= 58 ,
        .ComHandleId= 5 ,
        .ComBitSize= 32,
        .ComSignalType = UINT32,
        .ComTransferProperty = TRIGGERED_ON_CHANGE,
        .ComIPduHandleId=1,
        .ComNotification=NULL,
        .ComSignalDataPtr = ComSignalBuffer_5
    },
    {	//signal3
        .ComBitPosition= 0,
        .ComUpdateBitPosition= 16 ,
        .ComHandleId= 6 ,
        .ComBitSize= 16,
        .ComSignalType = UINT16,
        .ComTransferProperty = TRIGGERED,
        .ComIPduHandleId=2,
		.ComNotification=NULL,
		.ComSignalDataPtr = ComSignalBuffer_6

    },
    {	//signal4
        .ComBitPosition= 17,
        .ComUpdateBitPosition= 33 ,
        .ComHandleId= 4 ,
        .ComBitSize= 16,
        .ComSignalType = UINT16,
        .ComTransferProperty = TRIGGERED_ON_CHANGE_WITHOUT_REPETITION,
        .ComIPduHandleId=1,
		.ComNotification=NULL,
		.ComSignalDataPtr = ComSignalBuffer_7
    },
    {   //signal5
        .ComBitPosition= 0,
        .ComUpdateBitPosition= 64 ,
        .ComHandleId= 5,
        .ComBitSize= 64,
        .ComSignalType = UINT64,
        .ComTransferProperty = TRIGGERED_ON_CHANGE_WITHOUT_REPETITION,
        .ComIPduHandleId=2,
		.ComNotification=NULL,
		.ComSignalDataPtr = ComSignalBuffer_8
    }

};
/* group signal with different imagination :) */
//const ComGroupSignal_Type * const groupS0[]={
//       &ComSignal[0],
//       &ComSignal[1]
//};
//
//const ComGroupSignal_Type *const groupS1[]={
//  &ComSignal[2],
//  &ComSignal[3],
//  &ComSignal[4]
//};

/* Group signals of signal groups */
const ComGroupSignal_Type * const ComSignalGroup_GroupSignalsRefs1[]={
     &ComGSignals[ 0 ],
     &ComGSignals[ 1 ],
     NULL
};

const ComGroupSignal_Type * const ComSignalGroup_GroupSignalsRefs2[]={
     &ComGSignals[ 2 ],
     &ComGSignals[ 3 ],
     NULL
};

/* IPdu signal lists. */
const ComSignal_type * const ComIPduSignalRefs_Can_Message_1[] = {
    &ComSignal[ CanDB_Signal_32_21_BE_Tester ],
    &ComSignal[ CanDB_Signal_1_4_LE_Tester ],
    &ComSignal[ CanDB_Signal_45_12_LE_Tester ],
	NULL
};

const ComSignal_type * const ComIPduSignalRefs_Can_Message_2[] = {
    &ComSignal[ CanDB_Signal_32_21_BE ],
    &ComSignal[ CanDB_Signal_29_12_BE_Tester],
    &ComSignal[ CanDB_Signal_1_4_LE ],
	NULL
};
const ComSignal_type * const ComIPduSignalRefs_Can_Message_3[] = {
    &ComSignal[ CanDB_Signal_1_4_LE ],
    NULL
};
/* signal group list */
const ComSignalGroup_Type  ComSignalGroup[]={
    {
      .ComHandleId=0,
      .ComUpdateBitPosition=17,
      .ComTransferProperty=TRIGGERED_ON_CHANGE,
      .ComGroupSignal=ComSignalGroup_GroupSignalsRefs1,
      .Com_Asu_ShadowBuffer=ComShadowBuffer_0
     },
     {
      .ComHandleId=1,
      .ComUpdateBitPosition=26,
      .ComTransferProperty=TRIGGERED_ON_CHANGE,
      .ComGroupSignal=ComSignalGroup_GroupSignalsRefs2,
      .Com_Asu_ShadowBuffer=ComShadowBuffer_1
     }
};

/* IPdu buffers and signal */
uint8 ComIPduBuffer_1[8];

uint8 ComIPduBuffer_2[8];

uint8 ComIPduBuffer_3[8];

/* Com Ipdu */
const ComIPdu_type ComIPdu[] = 
{
    { // CanDB_Message_1
        .ComIPduDirection = SEND ,
		.ComIPduSize=8,
        .ComIPduHandleId = 0 ,
        .ComIPduSignalRef =ComIPduSignalRefs_Can_Message_1,
		.ComIPduDataPtr=ComIPduBuffer_1,
        .ComTxIPdu =
        {
             .ComTxModeFalse =
             {
                  .ComTxMode=
                  {
                    .ComTxModeMode = PERIODIC,
                    .ComTxModeNumberOfRepetitions = 2,
					.ComTxModeTimePeriod=500,
					.ComTxModeRepetitionPeriod=15
                  }
             },
						 
             .ComMinimumDelayTime = 0,
             .ComTxIPduUnusedAreasDefault = 255,
						 
        }
    },
    { // CanDB_Message_2
        .ComIPduDirection = RECEIVE ,
		.ComIPduSize=8,
		.ComIPduSignalProcessing = IMMEDIATE,
        .ComIPduHandleId = 1 ,
        .ComIPduSignalRef = ComIPduSignalRefs_Can_Message_2,
		.ComIPduDataPtr=ComIPduBuffer_2,
        /*.ComTxIPdu =
        {
             .ComTxModeFalse =
             {
                  .ComTxMode=
                  {
                    .ComTxModeMode = DIRECT,
                    .ComTxModeNumberOfRepetitions = 10,
					.ComTxModeTimePeriod=500,
                    .ComTxModeRepetitionPeriod=200
                  }
             },
             .ComMinimumDelayTime = 0,
             .ComTxIPduUnusedAreasDefault = 0,
        }*/
    },
    { // CanDB_Message_2
          .ComIPduDirection = SEND ,
           .ComIPduSize=8,
          .ComIPduHandleId = 2 ,
          .ComIPduSignalRef =ComIPduSignalRefs_Can_Message_3,
          .ComIPduDataPtr=ComIPduBuffer_3,
          .ComTxIPdu =
          {
               .ComTxModeFalse =
               {
                    .ComTxMode=
                    {
                      .ComTxModeMode = MIXED,
                      .ComTxModeNumberOfRepetitions = 2,
                      .ComTxModeTimePeriod = 100,
                      .ComTxModeRepetitionPeriod = 1000
                    }
               },

               .ComMinimumDelayTime = 0,
               .ComTxIPduUnusedAreasDefault = 0,

          }
      },
      { // CanDB_Message_3
            .ComIPduDirection = SEND ,
			.ComIPduSize=8,
            .ComIPduHandleId = 3 ,
            .ComIPduSignalRef =ComIPduSignalRefs_Can_Message_3,
            .ComIPduDataPtr=ComIPduBuffer_3,
            .ComTxIPdu =
            {
                 .ComTxModeFalse =
                 {
                      .ComTxMode=
                      {
                        .ComTxModeMode = NONE,
                        .ComTxModeNumberOfRepetitions = 2,
                        .ComTxModeTimePeriod = 10,
                        .ComTxModeRepetitionPeriod = 100
                      }
                 },

                 .ComMinimumDelayTime = 0,
                 .ComTxIPduUnusedAreasDefault = 0,

            }
        }
};


/* Com Config Container */
const ComConfig_type ComConfiguration =
{
    .ComTimeBase =
    {
         .ComRxTimeBase = 2,
         .ComTxTimeBase = 100
    },
    .ComIPdu = ComIPdu,
    .ComSignal = ComSignal,
    .ComSignalGroup=ComSignalGroup


};
