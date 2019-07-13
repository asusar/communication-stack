/*
 * PORTF_Init.h
 *
 *  Created on: 3 dec 2017
 *  Sarea Al Hariri
 */
#include <stdint.h>
#include <tm4c123gh6pm.h>

#ifndef PORTF_INIT_H_
#define PORTF_INIT_H_

// this function doesn't enable the interrupt on the port f
void PORTF_Init(void);
uint8_t PORTF_SSR(void);
uint8_t PORTF_SSL(void);

#endif /* PORTF_INIT_H_ */
