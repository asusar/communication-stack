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
#include <includes/Can_Cfg.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "includes/Can.h"

//
//void DisableInterrupts(void); // Disable interrupts
//void EnableInterrupts(void);  // Enable interrupts
//long StartCritical (void);    // previous I bit, disable interrupts
//void EndCritical(long sr);    // restore I bit to previous value
//void WaitForInterrupt(void);  // low power mode
//void (*PeriodicTask)(void);   // user function


// ***************** Timer0A_Init ****************
// Activate TIMER0 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq), 32 bits
// Outputs: none

//Can_ConfigType can=general;



void Timer0A_Init(void)
   {

  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0

  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000001;   // 3) configure for periodic mode, default down-count settings
  TIMER0_TAILR_R =16000000*CanTimeoutDuration;    // 4) reload value
  TIMER0_TAPR_R = 0;            // 5) bus clock resolution
  TIMER0_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
  TIMER0_IMR_R = 0x00000001;    // 7) arm timeout interrupt
 /* NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x80000000; */// 8) priority 4
 // interrupts enabled in the main program after all devices initialized
 // vector number 35, interrupt number 19
 /*NVIC_EN0_R = 1<<19; */          // 9) enable IRQ 19 in NVIC
 TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A

}

void Timer0A_Handler(void){
      // execute user task
}
