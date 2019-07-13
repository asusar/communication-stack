/*
 * ComStack_Types.h
 *
 *  Created on: May 3, 2018
 *      Author: Ahmed Usama Khalifa
 */

#ifndef INCLUDES_COMSTACK_TYPES_H_
#define INCLUDES_COMSTACK_TYPES_H_

#include "includes/Std_Types.h"
#include "includes/ComStack_Cfg.h"

    /* Type of PDU Length,
      Allowed ranges: uint8 .. uint32
     */

/*
  Variables of this type shall be used to store the basic information about a PDU of any type,
  namely a pointer variable pointing to its SDU (payload),
  a pointer to Meta Data of the PDU,
  and the corresponding length of the SDU in bytes.
 */
typedef struct PduInfoType
{
         uint8_t*           SduDataptr;
         uint8_t*           MetaDataptr;
         PduLengthType_t  SduLength;
} PduInfoType;

typedef struct {


} RetryInfoType_t;

#endif /* INCLUDES_COMSTACK_TYPES_H_ */
