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
  main.c
 */
#include <stdbool.h>
#include <stdint.h>
#include"includes/Dio.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "includes/Can.h"
#include "includes/Os.h"
#include "includes/PortingHW.h"
#include "tm4c123gh6pm.h"

extern Can_ConfigType CanContainer;  // extern from Can.c , where its definedin  Static_Can_Cfg.h
extern tCANMsgObject received_CANMessage;



void
InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}
void
SimpleDelay(void)
{
    //
    // Delay cycles for 1 second
    //
    SysCtlDelay(16000000 / 3);
}
void portf_init()
       {
           SYSCTL_RCGCGPIO_R |= 0x20;  // activate port F
                     // initialize SysTick timer
         GPIO_PORTF_DIR_R |= 0x0E;   // make PF1, 2 and 3 out
         GPIO_PORTF_AFSEL_R &= ~0x0E;// disable alt funct on PF1, 2 and 3
         GPIO_PORTF_DEN_R |= 0x0E;   // enable digital I/O on PF1,2 and 3
                                     // configure PF1,2 and 3 as GPIO
         GPIO_PORTF_AMSEL_R = 0;     // disable analog functionality on PF
       }
int main(void)
{

   InitGPIO();
   SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                     SYSCTL_XTAL_16MHZ);
   /* initialise the gpio_s to function as can  PORTB PIN_4 | PIN_5*/
    Can_Init(&CanContainer);

//    CANEnable(CAN0_BASE);
    Can_SetControllerMode(CanContainer.CanConfigSet.CanController[0].CanControllerId,CAN_T_START);






//    Can_EnableControllerInterrupts(CanContainer.CanConfigSet.CanController[0].CanControllerId);
    Can_PduType CanMsg[3];
    uint8_t data1[8]={1,2,3,4,5,6,7,8};
    uint8_t data2=2;
    uint8_t data3=3;
    CanMsg[0].id=0;
    CanMsg[0].length=8;
    CanMsg[0].sdu=data1;
    CanMsg[0].swPduHandle=0;

    CanMsg[1].id=2;
    CanMsg[1].length=1;
    CanMsg[1].sdu=&data2;
    CanMsg[1].swPduHandle=0;

    CanMsg[2].id=3;
    CanMsg[2].length=1;
    CanMsg[2].sdu=&data3;
    CanMsg[2].swPduHandle=0;

    uint8_t HTH=0;
    uint8_t i=0;
    portf_init();
    InitConsole();
    Can_ErrorStateType x;
   Std_ReturnType y;



                             /* One-time writable registers that require
                             initialisation directly after reset shall be initialized by the startup code.*/


    while(1){
                /*don't forget to clear testing declarations in can.c*/
               Can_Write(HTH, &CanMsg[i]);
//               Can_GetControllerErrorState( uint8_t ControllerId, Can_ErrorStateType* ErrorStatePtr );


//               CAN0_IF1MCTL_R&=~(0x100);
//               CAN0_IF1CMSK_R&=~(0x80);
//               CAN0_IF1CRQ_R=4;
//               CAN0_IF1CMSK_R|=0x80;
//               CAN0_IF1CRQ_R=4;
//               POLLING_REGISTER=CAN0_IF1MCTL_R;
//               POLLING_REGISTER|=0xFEFF;
             /*Can_EnableControllerInterrupts(CanContainer.CanConfigSet.CanController[0].CanControllerId); testing priority inversion*/

//                  HTH ++;
//                if(HTH>=2){HTH=0;}
//                i++;
//                if(i>2)
//                {
//                    i=0;
//                }

//              Can_Main_Function_Write();

                SimpleDelay();
            }
  /*  StartOS(OSDEFAULTAPPMODE);*/


}






















//int main(void){
//
//    PORTF_Init();
//
//    StartOS(OSDEFAULTAPPMODE);
//
//  return 0;
//}
//
//
//
///*TASK(Task_white)
//{
//    GPIO_PORTF_DATA_R = 0;
//    while(1)
//    {
//        GPIO_PORTF_DATA_R = 0x0E;
//        if(!(GPIO_PORTF_DATA_R & 0x01))
//            ActivateTask(Task_red);
//    }
//    TerminateTask();
//}*/


//USER_RxCfgMessage1.mailboxID = 2U     ;                               //  you pass the real no not index the frist hardware object , which has mask equals 0
//USER_RxCfgMessage1.canid     = 0x7A1U ;                             // id 11 bit , but it will not affect
//USER_RxCfgMessage1.canlength = 8U     ;                               // size
//Cfg_RxMsgObject(& USER_RxCfgMessage1);
//
//
//USER_RxCfgMessage7.mailboxID = 5U     ;                               //  you pass the real no not index the frist hardware object , which has mask equals 0
//USER_RxCfgMessage7.canid     = 0x7A4U ;                             // id 11 bit , but it will not affect
//USER_RxCfgMessage7.canlength = 8U     ;                               // size
//Cfg_RxMsgObject(& USER_RxCfgMessage7);
//
//uint8_t S1[8]  = {'C','G',0,'h'};
//uint8_t S2 [8]  = {0,'r','t'};
//uint8_t S3 [8]  = {'x','e','k'};








































































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//       Can_PduType_t CanWriteCANMessage;
//       /*
//        * Set user value for testing
//        */
//       uint8_t g_pui8Msg[8] = { 'm','o','u','s','t','a','f','a' };                                 //data you want to send
//       CanWriteCANMessage.id = 0x7A2;                                                             // the id 11 bit
//       CanWriteCANMessage.length = 8U;                                                             // 5 byte
//       CanWriteCANMessage.sdu = g_pui8Msg;                                                         // your data
//       CanWriteCANMessage.swPduHandle = 0U;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//         PduInfoType_t CanIFLayerCANMessage;
//        /*
//        * Set user value for testing
//        * Calling autosar function " CanIf_Transmit " to send target Message
//        * @param1 : CanTxPduId value will send from PDUR layer
//        * @param2 : pointer to structure message
//        */
//        uint8_t g_pui8Msg[5] = {'C','A','N','I','F'};
//        CanIFLayerCANMessage.SduLength = 5U;
//        CanIFLayerCANMessage.SduDataptr = g_pui8Msg;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//           PduInfoType_t PduRCANMessage;
//           /*
//           * Set user value for testing
//           * Calling autosar function " Can_Write " to send target Message
//           * @param1 : hth value will send from CANIF layer
//           * @param2 : pointer to structure message
//           */
//           uint8_t g_pui8Msg[8] = { 'm','o','u','s','t','a','f','a' };
//           PduRCANMessage.SduLength = 8U;
//           PduRCANMessage.SduDataptr = g_pui8Msg;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//           uint8_t update_data1[4] ={'A','U','T'};
//           uint8_t update_data2[4] ={'O','S','A','R'};
//           uint8_t update_data3[4] ={'M','O','S','U'};
//           uint8_t update_data4[4] ={'T','A','F','A'};
//           uint8_t update_data5[4] ={'s','t','N'};
//           uint8_t update_data6[4] ={'s','t','N'};
           //Timer0A_Init();
//Output_Init();
//#include <stdio.h>
//#include <stdint.h>    // C99 variable types
////void Output_Init(void);
//#include <Timer0A.h>
//uint8_t A[3] = {12,4,2};
//uint16_t i;
//
//int main(void)
//{
//    Output_Init();
//    A[4] = 42;
//    while(1)
//    { printf("Hello\n");}
//extern Pdu_t PDU;
//extern signal_t RTE_SeatHeater_Levels_RightHeatLevel;
//extern signal_t RTE_SeatHeater_Levels_LeftHeatLevel;
//extern signal_t SeatHeatingController_PassengerOnLeftSeat;
//extern signal_t SeatHeatingController_PassengerOnRighttSeat;
//extern signal_t  RTE_HeatRegulator_RegulatorPosition_Position;
//Can_Write(1u,&CanWriteCANMessage);
 //CanIf_Transmit(3U,&CanIFLayerCANMessage);
 // PduR_ComTransmit(5U,&PduRCANMessage); // CHOOSE THE PDU YOU WANT TO SENT ON
//           COM_SendSignal(&RTE_SeatHeater_Levels_RightHeatLevel ,    & update_data1);
//           COM_SendSignal(&RTE_SeatHeater_Levels_LeftHeatLevel  , & update_data2);
//           COM_SendSignal(&SeatHeatingController_PassengerOnLeftSeat ,  &update_data3);
//           COM_SendSignal(&SeatHeatingController_PassengerOnRighttSeat , &update_data4); // UPDATED BUT NOT SENT
//           COM_SendSignal(&RTE_HeatRegulator_RegulatorPosition_Position , &update_data5);

