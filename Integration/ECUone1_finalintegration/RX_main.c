///*
// * RX_main.c
// *
// *  Created on: Jul 4, 2019
// *      Author: moustafa
// */
//
//
//
//
///*
// * main.c
// */
//#pragma diag_push
//#pragma CHECK_MISRA("none")
//
//#include <stdbool.h>
//#include <stdint.h>
//#include "driverlib/interrupt.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/gpio.h"
//#include "driverlib/pin_map.h"
//#include "inc/hw_memmap.h"
//#include "driverlib/uart.h"
//#include "OS/include/task.h"
//#include "utils/uartstdio.h"
//#include "OS/include/InitConsole.h"
//#include <PORTF.h>
//#include "include/Com.h"
//#include "include/CanTp_Cfg.h"
//#include "include/CanTp.h"
//#include "include/CanIf.h"
//#include "include/Can.h"
//#include "Dio.h"
//#include "OS/include/event.h"
//
//extern const Can_ConfigType CanContainer;
//extern const CanTp_ConfigType CanTp_Config ;
//extern const ComConfig_type ComConfiguration ;
//extern  CanIf_ConfigType CanIf_configTypeInstance;
//
//DeclareTask(T1);
//
//DeclareEvent(RTE_Event_HeatRegulatorEvent);
//DeclareEvent(RTE_Event_HeatingControllerEvent);
//DeclareEvent(BSW_Event_Com_MainFunctionRx);
//DeclareEvent(BSW_Event_Com_MainFunctionTx);
//DeclareEvent(BSW_Event_CanTp_MainFunction);
//
////
////DeclareTask(T1);
////DeclareTask(T2);
////
////DeclareEvent(ayEv);
////DeclareEvent(ayEv1);
////DeclareEvent(ayEv2);
//
////DeclareAlarm(alar1);
//
////#pragma RESET_MISRA("all")
//
//
//int flag = 0;
//
//int main(void){
//
//    PORTF_Init();
//    InitGPIO();
//    Can_Init(&CanContainer);
//    Can_SetControllerMode(CanContainer.CanConfigSet.CanController[0].CanControllerId,CAN_T_START);
//    CanTp_Init(&CanTp_Config);
//    Com_Init(&ComConfiguration);
//    CanIf_Init(&CanIf_configTypeInstance);
//    CanIf_SetControllerMode(CanContainer.CanConfigSet.CanController[0].CanControllerId,CAN_CS_STARTED);
//    StartOS(OSDEFAULTAPPMODE);
//    return 0;
//}
//
//
//
//TASK(T1)
//{
//    EventMaskType NewEvent;
//    while(true)
//    {
//        WaitEvent(RTE_Event_HeatRegulatorEvent | RTE_Event_HeatingControllerEvent | BSW_Event_Com_MainFunctionRx | BSW_Event_Com_MainFunctionTx | BSW_Event_CanTp_MainFunction);
//        GetEvent(T1, &NewEvent);
//        ClearEvent(NewEvent);
//        if(NewEvent & RTE_Event_HeatRegulatorEvent)
//        {
//            HeatRegulatorRunnable();
//        }
//        if(NewEvent & RTE_Event_HeatingControllerEvent)
//        {
//            HeatingControllerRunnable();
//        }
//        if(NewEvent & BSW_Event_Com_MainFunctionRx)
//        {
//            Com_MainFunctionRx();
//        }
//        if(NewEvent & BSW_Event_Com_MainFunctionTx)
//        {
//            Com_MainFunctionTx();
//        }
//        if(NewEvent & BSW_Event_CanTp_MainFunction)
//        {
//            CanTp_MainFunction();
//        }
//        TerminateTask();
//    }
//}
//
//
//
//
////TASK(T1)
////{
//////    uint16 signal1 = 195;
//////    boolean signal2 = TRUE;
//////    uint32 signal3 = 12256;
//////
//////    static uint8 count = 0;
//////    // main();
////////    int n=200000; //2000000 = 2 sec
////////    while(n--)
////////    {
////////         GPIO_PORTF_DATA_R = 0x04;
////////
////////    }
////////    GPIO_PORTF_DATA_R = 0;
//////    if(count == 0)
//////    {
//////        Com_SendSignal(0, &signal1);
//////        Com_SendSignal(1, &signal2);
//////        Com_SendSignal(2, &signal3);
//////    }
////    CanTp_MainFunction();
//////    count++;
////
////    TerminateTask();
////}
////
////TASK(T2)
////{
////    // Transmit();
//////    int n=200000; //2000000 = 2 sec
//////    while(n--)
//////    {
//////         GPIO_PORTF_DATA_R = 0x02;
//////    }
//////    GPIO_PORTF_DATA_R = 0;
////    uint16 signal4 ;
////    boolean signal5 ;
////    uint32 signal6 ;
//////  Com_MainFunctionTx();
////    Com_MainFunctionRx();
////    Com_ReceiveSignal(4, &signal5);
////    Com_ReceiveSignal(3, &signal4);
////    Com_ReceiveSignal(5, &signal6);
////
////    TerminateTask();
////}
//
