#include "include/CanIf.h"
#if defined(USE_CANTP)
#include "CanTp.h"
#include "CanTp_Cbk.h"
#endif
#if defined(USE_J1939TP)
#include "J1939Tp.h"
#include "J1939Tp_Cbk.h"
#endif
#if defined(USE_PDUR)
#include "PduR.h"
#include "PduR_CanIf.h"
#include "PduR_PbCfg.h"
#endif
#if defined(USE_CANNM)
#include "CanNm_Cbk.h"
#endif
#include <stdlib.h>
#include"stdint.h"

#include "include/Can_GeneralTypes.h"
#include "include/Can_Cfg.h"
#include "include/CanIf_Types.h"
#include "include/CanIf_Cfg.h"
#include "include/PduR_CanIf.h"
#include"include/Can.h"
#include "stdbool.h"

uint8_t try[7] = vcanf;
extern CanIfRxPduCanIdRange CanIf_hrhRangeConfigTypeInstance[] = {1,900};

//Can_ConfigType CanHohContiner = hohMap;

extern CanIfBufferCfg  CanIfBufferCfgInstance[3];
extern CanIfRxPduCfg   CanIf_rxPduConfigTypeInstance[5];
extern CanIfTxPduCfg   CanIf_txPduConfigTypeInstance[5];
// CanIfHrhCfg CanIfHrhCfgInstance[];
// CanIfHthCfg CanIfHthCfgInstance[];
extern CanIfInitHohCfg     CanIfInitHohCfgInstance[2];
extern CanIfInitCfg        CanIf_initConfigTypeInstance[1];
extern CanIf_ConfigType    CanIf_configTypeInstance[1];
extern CanIfCtrlCfg CanIfCtrlCfgInstance[3];



extern const CanIfPrivateCfg CanIfPrivateCfgInstance[2]=
{
 {
 .CanIfFixedBuffer = TRUE,
 .CanIfPrivateDataLengthCheck = TRUE,
 .CanIfPrivateSoftwareFilterType = MASK,
 .CanIfSupportTTCAN = FALSE
 },
 {
    .CanIfFixedBuffer = TRUE,
    .CanIfPrivateDataLengthCheck = TRUE,
    .CanIfPrivateSoftwareFilterType = MASK,
    .CanIfSupportTTCAN = FALSE

 }
};

CanIfHthCfg CanIfHthCfgInstance[2] = {
    {
      .CanIfHthCanCtrlIdRef = &(CanIfCtrlCfgInstance[0]) ,
      .CanIfHthIdSymRef = &(CanContainer.CanConfigSet.CanHardwareObject[0])
    },
    {
      .CanIfHthCanCtrlIdRef = &(CanIfCtrlCfgInstance[0]) ,
      .CanIfHthIdSymRef = &(CanContainer.CanConfigSet.CanHardwareObject[1])
    }
};
CanIfHrhCfg CanIfHrhCfgInstance[1] = {
     {
      .CanIfHrhIdSymRef = &(CanContainer.CanConfigSet.CanHardwareObject[2]),
      .CanIfHrhSoftwareFilter = TRUE ,
      .CanIfHrhCanCtrlIdRef = &(CanIfCtrlCfgInstance[0]) ,
      .CanIfHrhRangeConfig = &CanIf_hrhRangeConfigTypeInstance
     }
};

CanIfBufferCfg CanIfBufferCfgInstance[3] ={
       {
        .CanIfBufferHthRef = &CanIfHthCfgInstance[0],
        .CanIfBufferSize = 8
       },
       {
        .CanIfBufferHthRef = &CanIfHthCfgInstance[0],
        .CanIfBufferSize = 8
       },
       {
        .CanIfBufferHthRef = &CanIfHthCfgInstance[1],
        .CanIfBufferSize = 8
       }

};



CanIfRxPduCfg CanIf_rxPduConfigTypeInstance[5] = {
    //  {CanIfRxPduCanId,CanIfRxPduCanIdMask,CanIfRxPduDataLength,CanIfRxPduReadData,
    //   CanIfRxPduReadNotifyStatus,CanIfRxPduCanIdType,CanIfRxPduId,CanIfRxPduUserRxIndicationName,
    //   CanIfRxPduUserRxIndicationUL,CanIfRxPduHrhIdRef,CanIfRxPduRef,CanIfRxPduCanIdRangePtr}
        {
         .CanIfRxPduCanId = 1,
         .CanIfRxPduCanIdMask = 0xFFFF,
         .CanIfRxPduDataLength = 8,
         .CanIfRxPduReadData = FALSE,
         .CanIfRxPduReadNotifyStatus = FALSE,
         .CanIfRxPduCanIdType = STANDARD_CAN,
         .CanIfRxPduId = 10,
         .CanIfRxPduUserRxIndicationName = 1,
         .CanIfRxPduUserRxIndicationUL_i = PDUR,
         .CanIfRxPduHrhIdRef = &(CanIfHrhCfgInstance[0]),
         .CanIfRxPduRef = &try[0],
         .CanIfRxPduCanIdRangePtr = CanIf_hrhRangeConfigTypeInstance
        },
        {
         .CanIfRxPduCanId = 1,
         .CanIfRxPduCanIdMask = 0,
         .CanIfRxPduDataLength = 8,
         .CanIfRxPduReadData = FALSE,
         .CanIfRxPduReadNotifyStatus = FALSE,
         .CanIfRxPduCanIdType = STANDARD_CAN,
         .CanIfRxPduId = 11,
         .CanIfRxPduUserRxIndicationName = 2,
         .CanIfRxPduUserRxIndicationUL_i = PDUR,
         .CanIfRxPduHrhIdRef = &(CanIfHrhCfgInstance[1]),
         .CanIfRxPduRef = &try[1],
         .CanIfRxPduCanIdRangePtr = CanIf_hrhRangeConfigTypeInstance
        },
        {
         .CanIfRxPduCanId = 2,
         .CanIfRxPduCanIdMask = 0,
         .CanIfRxPduDataLength = 8,
         .CanIfRxPduReadData = FALSE,
         .CanIfRxPduReadNotifyStatus = FALSE,
         .CanIfRxPduCanIdType = STANDARD_CAN,
         .CanIfRxPduId = 12,
         .CanIfRxPduUserRxIndicationName = 3,
         .CanIfRxPduUserRxIndicationUL_i = PDUR,
         .CanIfRxPduHrhIdRef = &(CanIfHrhCfgInstance[2]),
         .CanIfRxPduRef = &try[2],
         .CanIfRxPduCanIdRangePtr = CanIf_hrhRangeConfigTypeInstance
        },
        {
         .CanIfRxPduCanId = 3,
         .CanIfRxPduCanIdMask = 0,
         .CanIfRxPduDataLength = 8,
         .CanIfRxPduReadData = FALSE,
         .CanIfRxPduReadNotifyStatus = FALSE,
         .CanIfRxPduCanIdType = STANDARD_CAN,
         .CanIfRxPduId = 13,
         .CanIfRxPduUserRxIndicationName = 4,
         .CanIfRxPduUserRxIndicationUL_i = PDUR,
         .CanIfRxPduHrhIdRef = &(CanIfHrhCfgInstance[3]),
         .CanIfRxPduRef = &try[3],
         .CanIfRxPduCanIdRangePtr = CanIf_hrhRangeConfigTypeInstance
        },
        {
         .CanIfRxPduCanId = 4,
         .CanIfRxPduCanIdMask = 0xFFFF,
         .CanIfRxPduDataLength = 8,
         .CanIfRxPduReadData = FALSE,
         .CanIfRxPduReadNotifyStatus = FALSE,
         .CanIfRxPduCanIdType = STANDARD_CAN,
         .CanIfRxPduId = 14,
         .CanIfRxPduUserRxIndicationName = 5,
         .CanIfRxPduUserRxIndicationUL_i = PDUR,
         .CanIfRxPduHrhIdRef = &(CanIfHrhCfgInstance[4]),
         .CanIfRxPduRef = &try[4],
         .CanIfRxPduCanIdRangePtr = CanIf_hrhRangeConfigTypeInstance
        }
};




CanIfTxPduCfg  CanIf_txPduConfigTypeInstance[5] =
{
     /*
    uint32 CanIfTxPduCanId, uint32 CanIfTxPduCanIdMask,
    CanIfTxPduCanIdType CanIfTxPduCanIdType_i, uint32 CanIfTxPduId,
    bool CanIfTxPduPnFilterPdu, bool CanIfTxPduReadNotifyStatus,
    bool CanIfTxPduTriggerTransmit, bool CanIfTxPduTruncation,
    CanIfTxPduType CanIfTxPduType_i,uint16 CanIfTxPduUserTriggerTransmitName,
    uint16 CanIfTxPduUserTxConfirmationName,CanIfBufferCfg* CanIfTxPduBufferRef,
    PduInfoType* CanIfTxPduRef */
   {
    .CanIfTxPduCanId = 0,
    .CanIfTxPduCanIdMask = 0xF4, //////////////////// IMP
    .CanIfTxPduCanIdType_i = STANDARD_CAN,
    .CanIfTxPduId = 0,
    .CanIfTxPduPnFilterPdu = FALSE,
    .CanIfTxPduReadNotifyStatus = FALSE,
    .CanIfTxPduTriggerTransmit = FALSE,
    .CanIfTxPduTruncation = FALSE,
    .CanIfTxPduType_i = STATIC,
    .CanIfTxPduUserTxConfirmationUL_i = PDUR  ,
    .CanIfTxPduBufferRef=
        {
          &CanIfBufferCfgInstance[0]
        },
        .CanIfTxPduRef = 0
       },
   {
    .CanIfTxPduCanId = 6,
    .CanIfTxPduCanIdMask = 0xF4,
    .CanIfTxPduCanIdType_i = STANDARD_CAN,
    .CanIfTxPduId = 1,
    .CanIfTxPduPnFilterPdu = FALSE,
    .CanIfTxPduReadNotifyStatus = FALSE,
    .CanIfTxPduTriggerTransmit = FALSE,
    .CanIfTxPduTruncation = FALSE,
    .CanIfTxPduType_i = STATIC,
    .CanIfTxPduUserTxConfirmationUL_i = CAN_TP,
    .CanIfTxPduBufferRef=
    {
      &CanIfBufferCfgInstance[0]
    },
    .CanIfTxPduRef = 0
   },
   {
    .CanIfTxPduCanId = 7,
    .CanIfTxPduCanIdMask = 0xF4,
    .CanIfTxPduCanIdType_i = STANDARD_CAN,
    .CanIfTxPduId = 2,
    .CanIfTxPduPnFilterPdu = FALSE,
    .CanIfTxPduReadNotifyStatus = FALSE,
    .CanIfTxPduTriggerTransmit = FALSE,
    .CanIfTxPduTruncation = FALSE,
    .CanIfTxPduType_i = STATIC,
    .CanIfTxPduUserTxConfirmationUL_i = CAN_TP,
    .CanIfTxPduBufferRef=
    {
      &CanIfBufferCfgInstance[1]
    },
    .CanIfTxPduRef = 0
   },
   {
    .CanIfTxPduCanId = 8,
    .CanIfTxPduCanIdMask = 0xF4,
    .CanIfTxPduCanIdType_i = STANDARD_CAN,
    .CanIfTxPduId = 3,
    .CanIfTxPduPnFilterPdu = FALSE,
    .CanIfTxPduReadNotifyStatus = FALSE,
    .CanIfTxPduTriggerTransmit = FALSE,
    .CanIfTxPduTruncation = FALSE,
    .CanIfTxPduType_i = STATIC,
    .CanIfTxPduUserTxConfirmationUL_i = CAN_TP,
    .CanIfTxPduBufferRef=
    {
      &CanIfBufferCfgInstance[1]
    },
    .CanIfTxPduRef = 0
   },
   {
    .CanIfTxPduCanId = 9,
    .CanIfTxPduCanIdMask = 0xF4,
    .CanIfTxPduCanIdType_i = STANDARD_CAN,
    .CanIfTxPduId = 4,
    .CanIfTxPduPnFilterPdu = FALSE,
    .CanIfTxPduReadNotifyStatus = FALSE,
    .CanIfTxPduTriggerTransmit = FALSE,
    .CanIfTxPduTruncation = FALSE,
    .CanIfTxPduType_i = STATIC,
    .CanIfTxPduUserTxConfirmationUL_i = PDUR,
    .CanIfTxPduBufferRef=
    {
      &CanIfBufferCfgInstance[0]
    },
    .CanIfTxPduRef = 0
   }
};



//CanIfHthCfg CanIfHthCfgInstance[2] = {
//    {
//      .CanIfHthCanCtrlIdRef = &(CanIfCtrlCfgInstance[0]) ,
//      .CanIfHthIdSymRef = &(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[0])
//    },
//    {
//      .CanIfHthCanCtrlIdRef = &(CanIfCtrlCfgInstance[0]) ,
//      .CanIfHthIdSymRef = &(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[1])
//    }
//};


CanIfInitHohCfg CanIfInitHohCfgInstance[2] = { CanIfHrhCfgInstance , CanIfHthCfgInstance};

CanIfInitCfg CanIf_initConfigTypeInstance[1]= {
        {
        .CanIfInitCfgSet[0] =0,                           // uint8  CanIfInitCfgSet;
        .CanIfMaxBufferSize = 5,                                  // uint32 CanIfMaxRxPduCfg;
        .CanIfMaxRxPduCfg = 1,                                  // uint32 CanIfMaxTxPduCfg;
        .CanIfMaxTxPduCfg = 5,                                  // uint64 CanIfMaxBufferSiz;
        .CanIfHohConfigPtr = CanIfInitHohCfgInstance,            // const CanIfInitHohCfg* CanIfHohConfigPtr;
        .CanIfRxPduConfigPtr = &CanIf_rxPduConfigTypeInstance[0],      // const CanIfRxPduCfg*  CanIfRxPduConfigPtr;
        .CanIfTxPduConfigPtr = &CanIf_txPduConfigTypeInstance[0],  // const CanIfTxPduCfg* CanIfTxPduConfigPtr;
         }
};


///////////////////////////////////WAKEUPSUPPORTSOURCEREF ????//////////////////////////

CanIfCtrlCfg CanIfCtrlCfgInstance[3] = {
//  {CanIfCtrlId , CanIfCtrlWakeupSupport , CanIfCtrlCanCtrlRef}
    {
     .CanIfCtrlId = 0,
     .CanIfCtrlWakeupSupport = CANIF_WAKEUP_SUPPORT_NO_WAKEUP ,
     .CanIfCtrlCanCtrlRef = &(CanContainer.CanConfigSet.CanController[0])
    },
    {
     .CanIfCtrlId = 2 ,
     .CanIfCtrlWakeupSupport = CANIF_WAKEUP_SUPPORT_NO_WAKEUP ,
     .CanIfCtrlCanCtrlRef = &CanContainer.CanConfigSet.CanController[0]
    },
    {
     .CanIfCtrlId = 3 ,
     .CanIfCtrlWakeupSupport = CANIF_WAKEUP_SUPPORT_NO_WAKEUP ,
     .CanIfCtrlCanCtrlRef = &CanContainer.CanConfigSet.CanController[1]
    }
};

// ******************  Nada ****************** /n

CanIf_ConfigType CanIf_configTypeInstance[1] = {
       {
        .ControllerConfig = CanIfCtrlCfgInstance,
        .InitConfig = &CanIf_initConfigTypeInstance
       }
        // &CanIf_transceiverConfigTypeInstance,
        // canControllerIdType,Configuration_arr
};


