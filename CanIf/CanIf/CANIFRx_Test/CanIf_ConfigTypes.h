
/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/

/** @addtogroup CanIf CAN Interface
 *  @{ */

/** @file CanIf_ConfigTypes.h
 *  Definitions of configuration parameters for CAN Interface.
 */

#ifndef CANIF_CONFIGTYPES_H_
#define CANIF_CONFIGTYPES_H_


/** Software filtering type */
typedef enum {
	CANIF_SOFTFILTER_TYPE_BINARY = 0,  /**< Not supported */
	CANIF_SOFTFILTER_TYPE_INDEX,       /**< Not supported */
	CANIF_SOFTFILTER_TYPE_LINEAR,      /**< Not supported */
	CANIF_SOFTFILTER_TYPE_TABLE,       /**< Not supported */
	CANIF_SOFTFILTER_TYPE_MASK,        /**< CanIfCanRxPduCanIdMask in RxPduConfig is used for filtering */
} CanIf_SoftwareFilterTypeType;

/** Type of the upper layer interfacing this module */
typedef enum {
	CANIF_USER_TYPE_CAN_NM,
	CANIF_USER_TYPE_CAN_TP,
	CANIF_USER_TYPE_CAN_PDUR,
	CANIF_USER_TYPE_J1939TP,
	CANIF_USER_TYPE_CAN_SPECIAL
} CanIf_UserTypeType;

/** Notification function for CANIF_USER_TYPE_CAN_SPECIAL */
typedef void (*CanIf_FuncTypeCanSpecial)(uint8 channel, uint32 pduId, const uint8 *sduPtr, uint8 dlc, Can_IdType canId);

/** Defines if PDU Can id can be changed at runtime. */
typedef enum {
  CANIF_PDU_TYPE_STATIC = 0,
  CANIF_PDU_TYPE_DYNAMIC       /**< Not supported */
} CanIf_PduTypeType;

/** PDU Can id type */
typedef enum {
  CANIF_CAN_ID_TYPE_29 = 0,
  CANIF_CAN_ID_TYPE_11
} CanIf_CanIdTypeType;

/*------------------------------------------------------------------- */
/*
 * CanIfHrhRangeConfig container
 */

/** Parameters for configuring Can id ranges. Not supported. */
typedef struct {
	/** Lower CAN Identifier of a receive CAN L-PDU for identifier range
	 *  definition, in which all CAN Ids shall pass the software filtering. Range: 11
     *  Bit for Standard CAN Identifier 29 Bit for Extended CAN Identifer */
	/*AUTOSAR 4.3 uint32 CanIfRxPduLowerCanId; */
	VAR(uint32,AUTOMATIC) CanIfRxPduLowerCanId;

	/** Upper CAN Identifier of a receive CAN L-PDU for identifier range
	 *  definition, in which all CAN Ids shall pass the software filtering. Range: 11
	 *  Bit for Standard CAN Identifier 29 Bit for Extended CAN Identifer */
	/* AUTOSAR 4.3 uint32 CanIfRxPduUpperCanId; */
	VAR(uint32, AUTOMATIC) CanIfRxPduUpperCanId;
} CanIf_HrhRangeConfigType;






/*------------------------------------------------------------------- */
/*
 * CanIfInitHrhConfig container
 */
/** Definition of Hardware Receive Handle */
typedef struct {
	/** Defines the HRH type i.e, whether its a BasicCan or FullCan. If BasicCan is
	 *  configured, software filtering is enabled. */
	VAR(Can_Arc_HohType,AUTOMATIC) CanIfHrhType;

	/** Selects the hardware receive objects by using the HRH range/list from
	 *  CAN Driver configuration to define, for which HRH a software filtering has
	 *  to be performed at during receive processing. True: Software filtering is
	 *  enabled False: Software filtering is disabled */
	VAR(boolean,AUTOMATIC) CanIfSoftwareFilterHrh;

	/** Reference to controller Id to which the HRH belongs to. A controller can
	 *  contain one or more HRHs. */
	VAR(Can_Arc_HRHType,AUTOMATIC) CanIfCanControllerHrhIdRef;



	/** Defines the parameters required for configuraing multiple
	 *  CANID ranges for a given same HRH. */
	P2CONST(CanIf_HrhRangeConfigType,AUTOMATIC,TYPEDEF) CanIfHrhRangeConfig;

  /** End Of List. Set to TRUE if this is the last object in the list. */

	VAR(boolean,AUTOMATIC) CanIf_Arc_EOL;
} CanIf_HrhConfigType;

/*------------------------------------------------------------------- */
/*
 * CanIfInitHthConfig container
 */
/** Definition of Hardware Transmit Handle */
typedef struct {
  /** Defines the HTH type i.e, whether its a BasicCan or FullCan. */
	VAR(Can_Arc_HohType,AUTOMATIC) CanIfHthType;


  /** The parameter refers to a particular HTH object in the CAN Driver Module
   *  configuration. The HTH id is unique in a given CAN Driver. The HTH Ids
   *  are defined in the CAN Driver Module and hence it is derived from CAN
   *  Driver Configuration. */
	VAR(Can_Arc_HTHType,AUTOMATIC) CanIfHthIdSymRef;

  /** End Of List. Set to TRUE if this is the last object in the list. */
	VAR(boolean,AUTOMATIC) CanIf_Arc_EOL_Mod;
} CanIf_HthConfigType;


/*------------------------------------------------------------------- */
/*
 * CanIfTxPduConfig container
 */

typedef P2FUNC(void,CANIF_APPL_CODE,CanIfUserTxConfirmation_t)
		(
				VAR(uint32,AUTOMATIC)
				);

/*Post Build Configuration*/

typedef struct{
	/*The ID of the L-PDU to be buffered*/
	VAR(uint32,AUTOMATIC) TxPduId;
	/*The CAN ID of the L-PDU to be buffered*/
	VAR(uint32,AUTOMATIC) CanIfPduCanId;
	/*The data to be buffered */
	VAR(uint8,AUTOMATIC) Data[8];
	//P2VAR(uint8,CANIF_VAR,CANIF_APPL_DATA) PtrToData;

	VAR(uint8,AUTOMATIC) dataLength;
}CanIf_TxBuffPduInfo_t;

typedef struct{
	/*The buffer info "the data and the PDU" to be buffered*/
	P2VAR(CanIf_TxBuffPduInfo_t,CANIF_VAR,CANIF_APPL_DATA) BufferInfoPtr;
	/*The HTH index "in the array of HTHs" which this buffer is mapped to*/
	VAR(uint8,AUTOMATIC) HthIndex;
	/*Size of the buffer*/
	VAR(uint8,AUTOMATIC) BufferSize;
}CanIf_TxBufferCfg_t;

/** Definition of Tx PDU (Protocol Data Unit). */
typedef struct {
	/** ECU wide unique, symbolic handle for transmit CAN L-PDU. The
	 *  CanIfCanTxPduId is configurable at pre-compile and post-built time.
	 *  Range: 0..max. number of CantTxPduIds  	PduIdType 	CanTxPduId; */
	VAR(uint32,AUTOMATIC) CanIfTxPduId;

	/** CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-
	 *  PDU transmission. Range: 11 Bit For Standard CAN Identifier ... 29 Bit For
	 *  Extended CAN identifier */
	VAR(uint32,AUTOMATIC) CanIfCanTxPduIdCanId;

	/** Data length code (in bytes) of transmit CAN L-PDUs used by the CAN
	 *  Driver for CAN L-PDU transmission. The data area size of a CAN L-Pdu
	 *  can have a range from 0 to 8 bytes. */
	VAR(uint8,AUTOMATIC) CanIfCanTxPduIdDlc;
#if(CANIF_ARC_RUNTIME_PDU_CONFIGURATION == STD_ON)
	/*Mask to make parts of the dynamic ID static*/
	VAR(uint32,AUTOMATIC) CanIfTxPduCanIdMask;
#endif

	/** Defines the type of each transmit CAN L-PDU.
	 *  DYNAMIC  CAN ID is defined at runtime.
	 *  STATIC  CAN ID is defined at compile-time. */
	VAR(CanIf_PduTypeType,AUTOMATIC) CanIfCanTxPduType;

#if ( CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON )
	/** Enables and disables transmit confirmation for each transmit CAN L-PDU
	 *  for reading its notification status. True: Enabled False: Disabled */
	VAR(boolean,AUTOMATIC) CanIfReadTxPduNotifyStatus;
#endif

	/** CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-
	 *  PDU transmission.
	 *  EXTENDED_CAN  The CANID is of type Extended (29 bits).
	 *  STANDARD_CAN  The CANID is of type Standard (11 bits). */
	VAR(CanIf_CanIdTypeType,AUTOMATIC) CanIfTxPduIdCanIdType;

	/** Name of target confirmation services to target upper layers (PduR, CanNm
	 *  and CanTp. If parameter is not configured then no call-out function is
	 *  provided by the upper layer for this Tx L-PDU. */
	VAR(uint8,AUTOMATIC) CanIfUserTxIndex;

	/*The buffer handle that the L-PDU maps to*/
	P2VAR(CanIf_TxBufferCfg_t,CANIF_VAR,CANIF_APPL_DATA) CanIfTxBufferRef;
	/** Reference to the "global" Pdu structure to allow harmonization of handle
	 *  IDs in the COM-Stack. */
	P2VAR(void,CANIF_VAR,CANIF_APPL_DATA) PduIdRef;
} CanIf_TxPduConfigType;

/*------------------------------------------------------------------- */
/*
 * CanIfRxPduConfig container
 */


typedef P2FUNC(void,CANIF_APPL_CODE,CanIfUserRxIndication_t)(
		VAR(uint8,AUTOMATIC) channel,
		VAR(uint32,AUTOMATIC) pduId,
		P2CONST(uint8,TYPEDEF,CANIF_APPL_CONST) sduPtr,
		VAR(uint8,AUTOMATIC) dlc,
		VAR(Can_IdType,AUTOMATIC) canId
		);


typedef struct {
	VAR(CanIf_UserTypeType,AUTOMATIC) CanIfRxUserType;
	VAR(CanIfUserRxIndication_t,AUTOMATIC) CanIfUserRxIndication;
}CanIF_RxPDUCbkConfig;

typedef struct {
	VAR(CanIf_UserTypeType,AUTOMATIC) CanIfTxUserType;
	VAR(CanIfUserTxConfirmation_t,AUTOMATIC) CanIfUserTxIndication;
}CanIF_TxPDUCbkConfig;  //MentorTx



/** Definition of Rx PDU (Protocol Data Unit). */
typedef struct {
  /** ECU wide unique, symbolic handle for receive CAN L-PDU. The
   *  CanRxPduId is configurable at pre-compile and post-built time. It shall fulfill
   *  ANSI/AUTOSAR definitions for constant defines. Range: 0..max. number
   *  of defined CanRxPduIds */
	VAR(uint32,AUTOMATIC) CanIfCanRxPduId;

  /** CAN Identifier of Receive CAN L-PDUs used by the CAN Interface. Exa:
   *  Software Filtering. Range: 11 Bit For Standard CAN Identifier ... 29 Bit For
   *  Extended CAN identifier */
	VAR(uint32,AUTOMATIC) CanIfCanRxPduCanId;

  /** Data Length code of received CAN L-PDUs used by the CAN Interface.
   *  Exa: DLC check. The data area size of a CAN L-PDU can have a range
   *  from 0 to 8 bytes.*/
	VAR(uint8,AUTOMATIC) CanIfCanRxPduDlc;

#if ( CANIF_CANPDUID_READDATA_API == STD_ON ) /**/
  /** Enables and disables the Rx buffering for reading of received L-PDU data.
   *  True: Enabled False: Disabled */
	VAR(boolean,AUTOMATIC) CanIfReadRxPduData;
#endif

#if ( CANIF_READRXPDU_NOTIF_STATUS_API == STD_ON ) /**/
  /** CanIfReadRxPduNotifyStatus {CANIF_READRXPDU_NOTIFY_STATUS}
   *  Enables and disables receive indication for each receive CAN L-PDU for
   *  reading its' notification status. True: Enabled False: Disabled */
	VAR(boolean,AUTOMATIC) CanIfReadRxPduNotifyStatus;
#endif

  /** CAN Identifier of receive CAN L-PDUs used by the CAN Driver for CAN L-
   *  PDU transmission.
   *  EXTENDED_CAN  The CANID is of type Extended (29 bits)
   *  STANDARD_CAN  The CANID is of type Standard (11 bits) */
	VAR(CanIf_CanIdTypeType,AUTOMATIC) CanIfRxPduIdCanIdType;

  /** Name of target indication services to target upper layers (PduRouter,
   *  CanNm, CanTp and ComplexDeviceDrivers). If parameter is 0 no call-out
   *  function is configured. */
/*	void *CanIfUserRxIndication; */
	/* AUTOSAR 4.3 void (*CanIfUserRxIndication)(uint8 channel, PduIdType pduId, const uint8 *sduPtr, uint8 dlc, Can_IdType canId);*/
	/*VAR(CanIfUserRxIndication_t,AUTOMATIC) CanIfUserRxIndication;*/
	VAR(uint8,AUTOMATIC) CanIfRxPduCallBackInd;
  /** The HRH to which Rx L-PDU belongs to, is referred through this
   *  parameter. */
	P2CONST(CanIf_HrhConfigType,AUTOMATIC,TYPEDEF) CanIfCanRxPduHrhRef;

  /** Reference to the "global" Pdu structure to allow harmonization of handle
   *  IDs in the COM-Stack. */
	P2VAR(void,CANIF_VAR,CANIF_APPL_DATA) PduIdRef_Mod;

  /** Defines the type of software filtering that should be used
   *  for this receive object. */
	/* AUTOSAR 4.3 CanIf_SoftwareFilterTypeType CanIfSoftwareFilterType;*/
	/*VAR(CanIf_SoftwareFilterTypeType,AUTOMATIC) CanIfSoftwareFilterType; removed this parameter as its precompile and generic for all PDUs */

  /** Acceptance filters, 1 - care, 0 - don't care.
   *  Is enabled by the CanIfSoftwareFilterMask in CanIf_HrhConfigType
   *  ArcCore exension */
	VAR(uint32,AUTOMATIC) CanIfCanRxPduCanIdMask;

} CanIf_RxPduConfigType;

/*------------------------------------------------------------------- */



/*
 * CanIfControllerConfig container
 */
/** Not supported. */
typedef enum {
	CANIF_WAKEUP_SUPPORT_CONTROLLER,
	CANIF_WAKEUP_SUPPORT_NO_WAKEUP,
	CANIF_WAKEUP_SUPPORT_TRANSCEIVER
} CanIf_WakeupSupportType;


/** Container used to create channel init configurations.
 *  @see CanIf_Arc_ConfigurationIndexType
 *  @see CanIf_Arc_ChannelIdType */
typedef struct {
    /** Not used */
	/*AUTOSAR 4.3 CanIf_WakeupSupportType WakeupSupport;*/
	VAR(CanIf_WakeupSupportType,AUTOMATIC) WakeupSupport;

	/** CanIf-specific id of the controller */
	/*AUTOSAR 4.3 CanIf_Arc_ChannelIdType CanIfControllerIdRef;*/
	VAR(CanIf_Arc_ChannelIdType,AUTOMATIC) CanIfControllerIdRef;

	/* wake up not supported by arc core TEAM*/

	/** Not used */
	/*AUTOSAR 4.3 const char CanIfDriverNameRef[8];*/
	//CONST(char,AUTOMATIC) CanIfDriverNameRef[8];

	/** Reference to */
	/* AUTOSAR 4.3 const Can_ControllerConfigType *CanIfInitControllerRef;*/
	//P2CONST(Can_ControllerConfigType,AUTOMATIC,TYPEDEF) CanIfInitControllerRef;
} CanIf_ControllerConfigType;

/*------------------------------------------------------------------- */
/*
 * CanIfTransceiverDrvConfig container
 */

typedef struct {
	/* AUTOSAR 4.3 boolean	TrcvWakeupNotification;*/
	VAR(boolean,AUTOMATIC) TrcvWakeupNotification;
	/*AUTOSAR 4.3 uint8	TrcvIdRef;*/
	VAR(uint8,AUTOMATIC) TrcvIdRef;
} CanIf_TransceiverDrvConfigType;


typedef struct {
	VAR(uint8,AUTOMATIC) todo;
} CanIf_TransceiverConfigType;


/*Link Time Configurations*/

typedef struct {

#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)

	/* Name of the transceiver wake up notification service to target upper layers*/

	P2FUNC(void,CANIF_APPL_CODE,CanIfCheckTrcvWakeFlagIndication)(void);

	/*Name of the clear transceiver wake up notification service to target upper layers*/

	P2FUNC(void,CANIF_APPL_CODE,CanIfClearTrcvWakeFlagIndication)(void);

	/*Name of the transceiver wake up notification service to target upper layers*/

    P2FUNC(void,CANIF_APPL_CODE,CanIfConfirmPnAvailabilityName)(void);
#endif

    /*Notification to the upper layer "mostly Can_Sm" in case the
     * bus is off */

    P2FUNC(void,CANIF_APPL_CODE,CanIfBusOffNotification)
    (VAR(uint8,AUTOMATIC) ControllerId);

    /*Notification to the upper layer "mostly Can_Sm" indicating the
     * change of the mode of the CAN controller */

    P2FUNC(void,CANIF_APPL_CODE,CanIfCtrlModeIndication)
    (VAR(uint8,AUTOMATIC) CrtlId,
    VAR(Can_ControllerStateType,AUTOMATIC) CtrlMode);

    /*Notification to the upper layer "mostly Can_Sm" indicating the
     * change of the mode of the CAN Transceiver */

    P2FUNC(void,CANIF_APPL_CODE,CanIfTrcvModeIndication)(void);

    /** ArcCore ext. */
    /*AUTOSAR 4.3 void (*CanIfErrorNotificaton)(uint8 xx ,Can_Arc_ErrorType xxx);*/
    P2FUNC(void,CANIF_APPL_CODE,CanIfErrorNotificaton)
    (
    	VAR(uint8,AUTOMATIC) xx,
    	VAR(Can_Arc_ErrorType,AUTOMATIC) xxx
    );

#if(CANIF_WAKEUP_CHECK_VALIDATION_API == STD_ON)

    P2FUNC(void,CANIF_APPL_CODE,CanIfValidateWakeupEventNotification)(void);

#endif

} CanIf_DispatchConfigType;

/** This container contains the references to the configuration setup of each
 *  underlying CAN driver. */
typedef struct {
	/** Not used. */
	/* AUTOSAR 4.3 uint32 CanIfConfigSet;*/
	VAR(uint32,AUTOMATIC) CanIfConfigSet;

	/** Size of Rx PDU list. */
	/* AUTOSAR 4.3 uint32 CanIfNumberOfCanRxPduIds;*/
	VAR(uint32,AUTOMATIC) CanIfNumberOfCanRxPduIds;
	/** Size of Tx PDU list. */
	/* AUTOSAR 4.3 uint32 CanIfNumberOfCanTXPduIds;*/
	VAR(uint32,AUTOMATIC) CanIfNumberOfCanTXPduIds;
	/** Not used */
	/*AUTOSAR 4.3 uint32 CanIfNumberOfDynamicCanTXPduIds;*/
	VAR(uint32,AUTOMATIC) CanIfNumberOfDynamicCanTXPduIds;

	/*
	 Containers
	*/

	  /** This container contains configuration parameters for each hardware receive object. */
		P2CONST(CanIf_Arc_ChannelIdType,AUTOMATIC,TYPEDEF) CanIfHrhCanControllerIdArr;

	  /** This container contains parameters related to each HTH */
//		P2CONST(CanIf_HthConfigType,AUTOMATIC,TYPEDEF) CanIfHthConfig;

	/*This container contains the controller IDs for each HTH*/
		P2CONST(CanIf_Arc_ChannelIdType,AUTOMATIC,TYPEDEF) CanIfHthCanControllerIdArr;

  /* Rx PDU's list */
	P2CONST(CanIf_RxPduConfigType,AUTOMATIC,TYPEDEF) CanIfRxPduConfigPtr;

  /* Tx PDU's list */
#if (CANIF_ARC_RUNTIME_PDU_CONFIGURATION == STD_OFF)
	/* AUTOSAR 4.3 const CanIf_TxPduConfigType *CanIfTxPduConfigPtr;*/
	P2CONST(CanIf_TxPduConfigType,AUTOMATIC,TYPEDEF) CanIfTxPduConfigPtr;
#else
	/* AUTOSAR 4.3 CanIf_TxPduConfigType *CanIfTxPduConfigPtr;*/
	P2VAR(CanIf_TxPduConfigType,CANIF_VAR,CANIF_APPL_DATA) CanIfTxPduConfigPtr;
#endif


	/*Buffer NOt Supported
	 * CanIfMaxBufferSize
	 * CanIfBufferCfg -> Pointer to Buffer Confg.
	 * */

} CanIf_InitConfigType;

/** Top level config container. */
typedef struct {
	/** Reference to the list of channel init configurations. */
	P2CONST(CanIf_ControllerConfigType,AUTOMATIC,TYPEDEF) ControllerConfig;

	/** This container contains the init parameters of the CAN Interface. */
	P2CONST(CanIf_InitConfigType,AUTOMATIC,TYPEDEF) InitConfig;

	/** Not used */
	P2CONST(CanIf_TransceiverConfigType,AUTOMATIC,TYPEDEF) TransceiverConfig;

	/** ArcCore: Contains the mapping from CanIf-specific Channels to Can Controllers */
	P2CONST(CanControllerIdType,AUTOMATIC,TYPEDEF) Arc_ChannelToControllerMap;

	P2CONST(uint8,AUTOMATIC,TYPEDEF) Arc_ChannelDefaultConfIndex;
} CanIf_ConfigType;



#endif /* CANIF_CONFIGTYPES_H_ */
/** @} */
