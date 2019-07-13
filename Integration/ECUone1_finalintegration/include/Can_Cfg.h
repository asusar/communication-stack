/*
 * Static_Can_Cfg.h
 *
 *  Created on: May 3, 2018
 *      Author: Ahmed Usama Khalifa
 */
#ifndef INCLUDES_CAN_CFG_H_
#define INCLUDES_CAN_CFG_H_



#define False 0U
#define True  1U



#define  CanVersionInfoApi False
#define  CanIndex 0U
#define  CanMainFunctionModePeriod 0U
#define  CanMultiplexedTransmission True
#define  CanSetBaudrateApi True
#define  CanDevErrorDetect False
#define  CanTimeoutDuration 0.5





#define UserCANCfg \
{.CanConfigSet.CanController =\
    {\
{\
.CanControllerId = 0U,\
.CanControllerActivation = True,\
.CanControllerBaseAddress = 0x40040000U,\
.CanCpuClockRef=&McuPerClockConfigData,\
.CanControllerDefaultBaudrate = &CanContainer.CanConfigSet.CanController[0U].CanControllerBaudrateConfig[0U],\
.CanControllerBaudrateConfig=\
{\
 {\
.CanControllerBaudRate = 500U,\
.CanControllerPropSeg = 2U,\
.CanControllerSeg1 = 6U,\
.CanControllerSeg2 = 7U,\
.CanControllerSyncJumpWidth = 4U,\
.CanControllerBaudRateConfigID = 0U,\
        },\
 {\
.CanControllerBaudRate = 500U,\
.CanControllerPropSeg = 2U,\
.CanControllerSeg1 = 3U,\
.CanControllerSeg2 = 4U,\
.CanControllerSyncJumpWidth = 2U,\
.CanControllerBaudRateConfigID = 1U,\
        },\
 {\
.CanControllerBaudRate = 400U,\
.CanControllerPropSeg = 2U,\
.CanControllerSeg1 = 6U,\
.CanControllerSeg2 = 7U,\
.CanControllerSyncJumpWidth = 2U,\
.CanControllerBaudRateConfigID = 2U,\
        },\
 {\
.CanControllerBaudRate = 400U,\
.CanControllerPropSeg = 2U,\
.CanControllerSeg1 = 6U,\
.CanControllerSeg2 = 7U,\
.CanControllerSyncJumpWidth = 3U,\
.CanControllerBaudRateConfigID = 3U,\
        },\
 {\
.CanControllerBaudRate = 150U,\
.CanControllerPropSeg = 2U,\
.CanControllerSeg1 = 7U,\
.CanControllerSeg2 = 8U,\
.CanControllerSyncJumpWidth = 2U,\
.CanControllerBaudRateConfigID = 4U,\
        },\
 {\
.CanControllerBaudRate = 100U,\
.CanControllerPropSeg = 2U,\
.CanControllerSeg1 = 6U,\
.CanControllerSeg2 = 7U,\
.CanControllerSyncJumpWidth = 4U,\
.CanControllerBaudRateConfigID = 5U,\
        }\
       }\
      },\
{\
.CanControllerId = 1U,\
.CanControllerActivation = True,\
.CanControllerBaseAddress = 0x40041000U,\
.CanCpuClockRef=&McuPerClockConfigData,\
.CanControllerDefaultBaudrate = &CanContainer.CanConfigSet.CanController[1U].CanControllerBaudrateConfig[0U],\
.CanControllerBaudrateConfig=\
{\
 {\
.CanControllerBaudRate = 500U,\
.CanControllerPropSeg = 2U,\
.CanControllerSeg1 = 6U,\
.CanControllerSeg2 = 7U,\
.CanControllerSyncJumpWidth = 4U,\
.CanControllerBaudRateConfigID = 0U,\
        }\
       }\
 }\
 }\
};

#define  CanTxProcessing0 0U
#define  CanRxProcessing0 0U
#define  CanBusoffProcessing0 0U
#define  CanTxProcessing1 0U
#define  CanRxProcessing1 0U
#define  CanBusoffProcessing1 0U

#define hohMap \
{.CanConfigSet.CanHardwareObject =\
    {\
        {\
           .CanHandleType = FULL,\
           .CanObjectType = transmit,\
           .CanIdType = STANDARD,\
           .CanHwObjectCount=1,\
           .CanObjectId=0,\
           .CanTriggerTransmitEnable = FALSE,\
           .CanFdPaddingValue = 0U,\
           .CanControllerRef = &CanContainer.CanConfigSet.CanController[0],\
        },\
             {\
           .CanHandleType = FULL,\
           .CanObjectType = transmit,\
           .CanIdType = STANDARD,\
           .CanHwObjectCount=1,\
           .CanObjectId=1,\
           .CanTriggerTransmitEnable = FALSE,\
           .CanFdPaddingValue = 0U,\
           .CanControllerRef = &CanContainer.CanConfigSet.CanController[0],\
        },\
        {\
           .CanHandleType = FULL,\
           .CanObjectType = receive,\
           .CanIdType = STANDARD,\
           .CanHwObjectCount=1,\
           .CanObjectId= 1,\
           .CanTriggerTransmitEnable = FALSE,\
           .CanFdPaddingValue = 0U,\
           .CanControllerRef = &CanContainer.CanConfigSet.CanController[0],\
           .CanHwFilter=\
           {\
             .CanHwFilterMask=0xFFFFFFFF,\
             .CanHwFilterCode=0x1,\
          }\
        }\
    }\
};


#define  NUM_OF_HTH  2U
#define  NUM_OF_HRH  1U
#define  NUM_OF_HOH  3U
#define  Max_CanHwObjectCount  1U
#define  Max_num_of_baudrates  6U
#define  NUM_OF_CAN_CONTROLLERS  2U

#define SYSCTL_PERIPH \
    {\
        {.AHBClocksEnable = 0xf0003400U,\
         .APB1ClocksEnable = 0U,\
         .APB2ClocksEnable = 0U\
        },\
        {.AHBClocksEnable = 0xf0003401U,\
         .APB1ClocksEnable = 0U,\
         .APB2ClocksEnable = 0U\
        }\
    };

#endif /* INCLUDES_CAN_CFG_H_ */

