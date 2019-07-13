/*
 * Can_GeneralTypes.h
 *
 *  Created on: May 3, 2018
 *      Author: Ahmed Usama Khalifa
 */

/*[SWS_CAN_00487]⌈ The types specified in Can_GeneralTypes shall be declared in Can_GeneralTypes.h */
/*[SWS_Can_00439]⌈The content of Can_GeneralTypes.h shall be protected by a CAN_GENERAL_TYPES define. */
/*[SWS_Can_00440]⌈If different CAN drivers are used, only one instance of this file has to be included in the source tree.
For implementation all Can_GeneralTypes.h related types in the documents mentioned before shall be considered.*/

#ifndef INCLUDES_CAN_GENERALTYPES_H_
#define INCLUDES_CAN_GENERALTYPES_H_
#define TRUE 1U
#define FALSE 0U
#define BOFF 0xE0U
#define EPASS 0x60U
#define EWARN 0x40U
#define CAN_E_PARAM_POINTER 1U
#define CAN_E_PARAM_HANDLE  2U
#define CAN_E_PARAM_DATA_LENGTH 3U
#define CAN_E_PARAM_CONTROLLER  4U
#define CAN_E_UNINIT 5U
#define CAN_E_TRANSITION 6U
#define CAN_E_PARAM_BAUDRATE 7U
#define CAN_E_ICOM_CONFIG_INVALID 8U
#define CAN_E_INIT_FAILED 9U
#define CAN_E_PARAM_POINTER 10U

#define INTERRUPT  0U
#define mixed      1U
#define POLLING    2U

#include  "include/Can_Cfg.h"
#include "include/Mcu_Cfg.h"
#include "include/ComStack_Types.h"
#include "stdbool.h"


/*
Can_GeneralTypes.h shall contain all types and constants that
are shared among the AUTOSAR CAN modules Can, CanIf and CanTrcv.
 */
typedef uint32_t Can_IdType;
typedef uint32_t Can_HwHandleType ;

typedef enum {
 STANDARD,
 EXTENDED,
// MIXED
}CanIdType;


typedef enum {
                    confirmed,
                    un_confirmed
             }confirmation;
struct Can_objectCheck
      {
       confirmation Confirmation;
       PduIdType  PduId;
       uint8_t mail_box;
      };

typedef struct Can_PduType
    {
      PduIdType  swPduHandle;
      uint8_t      length;
      Can_IdType id;
      uint8_t*     sdu;
    } Can_PduType;

typedef enum {
    CAN_CS_UNINIT  =  0x00,
    CAN_CS_STARTED =  0x01,
    CAN_CS_STOPPED =  0x02,
    CAN_CS_SLEEP   =  0x03
    }Can_ControllerStateType;
/* Can_StateTransitionType */
typedef enum {
      CAN_T_START,
      CAN_T_STOP,
      CAN_T_SLEEP,
      CAN_T_WAKEUP
    }Can_StateTransitionType;

typedef enum {

      CAN_BUSY=0x2
    } Can_ReturnType;

typedef struct Can_HwType
    {
      Can_IdType id;
      Can_HwHandleType hoh;
      uint8_t controllerlId;
    }Can_HwType;

    typedef enum{
        CAN_UNINIT,
        CAN_READY
    }Can_StateType;

    typedef enum{
        CAN_ERRORSTATE_ACTIVE,
        CAN_ERRORSTATE_PASSIVE,
        CAN_ERRORSTATE_BUSOFF
     }Can_ErrorStateType;

     typedef uint32_t Can_IdType;

         /* This container contains bit timing related configuration/
          * parameters of the CAN controller(s)./
          * This container is a Sub container of "CanController" container with/
          * upperMultiplicity = * ,lowerMultiplicity = 1/
          */

     typedef struct CanControllerBaudrateConfig
         {

         /*Specifies the baud rate of the controller in kbps.
          *Range 0 .. 2000, Multiplicity 1
          */
         uint32_t CanControllerBaudRate;

         /*Specifies propagation delay in time quantas.
          *Range 0 .. 255, Multiplicity 1 */

         uint8_t CanControllerPropSeg;

         /*Specifies phase segment 1 in time quantas.
          *Range 0 .. 255, Multiplicity 1 */

         uint8_t CanControllerSeg1;

         /*Specifies phase segment 1 in time quantas.
          *Range 0 .. 255, Multiplicity 1 */

         uint8_t CanControllerSeg2;

         /*Specifies the synchronization jump width for the controller in time quanta.
          *Range 0 .. 255, Multiplicity 1 */

         uint8_t CanControllerSyncJumpWidth;

         /*Uniquely identifies a specific baud rate configuration. This ID is used by SetBaudrate API.
          *Range 0 .. 65535,  Multiplicity 1
          *Default value = 0 */

         uint16_t CanControllerBaudRateConfigID;
         }CanControllerBaudrateConfig;
         /*
          * Enables / disables API Can_MainFunction_Read()
          * for handling PDU reception events in polling mode.
          *
          *
          * Enables / disables API Can_MainFunction_Write()
          * for handling PDU transmission events in polling mode.
          *
          *
          * Enables / disables API Can_MainFunction_Wakeup()
          * for handling wakeup events in polling mode.
          */
//     typedef enum CanProcessing
//         {
//            INTERRUPT,
//            POLLING
//         }CanProcessing;

         /* This container "CanController" contains the configuration /
          * parameters of the CAN controller(s)./
          * This container is a Sub container of "CanConfigSet" container with /
          * upperMultiplicity = * ,lowerMultiplicity = 1 */

     typedef struct CanController
     {

         /* This parameter provides the controller ID which is unique in a given CAN Driver./
          * The value for this parameter starts with 0 and continue without any gaps./
          * The Range of CanControllerId is 0 .. 255, with Multiplicity 1.
          */
         uint8_t CanControllerId;

         /* This parameter defines if a CAN controller is used in the configuration.
          * The Multiplicity 1.
          */
         bool CanControllerActivation;

         /* This parameter specifies the CAN controller base address.
          * The Range of CanControllerBaseAddress is 0 .. 4294967295, with Multiplicity 1
          */

         uint32_t CanControllerBaseAddress;

         /* This parameter defines CAN driver support for wake up over CAN Bus.
          * The Multiplicity 1
          */

         bool CanWakeupSupport;

         /* Adds/removes the service Can_CheckWakeup() from the code.
          * True: Can_CheckWakeup can be used. False: Can_CheckWakeup cannot be used.
          * The Multiplicity 1.
          * Default value = false
          */

         bool CanWakeupFunctionalityAPI;

         /*  This parameter contains a reference to the Wake up Source for this controller /
          *  as defined in the ECU State Manager./
          *  Multiplicity 0..1 /
          *  COMMENTED AS ITS DESTINATION IS ECUM
          */

         //EcuM_WakeupSourceType * CanWakeupSourceRef;

         /* Reference to the CPU clock configuration,/
          * which is set in the MCU driver configuration./
          * COMMENTED AS ITS DESTINATION IS MCU
          */
         Mcu_PerClockConfigType  *CanCpuClockRef;

         /* This container contains bit timing related configuration parameters of the CAN /
          * controller(s).The Multiplicity is 1..many /
          */
         CanControllerBaudrateConfig  CanControllerBaudrateConfig[Max_num_of_baudrates ];

         /* Reference to baud rate configuration container configured for the Can Controller.
          * The Multiplicity is 1.
          */
         CanControllerBaudrateConfig  *CanControllerDefaultBaudrate;

         /* Enables/disables API Can_MainFunction_Write() for handling PDU transmission /
          * events in polling mode.Its range: INTERRUPT,POLLING.
          */
//           CanProcessing CanTxProcessing;

         /* Enables/disables API Can_MainFunction_Read() for handling PDU reception /
          * events in polling mode. Its range: INTERRUPT,POLLING.
          */
//           CanProcessing CanRxProcessing;

         /* Enables/disables API Can_MainFunction_BusOff() for handling bus off events/
          * in polling mode. Its range: INTERRUPT,POLLING.
          */

//           CanProcessing CanBusoffProcessing;

         /* Enables / disables API Can_MainFunction_Wakeup() for handling wake up events in polling mode.
          * Its range: INTERRUPT,POLLING. */
//           CanProcessing CanWakeupProcessing;
     }CanController;

         /*
          * This container is only valid for HRHs and contains /
          * the configuration (parameters) of one hardware filter.
          */
     typedef struct CanHwFilter
     {
         /*
          * Describes a mask for hardware-based filtering of CAN identifiers./
          * The CAN identifiers of incoming messages are masked with the appropriate/
          * CanFilterMaskValue.Bits holding a 0 mean don't care,/
          * i.e. do not compare the message's identifier in the respective bit position./
          * The mask shall be build by filling with leading 0./
          * The In case of CanIdType EXTENDED or MIXED a 29 bit mask shall
          */
         uint32_t CanHwFilterMask   ;
         /*
          * Specifies (together with the filter mask) the identifiers range that passes the hardware filter.
          */
         uint32_t CanHwFilterCode ;
     }CanHwFilter;


     typedef enum CanObjectType
     {
         /*
          * Receive HOH
          */
         receive,
         /*
          * Transmit HOH
          */
         transmit
     }CanObjectType;
         /*
          * Specifies the type (Full-CAN or Basic-CAN) of a hardware object.
          *
          */
     typedef enum CanHandleType
     {

      BASIC,

      FULL

     }CanHandleType;



         /*
          * This container contains the parameter for configuring the period for cyclic call
          * to Can_MainFunction_Read or Can_MainFunction_Write depending on the referring item.
          */
     typedef struct CanMainFunctionRWPeriods
     {
         /*
          * Unit is seconds. more info. in CAN SWS ->> 10.2.9
`
          */
         float CanMainFunctionPeriod;
     }CanMainFunctionRWPeriods;

         /*
          * This container contains the configuration (parameters) of CAN Hardware Objects.
          */
     typedef struct CanHardwareObject
     {
         /*
          * Reference to CAN Controller to which the HOH is associated to.
          *
          */
         CanController* CanControllerRef ;
         /*
          * Specifies whether the IdValue is of type
          *  standard identifier
          *  extended identifier
          *   mixed mode
          */
         Can_IdType CanIdType;
         /*
          * Holds the handle ID of HRH or HTH. The value of this parameter is unique in a given CAN Driver,
          * and it should start with 0 and continue without any gaps.
          *The HRH and HTH Ids share a common ID range.
          * Example: HRH0-0, HRH1-1, HTH0-2, HTH1-3
          *
          */
         uint16_t CanObjectId;
         /*
          * Specifies if the HardwareObject is used as Transmit or as Receive object
          *
          */
         CanObjectType CanObjectType;
         /*
          * Specifies the type (Full-CAN or Basic-CAN) of a hardware object.
          */
         CanHandleType CanHandleType;
         /*
          * This container is only valid for HRHs and contains the configuration (parameters) of one hardware filter.
          */
         CanHwFilter CanHwFilter;//done
         /*
          * Number of hardware objects used to implement one HOH.
          *  In case of a HRH this parameter defines the number of elements in the hardware FIFO or the number of shadow buffers,
          *  in case of a HTH it defines the number of hardware objects used for multiplexed transmission or
          *  for a hardware FIFO used by a FullCAN HTH.
          *
          */
         uint8_t CanHwObjectCount;
         /*
          * This parameter defines if or if not Can supports the trigger-transmit API for this handle.
          *
          */
         bool CanTriggerTransmitEnable;
         /*
          *
          * Reference to CanMainFunctionPeriod
          */
         CanMainFunctionRWPeriods* CanMainFunctionRWPeriodRef;

       Can_HwHandleType HOH ;
       uint32_t CanFdPaddingValue;
     }CanHardwareObject;

         /*
          * This parameter defines the operation,
          * which shall be used to verify the signal value creates a wakeup condition.
          *
          */
     typedef enum CanIcomSignalOperation{
         /*
          * The received signal value masked by CanIcomSignalMask has/
          * at least one bit set in common withCanIcomSignalValue (binary AND).
          */
         AND,
         /*
          * The received signal value masked by CanIcomSignalMask is equal to CanIcomSignalValue.
          *
          */
         EQUAL,
         /*
          * The received signal value masked by CanIcomSignalMask is strictly greater than CanIcomSignalValue.
          *  Values are interpreted as unsigned integers.
          *
          */
         GREATER,
         /*
          * The received signal value masked by CanIcomSignalMask is strictly smaller than CanIcomSignalValue.
          *  Values are interpreted as unsigned integers.
          *
          */
         SMALLER,
         /*
          * The received signal value masked by CanIcomSignalMask then XORed to CanIcomSignalValue is not null.
          *
          */
         XOR,
     }CanIcomSignalOperation;

         /*
          * This enum didn't support In SWS Can driver
          *
          */
     typedef enum ComSignal
     {
      Notused,
     }ComSignal;

     typedef struct CanIcomRxMessageSignalConfig
     {
         /*
          *This parameter shall be used to mask a signal in the payload of a CAN message.
          *The mask is binary AND with the signal payload.
          *The The result will be used in combination of the operations/
          *The defined in CanIcomSignalOperation with the CanIcomSignalValue.
          *
          */
         uint32_t CanIcomSignalMask;
         /*
          * This parameter defines the operation,
          *  which shall be used to verify the signal value creates a wakeup condition.
          *
          */
         CanIcomSignalOperation CanIcomSignalOperation;
         /*
          *
          * This parameter shall be used to define a signal value which shall be compared/
          * (CanIcomSignalOperation) with the masked CanIcomSignalMask value of the received signal (CanIcomSignalRef).
          */
         uint32_t CanIcomSignalValue;
         /*
          * This parameter defines a reference to the signal which shall be checked additional to the message id (CanIcomMessageId).
          * This reference is used for documentation to define which ComSignal originates this filter setting./
          * All signals being referred by this reference shall point to the same PDU.
          *
          */
         ComSignal CanIcomSignalRef;
     }CanIcomRxMessageSignalConfig;

         /*
          * This container contains the configuration parameters for/
          * the wakeup causes for matching received messages.
          *  It has to be configured as often as received messages are/
          *  defined as wakeup cause.
          */

     typedef struct CanIcomRxMessage
     {
         /*
          * This parameter defines that the MCU shall wake if the message with the ID is received n times on the communication channel.
          *
          */
         uint16_t CanIcomCounterValue;
          /*
           * This parameter defines the message ID the wakeup causes of this CanIcomRxMessage are configured for.
           * In addition a mask (CanIcomMessageIdMask) can be defined,
           * in that case it is possible to define a range of rx messages,
           * which can create a wakeup condition.
           *
           */
         uint32_t CanIcomMessageId;
          /*
          * Describes a mask for filtering of CAN identifiers.
          * he CAN identifiers of incoming messages are masked with this CanIcomMessageIdMask.
          * If the masked identifier matches the masked value of CanIcomMessageId,
          * it can create a wakeup condition for this CanIcomRxMessage. Bits holding a 0 mean don't care,
          * i.e. do not compare the message's identifier in the respective bit position.
          * The mask shall be build by filling with leading 0.
          */
         uint32_t CanIcomMessageIdMask;
         /*
          * This parameter defines that the MCU shall wake if the message with the ID is not received/
          * for a specific time in s on thecommunication channel.
          *
          */
         float CanIcomMissingMessageTimerValue;
         /*
          * This parameter defines that the MCU shall wake if a payload error occurs
          *
          */
         bool CanIcomPayloadLengthError;
         /*
          * This container contains the configuration parameters for the wakeup causes for matching signals.
          * It has to be configured as often as a signal is defined as wakeup cause.
          * If at least one Signal conditions defined in a CanIcomRxMessageSignalConfig evaluates to true or if/
          * no CanIcomRxMessageSignalConfig are defined,
          * the whole wakeup condition is considered to be true.
          * All instances of this container refer to the same frame/pdu (see CanIcomMessageId).
          *
          */
         CanIcomRxMessageSignalConfig CanIcomRxMessageSignalConfig;
     }CanIcomRxMessage;

         /*
          * This container contains the configuration parameters of /
          * the wakeup causes to leave the power saving mode.
          */
     typedef struct CanIcomWakeupCauses
     {
         /*
          * This container contains the configuration parameters for/
          * the wakeup causes for matching received messages.
          *  It has to be configured as often as received messages are/
          *  defined as wakeup cause.
          */
         CanIcomRxMessage CanIcomRxMessage;
     }CanIcomWakeupCauses;

     /*
      * This container contains the configuration parameters of the ICOM Configuration.
      */
     typedef struct CanIcomConfig
     {
         /*
          * This parameter identifies the ID of the ICOM configuration.
          */
         uint8_t CanIcomConfigId;
         /*
          * This parameter defines that the MCU shall wake if the bus off is detected or not.
          */
         bool CanIcomWakeOnBusOff;
         /*
          * This container contains the configuration parameters of the wakeup
          * causes to leave the power saving mode
          */
         CanIcomWakeupCauses CanIcomWakeupCauses ;
     }CanIcomConfig;

         /*
          * This container contains the parameters for configuring pretended networking
          */

     typedef struct CanIcom
     {
         /*
          * This container contains the configuration parameters of the ICOM Configuration.
          */
         CanIcomConfig CanIcomConfig;
     }CanIcom;
         /*
          * This container contains the configuration parameters and sub containers of the AUTOSAR Can module.
          *
          */
     typedef struct CanConfigSet
     {
         /*
          * This container contains the configuration parameters of the CAN controller(s).
          */
         CanController CanController[NUM_OF_CAN_CONTROLLERS];
         /*
          * This container contains the configuration (parameters) of CAN Hardware Objects.
          */
         CanHardwareObject CanHardwareObject[ NUM_OF_HOH ];
         /*
          * This container contains the parameters for configuring pretended networking
          */
         CanIcom CanIcom;
     }CanConfigSet;
         /*
          * Defines the level of Pretended Networking.
          * This parameter is reserved for future implementations (Pretended Networking level 2).
          */
     typedef enum CanIcomLevel
     {
         CAN_ICOM_LEVEL_ONE,
         CAN_ICOM_LEVEL_TWO
     } CanIcomLevel ;

         /*
         * Defines the variant, which is supported by this CanController
         */
     typedef enum CanIcomVariant
     {
         CAN_ICOM_VARIANT_HW,
         CAN_ICOM_VARIANT_NONE,
         CAN_ICOM_VARIANT_SW,
     }CanIcomVariant ;

         /*
          * This container contains the general configuration parameters of the ICOM Configuration
          */
     typedef struct CanIcomGeneral
     {
         CanIcomLevel CanIcomLevel ;
         CanIcomVariant CanIcomVariant ;
     }CanIcomGeneral;

         /*
          * CanGenreral: contains the parameters related each CAN Driver Unit.
          * NOTE: this srtucture does NOT support ERROR DETECTION
          */
     typedef struct CanGeneral
     {
         /*InstanceId of this module instance.If only 1 instance it shall have the Id 0 */



         //void * CanLPduReceiveCalloutFunction (void);

         /*
          * This parameter describes the period for cyclic
          * call to Can_MainFunction_Busoff. Unit is seconds
          */





         /*
          * This parameter describes the period for cyclic call
          *  to Can_MainFunction_Mode. Unit is seconds.
          */


         /*
          * describes the period for cyclic call
          *  to Can_MainFunction_Wakeup. Unit is seconds.
          */


         /*
          * Specifies if multiplexed transmission
          *  shall be supported.ON or OFF
          *  NOTE:
          *  dependency: CAN Hardware Unit supports multiplexed transmission
          */
//         bool CanMultiplexedTransmission ;

         /*
          * Selects support of Pretended Network features in Can driver.
          *   True: Enabled
          *   False: Disabled
          */
         bool CanPublicIcomSupport ;

         /*
          * Can_SetBaudrate API is optional if this parameter
          * true: the API shall be supported
          * otherwise the API isn't supported
          */
//         bool CanSetBaudrateApi ;

         /*
          * the max time for blocking function untill
          * the timeout is detected. Unit is seconds.
          */


         /*
          * This parameter contains a reference to the OsCounter
          * which is used by the CAN driver.
          */
         // pointer to the OScounter ??

         /*
          * The parameter refers to CanIfSupportTTCAN parameter in
          * the CAN Interface Module configuration.
          * The CanIfSupportTTCAN parameter defines whether TTCAN is supported
          */
         // Reference to [ CanIfPrivateCfg ] ??

         /*
          * contains the general configuration parameters of the ICOM Configuration
          */
         CanIcomGeneral CanIcomGeneral;

         /*
          * contains the parameter for configuring the period for cyclic call to
          *  Can_MainFunction_Read or Can_MainFunction_Write depending on the referring item
          */
         CanMainFunctionRWPeriods CanMainFunctionRWPeriods;


     }CanGeneral;

     /* Can:
      * This container holds the configuration of a single CAN Driver.
      */
     typedef struct Can{
         /*
          * CanGenreral: contains the parameters related each CAN Driver Unit.
          * NOTE: this srtucture does NOT support ERROR DETECTION
          */
         CanGeneral CanGeneral;
         /*
          * This container contains the configuration parameters and sub containers of the AUTOSAR Can module.
          *
          */
         CanConfigSet CanConfigSet;
     }Can_ConfigType; //should be named can_configtype //





#endif /* INCLUDES_CAN_GENERALTYPES_H_ */
