#ifndef CanTp_Cfg_H_
#define CanTp_Cfg_H_


#include "CanTp_Types.h"             // Farag's edition





#define CANTP_NSDU_CONFIG_LIST_SIZE_TX		2
#define CANTP_NSDU_CONFIG_LIST_SIZE_RX      2




#define CANTP_NSDU_RUNTIME_LIST_SIZE	(CANTP_NSDU_CONFIG_LIST_SIZE_TX + CANTP_NSDU_CONFIG_LIST_SIZE_RX)



extern const CanTp_TxNSduType CanTpTxNSdu[];
extern const CanTp_RxNSduType CanTpRxNSdu[];


//#define CANTP_CONVERT_MS_TO_MAIN_CYCLES(x) 	(x)/CanTp_Config.CanTpMainFunctionPeriod



#endif		/* CANTP_CFG_H_ */
