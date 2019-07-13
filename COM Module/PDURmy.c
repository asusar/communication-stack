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
///*
// * PDUR.c
// *
// *  Created on: ١١‏/٠٤‏/٢٠١٩
// *      Author: Omar
// */
//
//#include "include\ComStack_Types.h"
////#include "tm4c123gh6pm.h"
//#include "include/Com.h"
////#include <stdio.h>
////#include "UART.h"
//
//extern const ComConfig_type * ComConfig ;
//
//Std_ReturnType PduR_ComTransmit( PduIdType TxPduId, const PduInfoType* PduInfoPtr )
//{
//
//        uint64 signalID;
//    uint64* dataPtr=(uint64*) PduInfoPtr->SduDataPtr;
//    uint64 data=*dataPtr;
//    ComSignal_type * singal;
//    char * str;
//    ComIPdu_type *IPdu = GET_IPdu(TxPduId);
////    printString("\n\r IPDU ID : ");
////    UART_OutUDec(TxPduId);
////    printString(" Signals : ");
//
////    for (signalID = 0; (IPdu->ComIPduSignalRef != NULL) && (IPdu->ComIPduSignalRef[signalID] != NULL); signalID++)
////    {
////        singal = GET_Signal(signalID);
////
////        Com_ReceiveSignal(signalID, (void *) dataPtr );
////
////        if(singal->ComSignalType == UINT16)
////        {
////            printString("Id : ");
////            UART_OutUDec(signalID);
////            printString("Data : ");
//////            UART_OutUDec(*(uint16 *)dataPtr);
////            printString("   ");
////        }
////        else if(singal->ComSignalType == BOOLEAN)
////        {
////            printString("Id : ");
////            UART_OutUDec(signalID);
////            printString("Data : ");
//////            UART_OutUDec(*(boolean *)dataPtr);
////            printString("   ");
////        }
////        else if(singal->ComSignalType == UINT32)
////        {
////            printString("Id : ");
////            UART_OutUDec(signalID);
////            printString("Data : ");
//////            UART_OutUDec(*(uint32 *)dataPtr);
////            printString("   ");
////        }
////        else if(singal->ComSignalType == UINT64)
////        {
////            printString("Id : ");
////            UART_OutUDec(signalID);
////            printString("Data : ");
////            UART_OutUDec(*(uint64 *)dataPtr);
////            printString("   ");
////        }
////    }
////    printString("\n\r");
////
////    if(data== 195){
////            GPIO_PORTF_DATA_R |=(1<<1); //red
////
////
////    }
////    else if(data==0)
////    {
////        GPIO_PORTF_DATA_R |=(1<<2);   //blue
////    }
////    else
////    {
////        GPIO_PORTF_DATA_R |=(1<<3);
////    }
//	return 0;
//}
