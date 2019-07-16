#define  CanVersionInfoApi False
#define  CanIndex 0U
#define  CanMainFunctionModePeriod 0U
#define  CanMultiplexedTransmission False
#define  CanSetBaudrateApi False
#define  CanDevErrorDetect False
#define  CanTimeoutDuration 0U





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
.CanObjectId = 0U,\
.CanFdPaddingValue = 0U,\
.CanTriggerTransmitEnable = False,\
.CanHwObjectCount = 1U,\
.CanControllerRef = &CanContainer.CanConfigSet.CanController[0],\
 }\
 }\
};
#define  NUM_OF_HTH  1U
#define  NUM_OF_HRH  0U
#define  NUM_OF_HOH  1U
#define  Max_CanHwObjectCount  1U
#define  Max_num_of_baudrates  1U
#define  NUM_OF_CAN_CONTROLLERS  2U
