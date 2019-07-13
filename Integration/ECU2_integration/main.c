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
/*
 * main.c
 */
#pragma diag_push
#pragma CHECK_MISRA("none")

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/uart.h"
#include "OS/include/task.h"
#include "OS/include/event.h"
#include "utils/uartstdio.h"
#include "OS/include/InitConsole.h"
#include <PORTF.h>
#include "include/Com.h"
#include "include/CanTp_Cfg.h"
#include "include/CanTp.h"
#include "include/CanIf.h"
#include "include/Can.h"
#include "Rte/Rte.h"
#include "Dio.h"
#include "KeyPad.h"

extern const Can_ConfigType CanContainer;
extern const CanTp_ConfigType CanTp_Config ;
extern const ComConfig_type ComConfiguration ;
extern const CanIf_ConfigType CanIf_configTypeInstance;

DeclareTask(T1);

DeclareEvent(RTE_Event_HeatRegulatorEvent);
DeclareEvent(RTE_Event_HeatingControllerEvent);
DeclareEvent(BSW_Event_Com_MainFunctionRx);
DeclareEvent(BSW_Event_Com_MainFunctionTx);
DeclareEvent(BSW_Event_CanTp_MainFunction);

//DeclareAlarm(alar1);

//#pragma RESET_MISRA("all")


int flag = 0;

int main(void){

    PORTF_Init();
    InitGPIO();
    keypad_init();
    Can_Init(&CanContainer);
    Can_SetControllerMode(CanContainer.CanConfigSet.CanController[0].CanControllerId,CAN_T_START);
    CanTp_Init(&CanTp_Config);
    Com_Init(&ComConfiguration);
    CanIf_Init(&CanIf_configTypeInstance);
    CanIf_SetControllerMode(CanContainer.CanConfigSet.CanController[0].CanControllerId,CAN_CS_STARTED);
    StartOS(OSDEFAULTAPPMODE);
	return 0;
}


//TASK(T1)
//{
//    EventMaskType NewEvent;
//    while(true)
//    {
//        WaitEvent(BSW_Event_Com_MainFunctionTx );
//        GetEvent(T1, &NewEvent);
//        ClearEvent(NewEvent);
//        if(NewEvent & BSW_Event_Com_MainFunctionTx)
//        {
//            HeatRegulatorRunnable();
//            HeatingControllerRunnable();
//            Com_MainFunctionRx();
//            Com_MainFunctionTx();
//        }
//
//        TerminateTask();
//    }
//}

TASK(T1)
{
    EventMaskType NewEvent;
    while(true)
    {
        WaitEvent(RTE_Event_HeatRegulatorEvent | RTE_Event_HeatingControllerEvent | BSW_Event_Com_MainFunctionRx | BSW_Event_Com_MainFunctionTx);
        GetEvent(T1, &NewEvent);
        ClearEvent(NewEvent);
        if(NewEvent & RTE_Event_HeatRegulatorEvent)
        {
            HeatRegulatorRunnable();
        }
        if(NewEvent & RTE_Event_HeatingControllerEvent)
        {
            HeatingControllerRunnable();
        }
        if(NewEvent & BSW_Event_Com_MainFunctionRx)
        {
            Com_MainFunctionRx();
        }
        if(NewEvent & BSW_Event_Com_MainFunctionTx)
        {
            Com_MainFunctionTx();
        }
//        if(NewEvent & BSW_Event_CanTp_MainFunction)
//        {
//            CanTp_MainFunction();
//        }
    }
    TerminateTask();
}

