/*
 * Can_GeneralTypes.h
 *
 *  Created on: May 3, 2018
 *      Author: Ahmed Usama Khalifa
 */

/*[SWS_CAN_00487] The types specified in Can_GeneralTypes shall be declared in Can_GeneralTypes.h */
/*[SWS_Can_00439]ˆThe content of Can_GeneralTypes.h shall be protected by a CAN_GENERAL_TYPES define. */
/*[SWS_Can_00440]If different CAN drivers are used, only one instance of this file has to be included in the source tree.
For implementation all Can_GeneralTypes.h related types in the documents mentioned before shall be considered.*/

#ifndef INCLUDES_CAN_GENERALTYPES_H_
#define INCLUDES_CAN_GENERALTYPES_H_
#define TRUE 1U
#define FALSE 0U
#define BOFF 0xE0U
#define EPASS 0x60U
#define EWARN 0x40U
#define STANDARD        0U
#define EXTENDED        1U
#define MIXED           2U
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
#define POLLING    2U

#include  "Can_Cfg.h"
#include "Mcu_Cfg.h"


/*
Can_GeneralTypes.h shall contain all types and constants that
are shared among the AUTOSAR CAN modules Can, CanIf and CanTrcv.
 */
typedef uint32_t Can_IdType;
typedef uint32_t Can_HwHandleType ;
typedef uint32_t PduIdType;

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
      uint8_t controllerlId;
      Can_IdType id;
      Can_HwHandleType hoh;
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
   /*  typedef enum CanProcessing
         {
            INTERRUPT,
            POLLING
         }CanProcessing;*/

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


         /* Reference to the CPU clock configuration,/
          * which is set in the MCU driver configuration./
          * COMMENTED AS ITS DESTINATION IS MCU
          */
         Mcu_PerClockConfigType  *CanCpuClockRef;

         /* This container contains bit timing related configuration parameters of the CAN /
          * controller(s).The Multiplicity is 1..many /
          */
         CanControllerBaudrateConfig  CanControllerBaudrateConfig[Max_num_of_baudrates];

         /* Reference to baud rate configuration container configured for the Can Controller.
          * The Multiplicity is 1.
          */
         CanControllerBaudrateConfig  *CanControllerDefaultBaudrate;


     }CanController;

         /*
           This container is only valid for HRHs and contains /
           the configuration (parameters) of one hardware filter.
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
          * transmit HOH
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
          * Specifies if the HardwareObject is used as transmit or as Receive object
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
         bool CanHardwareObjectUsesPolling;

         CanMainFunctionRWPeriods* CanMainFunctionRWPeriodRef;

     }CanHardwareObject;


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

     }CanConfigSet;
     typedef struct CanGeneral
     {
         /*
          * contains the parameter for configuring the period for cyclic call to
          *  Can_MainFunction_Read or Can_MainFunction_Write depending on the referring item
          */
         CanMainFunctionRWPeriods CanMainFunctionRWPeriods[2U];/*this number of read write period shall be generated instead of 2*/


     }CanGeneral;

     /* Can:
      * This container holds the configuration of a single CAN Driver.
      */
     typedef struct Can{

         CanGeneral CanGeneral;

         CanConfigSet CanConfigSet;
     }Can_ConfigType;





#endif /* INCLUDES_CAN_GENERALTYPES_H_ */
