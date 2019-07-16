#ifndef INCLUDES_CAN_CFG_H_  
#define INCLUDES_CAN_CFG_H_  



#define False 0U  
#define True  1U 
#define  CanSetBaudrateApi 1U
#define  CanVersionInfoApi 0U
#define  CanIndex 0U
#define  CanMultiplexedTransmission 0U
#define  CanMainFunctionBusoffPeriod 1U
#define  CanDevErrorDetect 0U
#define  CanTimeoutDuration 1U
#define  CanMainFunctionModePeriod 1U





#define UserCANCfg \
{.CanConfigSet.CanController =\
    {\
{\
.CanControllerId = 0U,\
.CanControllerActivation = False,\
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
.CanControllerBaudRate = 200U,\
.CanControllerPropSeg = 2U,\
.CanControllerSeg1 = 3U,\
.CanControllerSeg2 = 4U,\
.CanControllerSyncJumpWidth = 2U,\
.CanControllerBaudRateConfigID = 1U,\
        }\
       }\
      },\
{\
.CanControllerId = 1U,\
.CanControllerActivation = False,\
.CanControllerBaseAddress = 0x40041000U,\
.CanCpuClockRef=&McuPerClockConfigData,\
.CanControllerDefaultBaudrate = &CanContainer.CanConfigSet.CanController[1U].CanControllerBaudrateConfig[0U],\
.CanControllerBaudrateConfig=\
{\
 {\
.CanControllerBaudRate = 300U,\
.CanControllerPropSeg = 2U,\
.CanControllerSeg1 = 6U,\
.CanControllerSeg2 = 7U,\
.CanControllerSyncJumpWidth = 4U,\
.CanControllerBaudRateConfigID = 0U,\
        }\
       }\
 }\
 },\
.CanConfigSet.CanHardwareObject =\
 {\
  {\
.CanHandleType = FULL,\
.CanObjectType = transmit,\
.CanIdType = STANDARD,\
.CanObjectId = 0U,\
.CanTriggerTransmitEnable = False,\
.CanHwObjectCount = 1U,\
.CanControllerRef = &CanContainer.CanConfigSet.CanController[0],\
 },\
  {\
.CanHandleType = FULL,\
.CanObjectType = receive,\
.CanIdType = STANDARD,\
.CanObjectId = 1U,\
.CanTriggerTransmitEnable = False,\
.CanHwObjectCount = 1U,\
.CanControllerRef = &CanContainer.CanConfigSet.CanController[0],\
 .CanHwFilter=\
 {\
.CanHwFilterMask =0xFFFFFFFFU,\
.CanHwFilterCode =0x0U,\
 }\
 }\
 }\
};
#define  NUM_OF_HTH  1U
#define  NUM_OF_HRH  1U
#define  NUM_OF_HOH  2U
#define  Max_CanHwObjectCount  1U
#define  Max_num_of_baudrates  2U
#define  NUM_OF_CAN_CONTROLLERS  2U





#define INTERRUPT 0U  
#define  POLLING 2U 
#define  CanTxProcessing0 0U
#define  CanRxProcessing0 0U
#define  CanBusoffProcessing0 0U
#define  CanTxProcessing1 0U
#define  CanRxProcessing1 0U
#define  CanBusoffProcessing1 0U



#endif
