/*
 * CanIf.h
 *
 *  Created on: May 4, 2018
 *      Author: Ahmed Usama Khalifa
 */

#ifndef INCLUDES_CANIF_H_
#define INCLUDES_CANIF_H_

#include "includes/CanIf_Types.h"
#include "includes/CanIf_Cfg.h"

Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId,
                              const PduInfoType* PduInfoPtr);


#endif /* INCLUDES_CANIF_H_ */
