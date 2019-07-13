
#ifndef CANIF_TYPES_H_
#define CANIF_TYPES_H_

#include "include/Can_GeneralTypes.h"
#include "include/Can_Cfg.h"
#include "CanIf_Cfg.h"
#include "stdint.h"
#include "Platform_Types.h"
#include "ComStack_Types.h"
#include "stdbool.h"

typedef enum {
    EXTENDED_CAN = 0,
    EXTENDED_FD_CAN,
    STANDARD_CAN,
    STANDARD_FD_CAN
} CanIfTxPduCanIdType;

typedef enum {
    /** Channel is in the offline mode ==> no transmission or reception */
  CANIF_GET_OFFLINE = 0,
  /** Receive path of the corresponding channel is enabled and
   *  transmit path is disabled */
  CANIF_GET_RX_ONLINE,
  /** Transmit path of the corresponding channel is enabled and
   *  receive path is disabled */
  CANIF_GET_TX_ONLINE,
  /** Channel is in the online mode ==> full operation mode */
  CANIF_GET_ONLINE,
  /** Transmit path of the corresponding channel is in
   *  the offline mode ==> transmit notifications are processed but
   *  transmit requests are blocked. The receiver path is disabled. */
  CANIF_GET_OFFLINE_ACTIVE,
  /** Transmit path of the corresponding channel is in the offline
   *  active mode ==> transmit notifications are processed but transmit
   *  requests are blocked. The receive path is enabled. */
  CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE

} CanIf_ChannelGetModeType;


typedef struct{
    Can_ControllerStateType Controller_Mode;
    CanIf_ChannelGetModeType PduMode;
}CanIf_ChannelPrivateType;

typedef struct {
    boolean initRun;
    CanIf_ChannelPrivateType channelData[CANIF_CHANNEL_CNT];
}CanIf_GlobalType;


typedef struct{
    /* This parameter abstracts from the CAN Driver specific parameter
     * Controller. Each controller of all connected CAN Driver modules shall
     * be assigned to one specific ControllerId of the CanIf. Range:
     * 0..number of configured controllers of all CAN Driver modules */
    uint8 CanIfCtrlId;

    /* This parameter defines if a respective controller of the referenced CAN
     * Driver modules is queriable for wake up events */
    CanIf_WakeupSupportType CanIfCtrlWakeupSupport;

    /* This parameter references to the logical handle of the underlying CAN
        controller from the CAN Driver module to be served by the CAN
        Interface module. The following parameters of CanController config
        container shall be referenced by this link: CanControllerId,
        CanWakeupSourceRef */
    CanController* CanIfCtrlCanCtrlRef;
}CanIfCtrlCfg;

typedef struct {
    /** Lower CAN Identifier of a receive CAN L-PDU for identifier range
     *  definition, in which all CAN Ids shall pass the software filtering. Range: 11
     *  Bit for Standard CAN Identifier 29 Bit for Extended CAN Identifer */
    /*AUTOSAR 4.3 uint32 CanIfRxPduLowerCanId; */
    uint32 CanIfHrhRangeRxPduLowerCanId;

    /** Upper CAN Identifier of a receive CAN L-PDU for identifier range
     *  definition, in which all CAN Ids shall pass the software filtering. Range: 11
     *  Bit for Standard CAN Identifier 29 Bit for Extended CAN Identifer */
    /* AUTOSAR 4.3 uint32 CanIfRxPduUpperCanId; */
    uint32 CanIfHrhRangeRxPduUpperCanId;
} CanIfHrhRangeCfg;

typedef struct {

    /* The parameter refers to a particular HRH object in the CanDrv
     * configuration */
    const CanHardwareObject* CanIfHrhIdSymRef;

    /** Selects the hardware receive objects by using the HRH range/list from
     *  CAN Driver configuration to define, for which HRH a software filtering has
     *  to be performed at during receive processing. True: Software filtering is
     *  enabled False: Software filtering is disabled */
    bool CanIfHrhSoftwareFilter;

    /** Reference to controller Id to which the HRH belongs to. A controller can
     *  contain one or more HRHs. */
    CanIfCtrlCfg* CanIfHrhCanCtrlIdRef;

    /** Defines the parameters required for configuraing multiple
     *  CANID ranges for a given same HRH. */
    CanIfHrhRangeCfg* CanIfHrhRangeConfig;


} CanIfHrhCfg;

typedef struct{
    /* Reference to controller Id to which the HTH belongs to. A controller can contain one or more HTHs*/
    CanIfCtrlCfg* CanIfHthCanCtrlIdRef;

    /* The parameter refers to a particular HTH object in the CanDrvconfiguration */
    CanHardwareObject* CanIfHthIdSymRef;

}CanIfHthCfg;

/* CanIF RXIndication  */
typedef struct{

    CanIfHrhCfg* CanIfHrhCfgPrt;

    CanIfHthCfg* CanIfHthCfgPtr;

}CanIfInitHohCfg;


typedef struct{
    /* Lower CAN Identifier of a receive CAN L-PDU for identifier range
        definition, in which all CAN Ids are mapped to one PduId
     */
    uint32 CanIfRxPduCanIdRangeLowerCanId;

    /* Upper CAN Identifier of a receive CAN L-PDU for identifier range
        definition, in which all CAN Ids are mapped to one PduId. */
    uint32 CanIfRxPduCanIdRangeUpperCanId;


}CanIfRxPduCanIdRange;

typedef struct {
  /** CAN Identifier of Receive CAN L-PDUs used by the CAN Interface.
    * Exa: Software Filtering. This parameter is used if exactly one Can
    * Identifier is assigned to the Pdu. If a range is assigned then the
    * CanIfRxPduCanIdRange parameter shall be used.
    * Range: 11 Bit For Standard CAN Identifier ... 29 Bit For Extended CAN identifier */
    uint32 CanIfRxPduCanId;  //


  /** CAN Identifier of Receive CAN L-PDUs used by the CAN Interface. Exa:
   *  Software Filtering. Range: 11 Bit For Standard CAN Identifier ... 29 Bit For
   *  Extended CAN identifier */
    uint32 CanIfRxPduCanIdMask;  //

  /** Data Length code of received CAN L-PDUs used by the CAN Interface.
   *  Exa: DLC check. The data area size of a CAN L-PDU can have a range
   *  from 0 to 8 bytes.*/
    uint16 CanIfRxPduDataLength;  //

  /** Enables and disables the Rx buffering for reading of received L-PDU data.
   *  True: Enabled False: Disabled */
    bool CanIfRxPduReadData;  //

  /** CanIfReadRxPduNotifyStatus {CANIF_READRXPDU_NOTIFY_STATUS}
   *  Enables and disables receive indication for each receive CAN L-PDU for
   *  reading its' notification status. True: Enabled False: Disabled */
    bool CanIfRxPduReadNotifyStatus; //

  /** CAN Identifier of receive CAN L-PDUs used by the CAN Driver for CAN L-
   *  PDU transmission.
     *  EXTENDED_CAN  The CANID is of type Extended (29 bits)
   *  STANDARD_CAN  The CANID is of type Standard (11 bits) */
    CanIfTxPduCanIdType CanIfRxPduCanIdType; //


    /** ECU wide unique, symbolic handle for receive CAN L-SDU. It shall
    * fulfill ANSI/AUTOSAR definitions for constant defines.
    * Range: 0..max. number of defined CanRxPduIds */
    uint16 CanIfRxPduId;  //

    ////////////////////////////////////////////////////////////TO BE DISCUSSED ////////////////////////////////////////////

    /* This parameter defines the name of the <User_RxIndication>. This
      parameter depends on the parameter CANIF_RXPDU_USERRXINDICATION_UL. If
      CANIF_RXPDU_USERRXINDICATION_UL equals CAN_TP,
      CAN_NM, PDUR, XCP, CAN_TSYN, J1939NM or J1939TP, the name
      of the <User_RxIndication> is fixed. If
      CANIF_RXPDU_USERRXINDICATION_UL equals CDD, the name of
      the <User_RxIndication> is selectable. */
    uint16 CanIfRxPduUserRxIndicationName;  //

    /*This parameter defines the upper layer (UL) module to which the
        indication of the successfully received CANRXPDUID has to be routed
        via <User_RxIndication>. This <User_RxIndication> has to be invoked
        when the indication of the configured CANRXPDUID will be received
        by an Rx indication event from the CAN Driver module. If no upper
        layer (UL) module is configured, no <User_RxIndication> has to be
        called in case of an Rx indication event of the CANRXPDUID from the
        CAN Driver module. */
    CanIfRxPduUserRxConfirmationUL CanIfRxPduUserRxIndicationUL_i; //

  /** The HRH to which Rx L-PDU belongs to, is referred through this
   *  parameter. */
    CanIfHrhCfg* CanIfRxPduHrhIdRef;  //
    ////////////////////////////////////////////////////////////TO BE DISCUSSED ////////////////////////////////////////////

  /** Reference to the "global" Pdu structure to allow harmonization of handle
   *  IDs in the COM-Stack. */
    uint8* CanIfRxPduRef;  //

  /** Defines the type of software filtering that should be used
   *  for this receive object. */
    /* AUTOSAR 4.3 CanIf_SoftwareFilterTypeType CanIfSoftwareFilterType;*/
    /*VAR(CanIf_SoftwareFilterTypeType,AUTOMATIC) CanIfSoftwareFilterType; removed this parameter as its precompile and generic for all PDUs */


    CanIfRxPduCanIdRange* CanIfRxPduCanIdRangePtr; //


}CanIfRxPduCfg;



typedef struct{
    /*The HTH index "in the array of HTHs" which this buffer is mapped to
     * Reference to HTH, that defines the hardware object or the pool of
     * hardware objects configured for transmission. All the CanIf Tx L-PDUs
     * refer via the CanIfBufferCfg and this parameter to the HTHs if
     * TxBuffering is enabled, or not. */
    CanIfHthCfg* CanIfBufferHthRef;

    /*Size of the buffer*/
    uint8 CanIfBufferSize;
}CanIfBufferCfg;

typedef struct {

    /** CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-
     *  PDU transmission. Range: 11 Bit For Standard CAN Identifier ... 29 Bit For
     *  Extended CAN identifier */
    uint32 CanIfTxPduCanId;   ///



    /*Mask to make parts of the dynamic ID static*/
    uint32 CanIfTxPduCanIdMask; ///


    /** Defines the type of each transmit CAN L-PDU.
     *  DYNAMIC  CAN ID is defined at runtime.
     *  STATIC  CAN ID is defined at compile-time. */
    CanIfTxPduCanIdType CanIfTxPduCanIdType_i; ///


    /** ECU wide unique, symbolic handle for transmit CAN L-PDU. The
     *  CanIfCanTxPduId is configurable at pre-compile and post-built time.
     *  Range: 0..max. number of CantTxPduIds   PduIdType   CanTxPduId; */
    uint32 CanIfTxPduId; ///


    /* If CanIfPublicPnFilterSupport is enabled, by this parameter PDUs
     * could be configured which will pass the CanIfPnFilter.
     * If there is no CanIfTxPduPnFilterPdu configured per controller,
     * the corresponding controller applies no CanIfPnFilter */
    bool CanIfTxPduPnFilterPdu; ///

    /** Enables and disables transmit confirmation for each transmit CAN L-PDU
     *  for reading its notification status. True: Enabled False: Disabled */
    bool CanIfTxPduReadNotifyStatus; ///



    /*Determines if or if not CanIf shall use the trigger transmit API for this PDU */
    bool CanIfTxPduTriggerTransmit; ///



    /* Enables/disables truncation of PDUs that exceed the configured size. */
    bool CanIfTxPduTruncation;  ///


    /** CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-
     *  PDU transmission.
     *  EXTENDED_CAN  The CANID is of type Extended (29 bits).
     *  STANDARD_CAN  The CANID is of type Standard (11 bits). */
    CanIfTxPduType CanIfTxPduType_i; ///

    //uint16 CanIfTxPduUserTriggerTransmitName;



    //uint16 CanIfTxPduUserTxConfirmationName;


    CanIfRxPduUserRxConfirmationUL CanIfTxPduUserTxConfirmationUL_i;




    /*The buffer handle that the L-PDU maps to*/
    CanIfBufferCfg* CanIfTxPduBufferRef;   //
    /** Reference to the "global" Pdu structure to allow harmonization of handle
     *  IDs in the COM-Stack. */
    PduInfoType* CanIfTxPduRef; //
} CanIfTxPduCfg;

typedef struct{
    /* AUTOSAR 4.3 uint32 CanIfConfigSet; Selects the CAN Interface specific configuration setup. This type of the
        external data structure shall contain the post build initialization data for
        the CAN Interface for all underlying CAN Dirvers.*/

    ///////////////////////////////////////edited nadaW///////////////////////////////////////
    uint8 CanIfInitCfgSet[32]; //

    /* Maximum total size of all Tx buffers. This parameter is needed only in
        case of post-build loadable implementation using static memory
        allocation. */
    uint64 CanIfMaxBufferSize;  //

    /* AUTOSAR 4.3 uint32 CanIfNumberOfCanRxPduIds; Maximum number of Pdus.
        This parameter is needed only in case of post-build loadable implementation
        using static memory allocation.*/
    uint64 CanIfMaxRxPduCfg; //

    /* AUTOSAR 4.3 uint32 CanIfMaxTxPduCfg;
        Maximum number of Pdus. This parameter is needed only in case of
        post-build loadable implementation using static memory allocation.*/
    uint64 CanIfMaxTxPduCfg;  //

      /** This container contains parameters related to each HTH */
    CanIfInitHohCfg* CanIfHohConfigPtr;  // Conflict between standerd and AVECORE Code

      /* Rx PDU's list */
    CanIfRxPduCfg*  CanIfRxPduConfigPtr;

    CanIfTxPduCfg* CanIfTxPduConfigPtr;


}CanIfInitCfg;



typedef struct 
{
	/* Reference to the Init Hoh Configuration */
	CanIfInitHohCfg* CanIfCtrlDrvInitHohConfigRef;

	/* CAN Interface Driver Reference. This reference can be used to get any information (Ex. Driver Name,
		Vendor ID) from the CAN driver. The CAN Driver name can be derived from the 
		ShortName of the CAN driver module. */
	CanGeneral* CanIfCtrlDrvNameRef;

}CanIfCtrlDrvCfg;

///* Can Transevier  */
//typedef struct
//{
//	/* data */
//	CanIfTrcvCfg* CanIfTrcvCfgPtr;
//}CanIfTrcvDrvCfg;


typedef struct {
	/** Reference to the list of channel init configurations. */
	CanIfCtrlCfg* ControllerConfig;

	/** This container contains the init parameters of the CAN Interface. */
	CanIfInitCfg* InitConfig;

	// /** ArcCore: Contains the mapping from CanIf-specific Channels to Can Controllers */
	// const CanControllerIdType* Arc_ChannelToControllerMap;

	// const uint8* Arc_ChannelDefaultConfIndex;
} CanIf_ConfigType;

//
//typedef struct
//{
//	/* This parameter abstracts from the CAN Transceiver Driver specific
//		parameter Transceiver. Each transceiver of all connected CAN
//		Transceiver Driver modules shall be assigned to one specific
//		TransceiverId of the CanIf */
//		uint8 CanIfTrcvId;
//
//	/* This parameter defines if a respective transceiver of the referenced
//	    CAN Transceiver Driver modules is queriable for wake up events */
//		boolean CanIfTrcvWakeupSupport;
//	/* This parameter references to the logical handle of the underlying CAN
//		transceiver from the CAN transceiver driver module to be served by the
//		CAN Interface module */
//		CanTrcvChannel* CanIfTrcvCanTrcvRef
//
//}CanIfTrcvCfg;




 
 /* Transmission Containers */








//
//typedef enum
//{
//	CAN_SM,
//	CDD
//}UserCheckTrcvFlag;

///////////////////////////NadaW/////////////////INQUIRY!!!////////////////////////////////

// typedef struct {

// 	#ifdef (CANIF_PUBLIC_PN_SUPPORT)

// 	/* Name of the transceiver wake up notification service to target upper layers*/
// 	void  *User_CheckTrcvWakeFlagIndication (void);
// 	//P2FUNC(void,CANIF_APPL_CODE,CanIfCheckTrcvWakeFlagIndication)(void);
	
// 	/*Name of the transceiver wake up notification service to target upper layers*/
// 	CanIfConfirmPnAvailabilityName
//     //P2FUNC(void,CANIF_APPL_CODE,CanIfConfirmPnAvailabilityName)(void);

//     UserCheckTrcvWakeFlag CanIfDispatchUserCheckTrcvWakeFlagIndicationUL;

//     UserCheckTrcvFlag CanIfDispatchUserClearTrcvWufFlagIndicationUL;

//     /*Name of the clear transceiver wake up notification service to target upper layers*/
// 	//CanIfDispatchUserClearTrcvWufFlagIndicationUL equals CAN_SM the name of <User_ClearTrcvWufFlagIndication> is fixed. 
// 	//If it equals CDD, the name is selectable
// 	CanIfDispatchUserClearTrcvWufFlagIndicationName
// 	//P2FUNC(void,CANIF_APPL_CODE,CanIfClearTrcvWakeFlagIndication)(void);

// 	#endif

//     Notification to the upper layer "mostly Can_Sm" in case the
//      * bus is off 

//     P2FUNC(void,CANIF_APPL_CODE,CanIfBusOffNotification)
//     (VAR(uint8,AUTOMATIC) ControllerId);

//     /*Notification to the upper layer "mostly Can_Sm" indicating the
//      * change of the mode of the CAN controller */

//     P2FUNC(void,CANIF_APPL_CODE,CanIfCtrlModeIndication)
//     (VAR(uint8,AUTOMATIC) CrtlId,
//     VAR(Can_ControllerStateType,AUTOMATIC) CtrlMode);

//     /*Notification to the upper layer "mostly Can_Sm" indicating the
//      * change of the mode of the CAN Transceiver */

//     P2FUNC(void,CANIF_APPL_CODE,CanIfTrcvModeIndication)(void);

//     /** ArcCore ext. */
//     /*AUTOSAR 4.3 void (*CanIfErrorNotificaton)(uint8 xx ,Can_Arc_ErrorType xxx);*/
//     P2FUNC(void,CANIF_APPL_CODE,CanIfErrorNotificaton)
//     (
//     	VAR(uint8,AUTOMATIC) xx,
//     	VAR(Can_Arc_ErrorType,AUTOMATIC) xxx
//     );

// #if(CANIF_WAKEUP_CHECK_VALIDATION_API == STD_ON)

//     P2FUNC(void,CANIF_APPL_CODE,CanIfValidateWakeupEventNotification)(void);

// #endif

// } CanIfDispatchCfg;



typedef struct 
{
	//to be defined and implemented in CanIf_Cfg.c 
	//TRUE: Minimum buffer element length is fixed to 8 Bytes. 
	//FALSE (default value) :Buffer element length depends on the size of the referencing PDUs 
	const bool CanIfFixedBuffer;  //

	const bool CanIfPrivateDataLengthCheck; //default value true  //

	/*
	dependency: BasicCAN reception must be enabled by referenced
	parameter CAN_HANDLE_TYPE of the CAN Driver module via
	CANIF_HRH_HANDLETYPE_REF for at least one HRH.
	*/

	//#if (CanIfHrhCfg->CanIfHrhType == CAN_HANDLE_TYPE_BASIC)

	const SoftwareFilterType CanIfPrivateSoftwareFilterType;

	//#endif

	//TRUE: TTCAN is supported. FALSE: TTCAN is not supported
	const bool CanIfSupportTTCAN; //only normal CAN communication is possible??


	/*not supported*/

	#if (CanIfSupportTTCAN == TRUE)
	//CanIfTTGeneral
	#endif
	
}CanIfPrivateCfg;


typedef struct 
{
	//Switches the development error detection and notification on or off.
	//default value: false
	bool CanIfDevErrorDetect;

	//Enable support for dynamic ID handling using L-SDU MetaData.
	bool CanIfMetaDataSupport;

	/*
	Configuration parameter to enable/disable dummy API for upper layer
	modules which allows to request the cancellation of an I-PDU.
	*/
	bool CanIfPublicCancelTransmitSupport;

	/*
	Defines header files for callback functions which shall be included in
	case of CDDs. Range of characters is 1.. 32.
	*/
	#if ( CanIfRxPduUserRxIndicationUL == CDD)
	uint8 CanIfPublicCddHeaderFile[32];
	#endif

	/*
	This parameter is used to configure the Can_HwHandleType. The
	Can_HwHandleType represents the hardware object handles of a CAN
	hardware unit. For CAN hardware units with more than 255 HW objects
	the extended range shall be used (UINT16).
	*/

	//////////////NadaW///////////////////// inquiry!! /////////////////
	Can_HwHandleType CanIfPublicHandleTypeEnum; //Can_HwHandleType is defined in Can_generalTypes.h and should be uint16 or uint8 but it is only uint8 there????

	/*
	Selects support of Pretended Network features in CanIf. 
	True: Enabled False: Disabled
	*/
	bool CanIfPublicIcomSupport;

	/*
	Selects support for multiple CAN Drivers.
	True: Enabled False: Disabled
	*/
	bool CanIfPublicMultipleDrvSupport;

	/*
	Selects support of Partial Network features in CanIf.
	True: Enabled False: Disabled
	*/
	bool CanIfPublicPnSupport;

	/*
	Enables / Disables the API CanIf_ReadRxPduData() for reading received L-SDU data.
	True: Enabled False: Disabled
	*/
	bool CanIfPublicReadRxPduDataApi;

	/*
	Enables and disables the API for reading the notification status of receive L-PDUs.
	True: Enabled False: Disabled
	*/
	bool CanIfPublicReadRxPduNotifyStatusApi;

	/*
	Enables and disables the API for reading the notification status of transmit L-PDUs.
	True: Enabled False: Disabled
	*/
	bool CanIfPublicReadTxPduNotifyStatusApi;

	/*
	Enables and disables the API for reconfiguration of the CAN Identifier for each Transmit L-PDU.
	True: Enabled False: Disabled
	*/
	bool CanIfPublicSetDynamicTxIdApi;

	/*
	Enables and disables the buffering of transmit L-PDUs (rejected by the CanDrv) within the CAN Interface module
 	True: Enabled False: Disabled
	*/
	bool CanIfPublicTxBuffering;

	/*
	Configuration parameter to enable/disable the API to poll for Tx Confirmation state.
 	True: Enabled False: Disabled
	*/
	bool CanIfPublicTxConfirmPollingSupport;

	/*
	Selects support for wake up validation
	True: Enabled False: Disabled
	*/
	bool CanIfPublicWakeupCheckValidSupport;


	//////////////////////NadaW///////////////////INQUIRY!!///////////////////////////////////////////
	/*
	If enabled, only NM messages shall validate a detected wake-up event
	in CanIf. If disabled, all received messages corresponding to a
	configured Rx PDU shall validate such a wake-up event. This
	parameter depends on CanIfPublicWakeupCheckValidSupport and
	shall only be configurable, if it is enabled.
	True: Enabled False: Disabled
	*/

	// #if (CanIfPublicWakeupCheckValidSupport == STD_ON) //CanIfPublicWakeupCheckValidSupport not defined yet
	// bool CanIfPublicWakeupCheckValidByNM;
	// #endif

	/*Configuration parameter to enable/disable the CanIf_SetBaudrate API
	to change the baud rate of a CAN Controller. If this parameter is set to
	true the CanIf_SetBaudrate API shall be supported. Otherwise the API
	is not supported.
	*/
	bool CanIfSetBaudrateApi;

	/*
	Enables the CanIf_TriggerTransmit API at Pre-Compile-Time.
	Therefore, this parameter defines if there shall be support for trigger
	transmit transmissions. 
	TRUE: Enabled FALSE: Disabled
	*/
	bool CanIfTriggerTransmitSupport;

	/*
	Determines wether TxOffLineActive feature (see SWS_CANIF_00072)
	is supported by CanIf. True: Enabled False: Disabled
	*/
	bool CanIfTxOfflineActiveSupport;

	/*
	Enables and disables the API for reading the version information about
	the CAN Interface.
	True: Enabled False: Disabled
	*/
	bool CanIfVersionInfoApi;

	/*
	Enables the CanIf_CheckWakeup API at Pre-Compile-Time.
	Therefore, this parameter defines if there shall be support for wake-up.
	TRUE: Enabled FALSE: Disabled
	*/
	bool CanIfWakeupSupport;

}CanIfPublicCfg;


/*
The PduMode of a channel defines its transmit or receive activity.
Communication direction (transmission and/or reception) of the channel can
be controlled separately or together by upper layers.
*/
typedef enum 
{
	//Transmit and receive path of the corresponding channel are disabled => no communicationmode
	CANIF_OFFLINE, 

	//Transmit path of the corresponding channel is disabled. The receive path is enabled.
	CANIF_TX_OFFLINE,

	//Transmit path of the corresponding channel is in offline active mode
	//The receive path is disabled. This mode requires CanIfTxOfflineActiveSupport = TRUE.
	CANIF_TX_OFFLINE_ACTIVE,

	//Transmit and receive path of the corresponding channel are enabled => full operation mode
	CANIF_ONLINE
	
}CanIf_PduModeType;


/*
Return value of CAN L-PDU notification status.
*/
typedef enum {
	/** No transmit or receive event occurred for
	 *  the requested L-PDU. */
	CANIF_NO_NOTIFICATION = 0,	
	/** The requested Rx/Tx CAN L-PDU was
	 *  successfully transmitted or received. */
	CANIF_TX_RX_NOTIFICATION
	
} CanIf_NotifStatusType;


#endif /* CANIF_TYPES_H_ */
