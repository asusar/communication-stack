
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

#ifndef COMSTACK_TYPES_H_
#define COMSTACK_TYPES_H_


#include <stdint.h>
#include "Std_Types.h"
#include "Com_Types.h"

/*typedef uint8_t bool;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
*/
//typedef void * RetryInfoType ;
typedef uint32 TPParameterType ;
typedef uint32 PduIdType ;
typedef uint32 PduLengthType ;

typedef enum
{
    BUFREQ_OK   ,                         //: success
    BUFREQ_E_NOT_OK  ,                    //: development error detected
    BUFREQ_E_BUSY ,                       //: all buffers in use
    BUFREQ_E_OVFL                         // : requested buffer too large
}BufReq_ReturnType ;


typedef struct
{
         uint8 *           SduDataPtr;
         uint8 *           MetaDataPtr;
         PduLengthType   SduLength;
} PduInfoType;

typedef enum
{
	TP_DATACONF,
	TP_DATARETRY,
	TP_CONFPENDING,
	TP_NORETRY,
} TpDataStateType;

typedef struct
{
	TpDataStateType TpDataState;
	PduLengthType TxTpDataCnt;
} RetryInfoType;


#endif /* COMSTACK_TYPES_H_ */

