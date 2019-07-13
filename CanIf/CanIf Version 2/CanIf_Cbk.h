/*
 * CanIf_Cbk.h
 *
 *  Created on: Jun 23, 2019
 *      Author: leenovoz510
 */

#ifndef CANIF_CBK_H_
#define CANIF_CBK_H_

#include "CanIf.h"
#include "CanIf_Types.h"
#include "CanIf_Cfg.h"
#include "ComStack_types.h"
#include "Std_Types.h"
#include "Can_GeneralTypes.h"
#include "PduR.h"
void CanIf_TxConfirmation(PduIdType CanTxPduId);
extern void CanIf_RxIndication(const Can_HwType* Mailbox,const PduInfoType* PduInfoPtr);
//void PduR_CanIfRxIndication(uint16 ,const PduInfoType*);
//void CanTp_CanIfRxIndication(uint16 ,const PduInfoType*);

#endif /* CANIF_CBK_H_ */
