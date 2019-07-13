/*
 * PduR_helper.h
 *
 *  Created on: Apr 28, 2019
 *      Author: lenovo
 */

#include "stdint.h"
#include "PduR.h"

#ifndef PDUR_HELPER_H_
#define PDUR_HELPER_H_

uint8_t get_ID(uint32_t source_id , type_t source );
type_t  get_type(uint32_t source_id, type_t source);



#endif /* PDUR_HELPER_H_ */
