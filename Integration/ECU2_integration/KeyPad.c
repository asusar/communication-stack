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
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "KeyPad.h"

/*
 *  Here is the keyPad map 4x4
 *
 */

const uint8_t keymap[4][4] = {
        { '1', '2', '3', '3'},
        { '4', '5', '6', '6'},
        { '7', '8', '9', '9'},
        { '*', '0', '#', 'D'},
    };


/********************************************************************************/
/* this function initializes
 * the ports connected to the keypad
 *
 */
void keypad_init(void)
{
    uint32_t dummy ;
    SYSCTL_RCGCGPIO_R |= 0x04;   /* enable clock to GPIOC */
    SYSCTL_RCGCGPIO_R |= 16;   /* enable clock to GPIOE */

    dummy = SYSCTL_RCGCGPIO_R ;  /* dummy wait for stable clock */

    GPIO_PORTE_DIR_R |= 0x0F;     /* set row pins 3-0 as output */
    GPIO_PORTE_DEN_R |= 0x0F;     /* set row pins 3-0 as digital pins */
    GPIO_PORTE_ODR_R |= 0x0F;

    GPIO_PORTC_DIR_R &= ~0xF0;    /* set column pin 7-4 as input */
    GPIO_PORTC_DEN_R |= 0xF0;     /* set column pin 7-4 as digital pins */
    GPIO_PORTC_PUR_R |= 0xF0;     /* enable pull-ups for pin 7-4*/

}

uint8_t GetKey(void){
    uint8_t key ;
    uint32_t col ;
    uint32_t row ;
    GPIO_PORTE_DATA_R &=0X0F;
    GPIO_PORTC_DATA_R &=0xF0;
    if(GPIO_PORTC_DATA_R ==0xF0 ) return 0;          /* if no key is pressed return 0 */


    /* if it gets here. A key is pressed */
    while (1){

        /* row 0 checking */
        row = 0  ;
        GPIO_PORTE_DATA_R   = 0x0E ;
        Delay_Us(2);                        /* all ones except first*/
        col = GPIO_PORTC_DATA_R & 0xF0 ;
        if (col != 0xF0) break ;    /* first row detected */


        /* row 1 checking */
        row = 1  ;
        GPIO_PORTE_DATA_R = 0x0D ;
        Delay_Us(2);                                /* all ones except 2nd*/
        col =GPIO_PORTC_DATA_R  & 0xF0 ;
        if (col != 0xF0) break ;    /* 2nd row detected */


        /* row 2 checking */
        row = 2  ;
        GPIO_PORTE_DATA_R  = 0x0B;         /* all ones except 3ed*/
        Delay_Us(2);
        col = GPIO_PORTC_DATA_R & 0xF0 ;
        if (col != 0xF0) break ;    /* 3ed row detected */


        /* row 3 checking */
        row = 3  ;
        GPIO_PORTE_DATA_R  = 0x07 ;         /* all ones except 4th*/
        Delay_Us(2);
        col = GPIO_PORTC_DATA_R & 0xF0 ;
        if (col != 0xF0) break ;    /* 4th row detected */

        return 0 ;
    }

    if (col == 0x70) return keymap[row][0]; /* key in column 0 */
    if (col == 0xB0) return keymap[row][1]; /* key in column 1 */
    if (col == 0xD0) return keymap[row][2]; /* key in column 2 */
    if (col == 0xE0) return keymap[row][3]; /* key in column 3 */

    /* this should be never execute */
    return 0;
}
/********************************************************************************/




/********************************************************************************/
/*
 * testing kepad init and GetKey function
 * this test use the terminal and send the character
 * pressed on the keyPad
 * input: void
 * return: void
 *
 */
/*void test2(void){
    keypad_init() ;

    uint32_t test2 = 0 ;
    UARTprintf("test 2 start \n\n");
    while(1){
    test2 = GetKey() ;
    switch (test2){
    case('0'):
        UARTprintf("0\n"); break;
    case('1'):
        UARTprintf("1\n"); break;
    case('2'):
        UARTprintf("2\n"); break;
    case('3'):
        UARTprintf("3\n"); break;
    case('4'):
        UARTprintf("4\n"); break;
    case('5'):
        UARTprintf("5\n"); break;
    case('6'):
        UARTprintf("6\n"); break;
    case('7'):
        UARTprintf("7\n"); break;
    case('8'):
        UARTprintf("8\n"); break;
    case('9'):
        UARTprintf("9\n"); break;
    case('*'):
        UARTprintf("*\n"); break;
    case('#'):
        UARTprintf("#\n"); break;
    case('A'):
        UARTprintf("A\n"); break;
    case('B'):
        UARTprintf("B\n"); break;
    case('C'):
        UARTprintf("C\n"); break;
    case('D'):
        UARTprintf("D\n"); break;


    }
    }

}*/
/********************************************************************************/
