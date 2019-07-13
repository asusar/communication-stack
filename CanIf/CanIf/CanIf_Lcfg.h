/*
 * CanIf_Lcfg.h
 *
 *  Created on: Nov 15, 2017
 *      Author: Ahmed.Abdelmoniem
 */

#ifndef CANIF_LCFG_H_
#define CANIF_LCFG_H_

#include "CanIf.h"
#if defined(USE_CANTP)
#include "CanTp.h"
#include "CanTp_Cbk.h"
#endif
#if defined(USE_J1939TP)
#include "J1939Tp.h"
#include "J1939Tp_Cbk.h"
#endif
/* #if defined(USE_PDUR) */
#include "PduR.h"
#include "PduR_CanIf.h"
#include "PduR_PbCfg.h"
/*#endif */
#if defined(USE_CANNM)
#include "CanNm_Cbk.h"
#endif
#include <stdlib.h>
#include "Can_Driver/Can_Cfg.h"
#include "AVECORE_CANIF.h" // upper layer function place

//extern const CanIf_DispatchConfigType CanIf_DispatchConfigInstance;
extern CanIf_TxBuffPduInfo_t buffer_a[BUFFER_MAX];
extern const CanIf_HthConfigType CanIf_hthConfigTypeInstance[];
extern const CanIf_HrhConfigType CanIf_hrhConfigTypeInstance[];

#endif /* CANIF_LCFG_H_ */
