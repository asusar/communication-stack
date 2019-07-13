/*
 * Dio.h
 *
 *  Created on: May 3, 2018
 *      Author: Ahmed Usama Khalifa
 */

#ifndef INCLUDES_DIO_H_
#define INCLUDES_DIO_H_

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"

/*
 * I/P : void
 * O/P : void
 * Usage : configure GPIO pins that working as a CAN
 */
void InitGPIO(void);



#endif /* INCLUDES_DIO_H_ */
