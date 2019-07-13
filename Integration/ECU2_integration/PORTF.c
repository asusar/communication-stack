/*
 * PORTF.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Sarea
 */
#include <PORTF.h>

/* this function doesn't enable the interrupt on the port f */
void PORTF_Init(void){
        int dummy ;
        SYSCTL_RCGCGPIO_R |= 0x020 ;
        dummy = SYSCTL_RCGC2_R ;
        GPIO_PORTF_LOCK_R = 0x4c4f434b ;
        GPIO_PORTF_CR_R = 0x01f ;
        GPIO_PORTF_DIR_R = 0xe  ;
        GPIO_PORTF_DIR_R &= ~0x11 ;
        GPIO_PORTF_PUR_R |= 0x11 ;
        GPIO_PORTF_DEN_R |= 0x1f ;
}

uint8_t PORTF_SSR(void){
    uint8_t data = !(GPIO_PORTF_DATA_R & 0x01) ;
    return data ;
}
uint8_t PORTF_SSL(void){
    uint8_t data = !(GPIO_PORTF_DATA_R & 0x10) ;
    return data ;
}
