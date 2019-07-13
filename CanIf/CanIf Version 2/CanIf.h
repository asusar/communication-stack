/*
 * CanIf.h
 *
 *  Created on: Jun 23, 2019
 *      Author: leenovoz510
 */

#ifndef CANIF_H_
#define CANIF_H_

#include "CanIf_Types.h"
#include "CanIf_Cfg.h"
#include "ComStack_types.h"
#include "Std_Types.h"
#include "Can_GeneralTypes.h"

#if defined(USE_PDUR)
#include "PduR.h"
#endif

#if defined(USE_COM)
#include "Com.h"
#endif


void CanIf_Init(const CanIf_ConfigType* ConfigPtr);

#if (CANIF_UNIT_TESTING==STD_ON)
void CanIf_DeInit(void);
#endif

Std_ReturnType CanIf_SetPduMode(uint8 ControllerId, CanIf_PduModeType PduModeRequest);
Std_ReturnType CanIf_GetPduMode(uint8 ControllerId, CanIf_PduModeType* PduModePtr);
Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, Can_ControllerStateType ControllerMode);
Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, Can_ControllerStateType* ControllerModePtr);
Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);
void Get_User_RxIndication(CanIfRxPduUserRxConfirmationUL user,uint16 i);
void CanIf_TxConfirmation(PduIdType CanTxPduId);

#endif /* CANIF_H_ */
