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

#ifndef COM_CBK_H_
#define COM_CBK_H_


void Com_RxIndication( PduIdType RxPduId, const PduInfoType* PduInfoPtr ) ;
void Com_TpRxIndication( PduIdType id, Std_ReturnType result );
void Com_TxConfirmation( PduIdType TxPduId, Std_ReturnType result );
void Com_TpTxConfirmation( PduIdType id, Std_ReturnType result );
BufReq_ReturnType Com_StartOfReception( PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr ) ;
BufReq_ReturnType Com_CopyRxData( PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr ) ;
BufReq_ReturnType Com_CopyTxData( PduIdType id,  PduInfoType* info, const RetryInfoType* retry, PduLengthType* availableDataPtr );


#endif /* COM_CBK_H_ */
