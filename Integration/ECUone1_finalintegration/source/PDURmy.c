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
