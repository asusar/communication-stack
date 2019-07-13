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
 *  the file includes the initialization
 *  of PORTB.
 *  and configure the following:
 *
 *  PB4 - CAN0RX
 *  PB5 - CAN0TX
 *
 *
 *
 */

#pragma diag_push
#pragma CHECK_MISRA("none")

#include "Dio.h"

#pragma RESET_MISRA("all")

/* PA0, PA1 are used for serial communication and for CAN1 this #define cancels the initialization of GPIO for CAN1 */
#define USE_TERMINAL
/*
 * I/P : void
 * O/P : void
 * Usage : configure GPIO pins that working as a CAN
 */
void InitGPIO(void){

    /*CAN0 CONTROLLER */

    /* Enable clk on PORT B */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    /* Set PB4 as CAN0RX */
    GPIOPinConfigure(GPIO_PB4_CAN0RX);
    /* Set PB5 as CAN0TX */
    GPIOPinConfigure(GPIO_PB5_CAN0TX);
    /* Configures pin(s) for use as a CAN device */
    GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    /*CAN1 CONTROLLER */
#ifndef USE_TERMINAL
    /* Enable clk on PORT A */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    /* Set PA0 as CAN1RX */
    GPIOPinConfigure(GPIO_PA0_CAN1RX);
    /* Set PA1 as CAN1TX */
    GPIOPinConfigure(GPIO_PA1_CAN1TX);
    /* Configures pin(s) for use as a CAN device */
    GPIOPinTypeCAN(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
#endif

    }

