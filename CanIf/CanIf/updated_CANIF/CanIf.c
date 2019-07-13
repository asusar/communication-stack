
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
#if defined(USE_DET)
#include "Det.h"
#endif
#include "CanIf.h"
#include "E:\merged_partition_content\MCT\GradProject\Final Phase testing and integration\Integration-20190619T083804Z-001\Integration\Can_Driver/Can.h"
#include "CanIf_Cbk.h"

/* ______________________________________________________RxIndication________________________________________________________*/
#include <string.h>
#include "debug.h"
#include "CanIf_Cfg.h"
#include "PduR.h"
#include "CanIf_Lcfg.h"
#include "CanIf_Sec_cfg.h"

#if defined(USE_CANTP)
#include "CanTp_Cbk.h"
#endif
#if defined(USE_J1939TP)
#include "J1939Tp_Cbk.h"
#endif
#if defined(USE_CANNM)
#include "CanNm.h"
#endif
#if 0 /* TODO: Include upper layer functions, See CANIF208 and CANIF233 */
#include "PduR_CanIf.h"
#include "CanNm.h"
#include "CanTp.h"
#include "PduR_Cbk.h"
#include "CanNm_Cbk.h"
#include "CanTp_Cbk.h"
#endif

/*
 * outer configuration call back array () Mentor 4th Edit :
 * */

/* ______________________________________________________RxIndication________________________________________________________*/
#define CANIF_SOFTWARE_FILTER_TYPE (CANIF_SOFTFILTER_TYPE_MASK)
extern CanIF_RxPDUCbkConfig CanIF_RxPDUCbkConfig_a[1];

//extern CanIF_TxPDUCbkConfig CanIF_TxPDUCbkConfig_a[1];

//#define USE_PDUR 1

#if  ( CANIF_DEV_ERROR_DETECT == STD_ON )
#if CANIF_UNIT_TESTING == STD_ON
#define UNIT_TEST_INDICATOR(_err)                   \
        if(CANIF_E_PARAM_LPDU == _err)  {   \
            testNumber = 2;                 \
        }                                   \
        else if(CANIF_E_UNINIT == _err) {   \
            testNumber = 16;                \
        }
#else
#define UNIT_TEST_INDICATOR(_err)
#endif
#endif

/* Global configure */
#if  ( CANIF_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
            DET_REPORTERROR(MODULE_ID_CANIF, 0, _api, _err); \
            return E_NOT_OK; \
        }

#define VALIDATE_NO_RV(_exp,_api,_err ) \
        if( !(_exp) ) { \
            DET_REPORTERROR(MODULE_ID_CANIF, 0, _api, _err); \
            UNIT_TEST_INDICATOR(_err)       \
            return; \
        } 
#define DET_REPORTERROR(_x,_y,_z,_q) printf("An error occurred in module number %d in function number 0x%x and the error is %d. \n",_x,_z,_q)

#else
#define VALIDATE(_exp,_api,_err )  /*Autosar standard */

#define VALIDATE_NO_RV(_exp,_api,_err ) /*Autosar standard */

#define DET_REPORTERROR(_x,_y,_z,_q) /*Autosar standard */


#endif


#if CANIF_UNIT_TESTING == STD_ON
#define PRINT(_Msg)                     printf(_Msg)
#define PRINT_E_D(_Msg, _api, _err)     printf(_Msg, _api, _err)

extern uint8 testNumber;

#endif

CanIf_TxBuffPduInfo_t BuffPool[CANIF_BUFFER_POOL_SIZE];


static const CanIf_ConfigType *CanIf_ConfigPtr;

#if(CANIF_UNIT_TESTING==STD_ON)
CanIf_InitConfigType CanIF_UnInitConfig = {0,0,0,0,NULL,NULL,NULL};
static const CanIf_ConfigType Config_UnInit = {NULL,NULL,&CanIF_UnInitConfig,NULL,NULL};
#endif


/*Array with the size of amount of all the buffers to indicate how much of the buffer is full*/
uint8 CanIf_Pdu_BufferIndex[NUM_OF_HTHS];



/* Struct of controller private data. */
typedef struct
{
    
Can_ControllerStateType  Controller_Mode;
    CanIf_ChannelGetModeType  PduMode;
} CanIf_ChannelPrivateType;

typedef struct
{
    boolean initRun;
    CanIf_ChannelPrivateType channelData[CANIF_CHANNEL_CNT];
} CanIf_GlobalType;

/*CanControllerIdType ARC_GET_CHANNEL_CONTROLLER(uint8 channel)  SWS_compiler*/
 FUNC(CanControllerIdType,CANIF_CODE) ARC_GET_CHANNEL_CONTROLLER(
		 /* uint8 channel*/
		 VAR(uint8, AUTOMATIC) channel
		 )
{
    return CanIf_ConfigPtr->Arc_ChannelToControllerMap[channel];
}



/*static CanIf_Arc_ChannelIdType CanIf_Arc_FindHrhChannel( Can_Arc_HRHType hrh ) SWS_compiler*/

static FUNC(CanIf_Arc_ChannelIdType,CANIF_CODE) CanIf_Arc_FindHrhChannel( /*Can_Arc_HRHType hrh */
		VAR(Can_Arc_HRHType, AUTOMATIC) hrh
		)
{
		P2CONST(CanIf_HrhConfigType, AUTOMATIC, CANIF_APPL_CONST) hrhConfig;

	    VAR( sint8, AUTOMATIC )hrhConfig_count = 0;

	    VAR( CanIf_Arc_ChannelIdType, AUTOMATIC ) To_Return = (CanIf_Arc_ChannelIdType) -1;
	 /* CanIf_Arc_ChannelIdType To_Return = (CanIf_Arc_ChannelIdType) -1 ;  */
	    VAR( uint8, AUTOMATIC ) check = (uint8)  0;
	 /* uint8 check = (uint8)  0; */

	    hrhConfig = CanIf_ConfigPtr->InitConfig->CanIfHrhCanControllerIdArr;
	    		/*CanIf_ConfigPtr->InitConfig->CanIfHrhConfig*/;

	       /*(MISRA-C:2004 17.4/R) Array indexing shall be the only allowed form of pointer arithmetic */
	        --hrhConfig_count;
	        do
	        {
	            /* M_E hrhConfig++; */
	            /*(MISRA-C:2004 17.4/R) Array indexing shall be the only allowed form of pointer arithmetic */
	            ++hrhConfig_count;

	             if ((CanIf_hrhConfigTypeInstance[hrhConfig_count].CanIfCanControllerHrhIdRef) == hrh){
	               /*M_E return hrhConfig->CanIfCanControllerHrhIdRef; */
	               /* (MISRA-C:2004 14.7/R) A function shall have a single point of exit at the end of the function*/
	                To_Return= (&hrhConfig[hrhConfig_count])->CanIfCanControllerHrhIdRef;
	                check= (uint8) 1;
	            }
	            /*M_E while(!hrhConfig->CanIf_Arc_EOL); */
	            /* (MISRA-C:2004 12.6/A) The operands of logical operators (&&, || and !) should be effectively Boolean */
	        } while(  (check==(uint8) 0) &&  (!((boolean)((&hrhConfig[hrhConfig_count])->CanIf_Arc_EOL))));

	    if(!check)
	    {
	        DET_REPORTERROR(MODULE_ID_CANIF, 0, CANIF_RXINDICATION_ID, CANIF_E_PARAM_HRH);
	    }

	    /*return (CanIf_Arc_ChannelIdType) -1;*/
	    return To_Return;
}

/* Global config */
CanIf_GlobalType CanIf_Global;

/*void CanIf_Init( const CanIf_ConfigType *ConfigPtr) SWS_compiler_FUNC*/

FUNC(void,CANIF_CODE) CanIf_Init(
		/* const CanIf_ConfigType *ConfigPtr */
		P2CONST(CanIf_ConfigType, AUTOMATIC,CANIF_APPL_CONST) ConfigPtr
		)
{
    VALIDATE_NO_RV(ConfigPtr != 0, CANIF_INIT_ID, CANIF_E_PARAM_POINTER); /* Only PostBuild case supported */

    CanIf_ConfigPtr = ConfigPtr;
    VAR( uint8, AUTOMATIC ) i = (uint8)  0;
 /* uint8 i; */
    for ( i = (uint8)0; i <  CANIF_CHANNEL_CNT; i++)
    {
        CanIf_Global.channelData[i].Controller_Mode = CAN_CS_STOPPED;
        CanIf_Global.channelData[i].PduMode = CANIF_GET_OFFLINE;
        //CanIf_PreInit_InitController(i, CanIf_ConfigPtr->Arc_ChannelDefaultConfIndex[i]);
    }


    CanIf_Global.initRun = (uint8) TRUE;
    /*buffer initialization*/
    i = 0;
    for(i=0;i<NUM_OF_HTHS;i++){
    	CanIf_Pdu_BufferIndex[i] = 0;
    }
    /*init the buffer internal CAN ID*/
    for(i=0;i<CANIF_BUFFER_POOL_SIZE;i++)
    {
    	BuffPool[i].CanIfPduCanId=0x0;
    }
}


#if (CANIF_UNIT_TESTING==STD_ON)
//void CanIf_UnInit (void)
FUNC(void,CANIF_CODE) CanIf_UnInit(void)
{
    CanIf_ConfigPtr = &Config_UnInit;
    uint8 i_UnInit ;
    for ( i_UnInit = (uint8)0; i_UnInit <  CANIF_CHANNEL_CNT; i_UnInit++)
    {
        CanIf_Global.channelData[i_UnInit].Controller_Mode = CAN_CS_UNINIT;
        CanIf_Global.channelData[i_UnInit].PduMode = CANIF_GET_OFFLINE;
    }


    CanIf_Global.initRun = (uint8) FALSE; // N_1M 
}
#endif

/*------------------------------------------------------------------- */
/*
 * Controller :: CanIf_Arc_ChannelIdType (CanIf-specific id to abstract from Can driver/controllers)
 * ConfigurationIndex :: CanIf_Arc_ConfigurationIndexType
 */
//void CanIf_InitController(uint8 Controller, uint8 ConfigurationIndex)
//FUNC(void,CANIF_CODE) CanIf_InitController(/* uint8 Controller, uint8 ConfigurationIndex */
//		VAR(uint8, AUTOMATIC) Controller,
//		VAR(uint8, AUTOMATIC) ConfigurationIndex
//		)
//{
//
//    /* We call this a CanIf channel_CanIf_InitController. Hopefully makes it easier to follow. */
//
//	VAR( CanIf_Arc_ChannelIdType, AUTOMATIC ) channel_CanIf_InitController = (CanIf_Arc_ChannelIdType) Controller;
// /* CanIf_Arc_ChannelIdType channel_CanIf_InitController = (CanIf_Arc_ChannelIdType) Controller; */
//	VAR( CanIf_ControllerModeType, AUTOMATIC ) mode = (CanIf_ControllerModeType) 0;
// /* CanIf_ControllerModeType mode = (CanIf_ControllerModeType) 0; */
//
//    VALIDATE_NO_RV(CanIf_Global.initRun, CANIF_INIT_CONTROLLER_ID, CANIF_E_UNINIT );
//    VALIDATE_NO_RV(channel_CanIf_InitController < CANIF_CHANNEL_CNT, CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER);
//    VALIDATE_NO_RV(ConfigurationIndex < CANIF_CHANNEL_CONFIGURATION_CNT, CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_POINTER);
//
//    if ( CanIf_GetControllerMode(channel_CanIf_InitController, &mode)== E_OK)
//    {
//        if (mode == CAN_CS_STARTED)
//        {
//            CanIf_SetControllerMode(channel_CanIf_InitController, CAN_CS_STOPPED); /* CANIF092 */
//        }
//        else if (mode != CAN_CS_STOPPED)
//        {
//            VALIDATE_NO_RV((uint8)FALSE, CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER_MODE); /* CANIF092 */
//        }
//        /*M_E */
//        /* (MISRA-C:2004 14.10/R) All if ... else if constructs shall be terminated with an else clause   */
//        else
//        {
//
//        }
//    }
//    else
//    {
//        VALIDATE_NO_RV((uint8)FALSE, CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER_MODE);
//    }
//
//    /* CANIF293: ..Subsequently the CAN Interface calls the corresponding */
//    /*             CAN Driver initialization services. */
//
//    /* CANIF066: The CAN Interface has access to the CAN Driver configuration data. All */
//    /* public CAN Driver configuration data are described in [8] Specification of CAN Driver. */
//
//    /* Grab the configuration from the Can Controller */
//    P2CONST(Can_ControllerConfigType, AUTOMATIC, CANIF_APPL_CONST) canConfig;
// /* const Can_ControllerConfigType *canConfig; */
//    CONST(CanControllerIdType,AUTOMATIC) canControllerId = ARC_GET_CHANNEL_CONTROLLER(channel_CanIf_InitController);
//  /*  const CanControllerIdType canControllerId = ARC_GET_CHANNEL_CONTROLLER(channel_CanIf_InitController); */
//
//    /* Validate that the configuration at the index match the right channel */
//    VALIDATE_NO_RV(CanIf_ConfigPtr->ControllerConfig[ConfigurationIndex].CanIfControllerIdRef == channel_CanIf_InitController, CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER);
//
//    canConfig = CanIf_ConfigPtr->ControllerConfig[ConfigurationIndex].CanIfInitControllerRef;
//
//    /* Validate that the CanIfControllerConfig points to configuration for the right Can Controller */
//    VALIDATE_NO_RV(canConfig->CanControllerId == canControllerId, CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER);
//
//    Can_InitController(canControllerId, canConfig);
//
//    /* Set mode to stopped */
//    CanIf_SetControllerMode(channel_CanIf_InitController, CAN_CS_STOPPED);
//}

/*void CanIf_PreInit_InitController(uint8 Controller, uint8 ConfigurationIndex) SWS_compiler*/
//FUNC(void,CANIF_CODE) CanIf_PreInit_InitController(/* uint8 Controller, uint8 ConfigurationIndex */
//		VAR(uint8, AUTOMATIC) Controller,
//		VAR(uint8, AUTOMATIC) ConfigurationIndex
//		)
//{
//    /* We call this a CanIf channel. Hopefully makes it easier to follow. */
//    /* M_E CanIf_Arc_ChannelIdType channel = (CanIf_Arc_ChannelIdType) Controller; */
//    /*  (MISRA-C:2004 5.7/A) No identifier name should be reused ("channel") */
//	VAR(CanIf_Arc_ChannelIdType,AUTOMATIC) channel_CanIf_PreInit_InitController = (CanIf_Arc_ChannelIdType) Controller;
//  /*  CanIf_Arc_ChannelIdType channel_CanIf_PreInit_InitController = (CanIf_Arc_ChannelIdType) Controller; */
//
//    VALIDATE_NO_RV(channel_CanIf_PreInit_InitController < CANIF_CHANNEL_CNT, CANIF_INIT_ID, CANIF_E_PARAM_CONTROLLER);
//    VALIDATE_NO_RV(ConfigurationIndex < CANIF_CHANNEL_CONFIGURATION_CNT, CANIF_INIT_ID, CANIF_E_PARAM_POINTER);
//
//    CONST (CanControllerIdType,AUTOMATIC) canControllerId_CanIf_PreInit_InitController = ARC_GET_CHANNEL_CONTROLLER(channel_CanIf_PreInit_InitController);
// /* const CanControllerIdType canControllerId_CanIf_PreInit_InitController = ARC_GET_CHANNEL_CONTROLLER(channel_CanIf_PreInit_InitController); */
//    /* Validate that the configuration at the index match the right channel */
//    VALIDATE_NO_RV(CanIf_ConfigPtr->ControllerConfig[ConfigurationIndex].CanIfControllerIdRef == channel_CanIf_PreInit_InitController, CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER);
//    P2CONST (Can_ControllerConfigType,AUTOMATIC,CANIF_APPL_CONST) canConfig_CanIf_PreInit_InitController = CanIf_ConfigPtr->ControllerConfig[ConfigurationIndex].CanIfInitControllerRef;
// /* const Can_ControllerConfigType *canConfig_CanIf_PreInit_InitController = CanIf_ConfigPtr->ControllerConfig[ConfigurationIndex].CanIfInitControllerRef; */
//    /* Validate that the CanIfControllerConfig points to configuration for the right Can Controller */
//    VALIDATE_NO_RV(canConfig_CanIf_PreInit_InitController->CanControllerId == canControllerId_CanIf_PreInit_InitController, CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER);
//
//    Can_InitController(canControllerId_CanIf_PreInit_InitController, canConfig_CanIf_PreInit_InitController);
//}

/*------------------------------------------------------------------- */
/*M_E  Std_ReturnType CanIf_SetControllerMode(uint8 Controller,
    CanIf_ControllerModeType ControllerMode_CanIf_SetControllerMode)*/
/* (MISRA-C:2004 16.4/R) The identifiers used in the declaration and definition of a function shall be identical*/

/*Std_ReturnType CanIf_SetControllerMode(uint8 Controller,CanIf_ControllerModeType ControllerMode) SWS_compiler*/

FUNC(Std_ReturnType,CANIF_CODE) CanIf_SetControllerMode(
		/*(uint8 Controller,
          CanIf_ControllerModeType ControllerMode)*/
VAR(uint8, AUTOMATIC) Controller,
VAR(
Can_ControllerStateType, AUTOMATIC) ControllerMode
)

{
    /* Sayed add on Code */
    VAR(Std_ReturnType,AUTOMATIC) To_return = E_OK;
    /* We call this a CanIf channel. Hopefully makes it easier to follow. */
    /* M_E CanIf_Arc_ChannelIdType channel = (CanIf_Arc_ChannelIdType) Controller; */
    /*  (MISRA-C:2004 5.7/A) No identifier name should be reused ("channel") */

    VAR(CanIf_Arc_ChannelIdType,AUTOMATIC) channel_CanIf_SetControllerMode = (CanIf_Arc_ChannelIdType) Controller;




    VALIDATE( CanIf_Global.initRun, CANIF_SET_CONTROLLER_MODE_ID, CANIF_E_UNINIT );
    VALIDATE( channel_CanIf_SetControllerMode < CANIF_CHANNEL_CNT, CANIF_SET_CONTROLLER_MODE_ID, CANIF_E_PARAM_CONTROLLER );




   To_return=E_OK;        //VALIDATE((uint8)FALSE, CANIF_SET_CONTROLLER_MODE_ID, CANIF_E_UNINIT);

//    if (oldMode == CAN_CS_UNINIT)
//    {
//
//        VALIDATE((uint8)FALSE, CANIF_SET_CONTROLLER_MODE_ID, CANIF_E_UNINIT); /* See figure 32, 33 */
//        To_return= E_NOT_OK;
//
//        /*return E_NOT_OK;*/
//    }


            if(To_return==E_OK)
    {
        /*M_E   CanControllerIdType canControllerId = ARC_GET_CHANNEL_CONTROLLER(Controller); */
        /*(MISRA-C:2004 5.7/A) No identifier name should be reused ("canControllerId") */
        CanControllerIdType canControllerId_CanIf_SetControllerMode = ARC_GET_CHANNEL_CONTROLLER(Controller);

        switch (ControllerMode)
        {
        case CAN_CS_STARTED:   /* Figure 32 */
        {




            CanIf_SetPduMode(channel_CanIf_SetControllerMode, CANIF_SET_ONLINE);
            if (Can_SetControllerMode(canControllerId_CanIf_SetControllerMode, CAN_T_START) == /*CAN_NOT_OK*/E_NOT_OK){
                /*   To_return = E_NOT_Ok; */
                To_return=E_NOT_OK;
                break;
                /* return E_NOT_OK; */
            }
            //CanIf_Global.channelData[channel_CanIf_SetControllerMode].Controller_Mode = CAN_CS_STARTED;
        }
        break;

        case CAN_CS_SLEEP: /* Figure 33 */
        {

            if (Can_SetControllerMode(canControllerId_CanIf_SetControllerMode, CAN_T_SLEEP) == /*CAN_NOT_OK*/E_NOT_OK){
                To_return = E_NOT_OK;
                break;
                /* return E_NOT_OK; */
            }
            //CanIf_Global.channelData[channel_CanIf_SetControllerMode].Controller_Mode = CAN_CS_SLEEP;
            break;
        }

        case CAN_CS_STOPPED:
        {
     CanIf_SetPduMode(channel_CanIf_SetControllerMode, CANIF_SET_OFFLINE);
            if (Can_SetControllerMode(canControllerId_CanIf_SetControllerMode, CAN_T_STOP) == /*CAN_NOT_OK*/E_NOT_OK)
            {
                To_return = E_NOT_OK;
                break;
                /* return E_NOT_OK; */
            }
            //CanIf_Global.channelData[channel_CanIf_SetControllerMode].Controller_Mode = CAN_CS_STOPPED;
            break;
        }

        case CAN_CS_UNINIT:

            /* Just fall through */
            break;
            /*M_E No default */
            /*(MISRA-C:2004 15.3/R) The final clause of a switch statement shall be the default clause */
        default :

        {
            break;
        }
       }
    }
    /* return E_NOT_OK; */
    return To_return;
}

FUNC(void,CANIF_CODE) CanIf_ControllerModeIndication
(
	VAR(CanIf_Arc_ChannelIdType,AUTOMATIC) channel_CanIf_SetControllerMode,
	VAR(
Can_ControllerStateType, AUTOMATIC) ControllerMode
)
{
	VALIDATE_NO_RV( CanIf_Global.initRun, CANIF_SET_CONTROLLER_MODE_ID, CANIF_E_UNINIT );
	VALIDATE_NO_RV( channel_CanIf_SetControllerMode < CANIF_CHANNEL_CNT, CANIF_SET_CONTROLLER_MODE_ID, CANIF_E_PARAM_CONTROLLER );
	CanIf_Global.channelData[channel_CanIf_SetControllerMode].Controller_Mode = ControllerMode;
}

/*------------------------------------------------------------------- */

/*Std_ReturnType CanIf_GetControllerMode(uint8 Controller,CanIf_ControllerModeType *ControllerModePtr)*/

FUNC(Std_ReturnType,CANIF_CODE) CanIf_GetControllerMode(/*(uint8 Controller,
                                       CanIf_ControllerModeType *ControllerModePtr)*/

VAR(uint8, AUTOMATIC) Controller,
P2VAR(
Can_ControllerStateType, AUTOMATIC, CANIF_APPL_DATA) ControllerModePtr
)
{
    /* We call this a CanIf channel_CanIf_GetControllerMode. Hopefully makes it easier to follow. */

	VAR(CanIf_Arc_ChannelIdType,AUTOMATIC) channel_CanIf_GetControllerMode = (CanIf_Arc_ChannelIdType) Controller;
   /* CanIf_Arc_ChannelIdType channel_CanIf_GetControllerMode = (CanIf_Arc_ChannelIdType) Controller; */

    VALIDATE(CanIf_Global.initRun, CANIF_GET_CONTROLLER_MODE_ID, CANIF_E_UNINIT );
    VALIDATE(channel_CanIf_GetControllerMode < CANIF_CHANNEL_CNT, CANIF_GET_CONTROLLER_MODE_ID, CANIF_E_PARAM_CONTROLLER );
    VALIDATE(ControllerModePtr != NULL, CANIF_GET_CONTROLLER_MODE_ID, CANIF_E_PARAM_POINTER );

    *ControllerModePtr = CanIf_Global.channelData[channel_CanIf_GetControllerMode].Controller_Mode;

    return E_OK;
}

/*------------------------------------------------------------------- */
/**
 * Matches a Tx PDU id agaist the ones that are in the database.
 *
 * @returns Ptr a TxPdu
 */
/*testing*/



#if ( CANIF_ARC_RUNTIME_PDU_CONFIGURATION == STD_ON )
FUNC_P2VAR(CanIf_TxPduConfigType,AUTOMATIC, CANIF_CODE)CanIf_FindTxPduEntry (VAR(uint32, AUTOMATIC) id_CanIf_FindTxPduEntry)
#else
static FUNC_P2CONST(CanIf_TxPduConfigType, AUTOMATIC, CANIF_CODE) CanIf_FindTxPduEntry(VAR(uint32, AUTOMATIC) id_CanIf_FindTxPduEntry)
#endif
{
#if CANIF_ARC_RUNTIME_PDU_CONFIGURATION == STD_ON
	P2VAR (CanIf_TxPduConfigType,AUTOMATIC,CANIF_APPL_CONST) To_ret;
#else
	P2CONST (CanIf_TxPduConfigType,AUTOMATIC,CANIF_APPL_CONST) To_ret;
#endif
    if (id_CanIf_FindTxPduEntry >= (uint32) CanIf_ConfigPtr->InitConfig->CanIfNumberOfCanTXPduIds) {

        To_ret = ( CanIf_TxPduConfigType * ) NULL;

    } else {

        To_ret =  &CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr[id_CanIf_FindTxPduEntry];

    }

    return To_ret ;
}




#if ( CANIF_ARC_RUNTIME_PDU_CONFIGURATION == STD_ON )

/*CanIf_RxPduConfigType * CanIf_FindRxPduEntry(PduIdType id)*/
FUNC_P2VAR(CanIf_RxPduConfigType,AUTOMATIC, CANIF_CODE)CanIf_FindTxPduEntry (uint32 id_CanIf_FindTxPduEntry)
{
    if (id >= CanIf_ConfigPtr->InitConfig->CanIfNumberOfCanRxPduIds) {
        return NULL;
    } else {
        return (CanIf_RxPduConfigType*) &CanIf_ConfigPtr->InitConfig->CanIfRxPduConfigPtr[id];
    }
}

/*const CanIf_HrhConfigType* CanIf_Arc_GetReceiveHandler(CanIf_Arc_ChannelIdType Channel)*/

{
    const CanIf_InitHohConfigType *hohConfig;
    const CanIf_HrhConfigType *hrhConfig;

    /* foreach(hoh){ foreach(hrh in hoh) {} } */
    hohConfig = CanIf_ConfigPtr->InitConfig->CanIfHohConfigPtr;
    hohConfig--;
    do
    {
        hohConfig++;

        hrhConfig = hohConfig->CanIfHrhConfig;
        hrhConfig--;
        do
        {
            hrhConfig++;
            if (hrhConfig->CanIfCanControllerHrhIdRef == Channel)
                return hrhConfig;
        } while(!hrhConfig->CanIf_Arc_EOL);

    } while(!hohConfig->CanIf_Arc_EOL_Mod2);

    DET_REPORTERROR(MODULE_ID_CANIF, 0, 0xFF, CANIF_E_PARAM_HRH);

    return NULL;
}

const CanIf_HthConfigType* CanIf_Arc_GetTransmitHandler(CanIf_Arc_ChannelIdType Channel) {
    const CanIf_InitHohConfigType *hohConfig;
    const CanIf_HthConfigType *hthConfig;

    /* foreach(hoh){ foreach(hrh in hoh) {} } */
    hohConfig = CanIf_ConfigPtr->InitConfig->CanIfHohConfigPtr;
    hohConfig--;
    do
    {
        hohConfig++;

        hthConfig = hohConfig->CanIfHthConfig;
        hthConfig--;
        do
        {
            hthConfig++;
            if (hthConfig->CanIfCanControllerIdRefHth == Channel)
                return hthConfig;
        } while(!hthConfig->CanIf_Arc_EOL_Mod);

    } while(!hohConfig->CanIf_Arc_EOL_Mod2);

    DET_REPORTERROR(MODULE_ID_CANIF, 0, 0xFF, CANIF_E_PARAM_HTH);

    return NULL;
}
#endif
/*
 * canIF Buffer Message :
 *
 */
static FUNC(Std_ReturnType,CANIF_CODE)CanIf_BufferPdu
(
 VAR(uint32,AUTOMATIC) TxPduId,
 P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr
)
{
	volatile VAR(uint8,AUTOMATIC) BufferSortingCounter1 = 0;
	volatile VAR(uint8,AUTOMATIC) BufferSortingCounter2 = 0;
	VAR(uint8,AUTOMATIC) BuffSize = 0;
	VAR(uint8,AUTOMATIC) ExistFlag = 0;
	VAR(Std_ReturnType,AUTOMATIC) ret = E_NOT_OK;
	VAR(CanIf_TxBuffPduInfo_t,AUTOMATIC) TempTxBuffInfo;
	P2VAR(CanIf_TxBufferCfg_t,AUTOMATIC,CANIF_CODE) BuffPtr = CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr[TxPduId].CanIfTxBufferRef;
	P2CONST(CanIf_TxPduConfigType, AUTOMATIC,CANIF_CODE) txEntry;
	txEntry = CanIf_FindTxPduEntry(TxPduId);

	BuffSize = txEntry->CanIfTxBufferRef->BufferSize;

	if(BuffSize <= CanIf_Pdu_BufferIndex[txEntry->CanIfTxBufferRef->HthIndex]){
		ret = E_NOT_OK;
	}
	else
	{
		for(BufferSortingCounter1 = 0; BufferSortingCounter1<CanIf_Pdu_BufferIndex[txEntry->CanIfTxBufferRef->HthIndex];BufferSortingCounter1++){
			if(TxPduId == txEntry->CanIfTxBufferRef->BufferInfoPtr[BufferSortingCounter1].TxPduId){
				if(txEntry->CanIfCanTxPduType == CANIF_PDU_TYPE_DYNAMIC){
					ExistFlag = 2;
					txEntry->CanIfTxBufferRef->BufferInfoPtr[BufferSortingCounter1].CanIfPduCanId = txEntry->CanIfCanTxPduIdCanId;
					txEntry->CanIfTxBufferRef->BufferInfoPtr[BufferSortingCounter1].dataLength = PduInfoPtr->SduLength;
					for(BufferSortingCounter2=0;BufferSortingCounter2<PduInfoPtr->SduLength;BufferSortingCounter2++)
					{
						txEntry->CanIfTxBufferRef->BufferInfoPtr[BufferSortingCounter1].Data[BufferSortingCounter2] = PduInfoPtr->SduDataPtr[BufferSortingCounter2];
					}
				}
				else{
					ExistFlag = 1;
					txEntry->CanIfTxBufferRef->BufferInfoPtr[BufferSortingCounter1].dataLength = PduInfoPtr->SduLength;
					for(BufferSortingCounter2=0;BufferSortingCounter2<PduInfoPtr->SduLength;BufferSortingCounter2++)
					{
						txEntry->CanIfTxBufferRef->BufferInfoPtr[BufferSortingCounter1].Data[BufferSortingCounter2] = PduInfoPtr->SduDataPtr[BufferSortingCounter2];
					}
				}
				break;
			}
		}
		if(ExistFlag==0){
			TempTxBuffInfo.TxPduId = TxPduId;
			TempTxBuffInfo.CanIfPduCanId = txEntry->CanIfCanTxPduIdCanId;
			for(BufferSortingCounter1=0;BufferSortingCounter1<8;BufferSortingCounter1++)
			{
				TempTxBuffInfo.Data[BufferSortingCounter1] = PduInfoPtr->SduDataPtr[BufferSortingCounter1];
			}
			TempTxBuffInfo.dataLength = PduInfoPtr->SduLength;
			BuffPtr->BufferInfoPtr[CanIf_Pdu_BufferIndex[CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr[TxPduId].CanIfTxBufferRef->HthIndex]] = TempTxBuffInfo;
			CanIf_Pdu_BufferIndex[txEntry->CanIfTxBufferRef->HthIndex]++;
		}
		if(ExistFlag == 0 || ExistFlag == 2){
			for(BufferSortingCounter1=0; BufferSortingCounter1 < CanIf_Pdu_BufferIndex[txEntry->CanIfTxBufferRef->HthIndex]; BufferSortingCounter1++)
			{
				for(BufferSortingCounter2=0; BufferSortingCounter2 < CanIf_Pdu_BufferIndex[txEntry->CanIfTxBufferRef->HthIndex]-1; BufferSortingCounter2++)
				{
					if(BuffPtr->BufferInfoPtr[BufferSortingCounter2].CanIfPduCanId < BuffPtr->BufferInfoPtr[BufferSortingCounter2+1].CanIfPduCanId)
					{
						TempTxBuffInfo = BuffPtr->BufferInfoPtr[BufferSortingCounter2];
						BuffPtr->BufferInfoPtr[BufferSortingCounter2] = BuffPtr->BufferInfoPtr[(BufferSortingCounter2)+1];
						BuffPtr->BufferInfoPtr[BufferSortingCounter2+1]  = TempTxBuffInfo;
					}
				}
			}
		}


		ret = E_OK;
	}
	return ret;
}
/*-------------------------------------------------------------------*/
/*
 * Buffer send request :
 * */
static FUNC(void,CANIF_CODE) BufferSendRequest(
		P2CONST(CanIf_TxPduConfigType,AUTOMATIC,CANIF_APPL_CONST) entry
)
{

	CanIf_TxBufferCfg_t *bfrTmp=entry->CanIfTxBufferRef;

	if (bfrTmp->BufferSize==0){
		return;
	}
	else {
		VAR(uint8,AUTOMATIC) CurrentHthIndex=entry->CanIfTxBufferRef->HthIndex;
		if(CanIf_Pdu_BufferIndex[CurrentHthIndex]>0){
			VAR(Can_PduType,AUTOMATIC) canPdu;

			 canPdu.id = entry->CanIfTxBufferRef->BufferInfoPtr[CanIf_Pdu_BufferIndex[CurrentHthIndex]-1].CanIfPduCanId;

			 canPdu.length = (uint8)entry->CanIfTxBufferRef->BufferInfoPtr[CanIf_Pdu_BufferIndex[CurrentHthIndex]-1].dataLength ;
			 canPdu.sdu = entry->CanIfTxBufferRef->BufferInfoPtr[CanIf_Pdu_BufferIndex[CurrentHthIndex]-1].Data;
			 canPdu.swPduHandle = entry->CanIfTxBufferRef->BufferInfoPtr[CanIf_Pdu_BufferIndex[CurrentHthIndex]-1].TxPduId;

			  Can_ReturnType rVal = Can_Write(CanIf_hthConfigTypeInstance[entry->CanIfTxBufferRef->HthIndex].CanIfHthIdSymRef,&canPdu);
			  if(rVal == /*CAN_OK*/E_OK){
				  CanIf_Pdu_BufferIndex[CurrentHthIndex]--;
			  }

		}


	}


}

FUNC(Std_ReturnType,CANIF_CODE) CanIf_Transmit //N_1M Std_ReturnType is uint8
		(VAR(uint32, AUTOMATIC) CanTxPduId,
				P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr) //N_1M CANIF_APPL_CONST is Empty

{

	VAR(Std_ReturnType,AUTOMATIC) ret=E_OK; //N_1M E_OK is 0

	VAR(Can_PduType,AUTOMATIC) canPdu; //N_1M Can_PduType is a struct id, length, sdu, swpduhandle

    P2CONST(CanIf_TxPduConfigType,AUTOMATIC,CANIF_APPL_CONST) txEntry; //N_1M CanIf_TxPduConfigType struct of CanIfTxPduId, ,..

    VAR(Can_ControllerStateType,AUTOMATIC) csMode=(Can_ControllerStateType) 0; //N_1M Can_ControllerStateType CanIf modes enum UNINIT, STOPPED, STARTED, SLEEP

    VAR(Can_ControllerStateType,AUTOMATIC) pduMode=(Can_ControllerStateType) 0;


    VALIDATE(CanIf_Global.initRun, CANIF_TRANSMIT_ID, CANIF_E_UNINIT ); //N_1M if CanIf_Global.initRun=0 Error in function CANIF_TRANSMIT_ID error is CANIF_E_UNINIT.. CanIf_UnInit is called 
    VALIDATE((PduInfoPtr != 0), CANIF_TRANSMIT_ID, CANIF_E_PARAM_POINTER ); //N_1M if PduInfoPtr != 0 Error in function CANIF_TRANSMIT_ID error is CANIF_E_PARAM_POINTER.. CanIf_UnInit is called 

    /* Get the controller from L-PDU handle */
    txEntry = CanIf_FindTxPduEntry(CanTxPduId);

    if (txEntry == 0)
    {
        VALIDATE((uint8)FALSE, CANIF_TRANSMIT_ID, CANIF_E_INVALID_TXPDUID); //N_1M CANIF_E_INVALID_TXPDUID error with pdu Id
        ret = E_NOT_OK;
    }

    if(ret==E_OK)
    {
        CanIf_Arc_ChannelIdType channel_CanIf_Transmit = CanIf_ConfigPtr->InitConfig->CanIfHthCanControllerIdArr[txEntry->CanIfTxBufferRef->HthIndex]; /*The HTH index "in the array of HTHs" which this buffer is mapped to*/
        		/*CanIfHthCanControllerIdArr has controller IDs for each HTH*/ /*channel_CanIf_Transmit has Ctrlr ID of the HTH index*/

        /* Get and verify the controller mode */
        if(ret == E_OK)
        {
            if (CanIf_GetControllerMode(channel_CanIf_Transmit, &csMode) == E_NOT_OK){
                ret = E_NOT_OK; //N_1M Conditon gets Controller mode and puts it in csMode and returns E_NOT_OK if it failed
            }
        }

        if ( (ret == E_OK) && (csMode != CAN_CS_STARTED) ){  /* CANIF_161 */
            ret= E_NOT_OK;
        }

        /* Get and verify the PDU channel mode control */
       if(ret == E_OK)
        {
        if ((CanIf_GetPduMode(channel_CanIf_Transmit, &pduMode) == E_NOT_OK) ){
            ret= E_NOT_OK;
            /*  return E_NOT_OK; */
        }
        }

        if ( (ret == E_OK) && (pduMode != CANIF_GET_TX_ONLINE) && (pduMode != CANIF_GET_ONLINE) ){
            ret = E_NOT_OK;
            /*  return E_NOT_OK; */
        }
        if (ret == E_OK)
        {
            canPdu.id = txEntry->CanIfCanTxPduIdCanId;

            canPdu.length = (uint8) PduInfoPtr->SduLength;
            canPdu.sdu = PduInfoPtr->SduDataPtr;
            canPdu.swPduHandle = CanTxPduId;

            Can_ReturnType rVal = Can_Write(CanIf_hthConfigTypeInstance[txEntry->CanIfTxBufferRef->HthIndex].CanIfHthIdSymRef, &canPdu); /*S_CANIF023 */
            if (rVal == /*CAN_NOT_OK*/E_NOT_OK){
                ret = E_NOT_OK;
                /* return E_NOT_OK; */
            }

            if (  (ret == E_OK) && (rVal == CAN_BUSY) )  /* CANIF 082, CANIF 161 */
            {
            	printf("HERE\n");

            	//printf("The Size of Buffer is %d\n",txEntry->CanIfTxBufferRef->BufferSize);
            	if(txEntry->CanIfTxBufferRef->BufferSize == 0){

            		ret = E_NOT_OK;
            	}
            	else{

            		if(CanIf_BufferPdu(CanTxPduId,PduInfoPtr) != E_OK){

            		        ret = E_NOT_OK;
            		  }
            	}
            	//printf("The After Size of Buffer is %d\n",txEntry->CanIfTxBufferRef->BufferSize);


            }
        }
    }

    return ret;
}

/*------------------------------------------------------------------- */

#if ( CANIF_READRXPDU_DATA_API == STD_ON )
Std_ReturnType CanIf_ReadRxPduData(uint32 CanRxPduId,
                                   PduInfoType *PduInfoPtr)
{
    VALIDATE(FALSE, CANIF_READTXPDUDATA_ID, CANIF_E_NOK_NOSUPPORT);
    VALIDATE(CanIf_Global.initRun == STD_ON, CANIF_READTXPDUDATA_ID, CANIF_E_UNINIT );
    VALIDATE(PduInfoPtr != 0, CANIF_READTXPDUDATA_ID, CANIF_E_PARAM_POINTER );

    /* This function is not supported */

    return E_NOT_OK;
}
#endif

/*------------------------------------------------------------------- */

#if ( CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON )
CanIf_NotifStatusType CanIf_ReadTxNotifStatus(uint32 CanTxPduId)
{
    const CanIf_TxPduConfigType *txEntry;
    VALIDATE(FALSE, CANIF_READTXNOTIFSTATUS_ID, CANIF_E_NOK_NOSUPPORT);
    VALIDATE(CanIf_Global.initRun, CANIF_READTXNOTIFSTATUS_ID, CANIF_E_UNINIT );

    /* Get the controller from L-PDU handle */
    txEntry = CanIf_FindTxPduEntry(CanTxPduId);

    if (txEntry == 0)
    {
        VALIDATE(FALSE, CANIF_READTXNOTIFSTATUS_ID, CANIF_E_INVALID_TXPDUID);
        return CANIF_NO_NOTIFICATION;
    }

    if (txEntry->CanIfReadTxPduNotifyStatus == FALSE)
    {
        VALIDATE(FALSE, CANIF_READTXNOTIFSTATUS_ID, CANIF_E_INVALID_TXPDUID);
        return CANIF_NO_NOTIFICATION;
    }

    /* This function is not supported */

    return CANIF_NO_NOTIFICATION;
}
#endif

/*------------------------------------------------------------------- */

#if ( CANIF_READRXPDU_NOTIFY_STATUS_API == STD_ON )
CanIf_NotifStatusType CanIf_ReadRxNotifStatus(uint32 CanRxPduId)
{
    VALIDATE(FALSE, CANIF_READRXNOTIFSTATUS_ID, CANIF_E_NOK_NOSUPPORT);
    VALIDATE(CanIf_Global.initRun, CANIF_READRXNOTIFSTATUS_ID, CANIF_E_UNINIT );

    return CANIF_NO_NOTIFICATION;
}
#endif

/*------------------------------------------------------------------- */

/*Std_ReturnType CanIf_SetPduMode(uint8 Controller, CanIf_ChannelSetModeType PduModeRequest)*/

FUNC(Std_ReturnType,CANIF_CODE) CanIf_SetPduMode(
		/*(uint8 Controller,
		 CanIf_ChannelSetModeType PduModeRequest) */
		VAR(uint8, AUTOMATIC) Controller,
		VAR(CanIf_ChannelSetModeType, AUTOMATIC) PduModeRequest)

{

    /* We call this a CanIf channel_CanIf_SetPduMode. Hopefully makes it easier to follow. */
	VAR(CanIf_Arc_ChannelIdType,AUTOMATIC) channel_CanIf_SetPduMode = (CanIf_Arc_ChannelIdType) Controller;
   /* CanIf_Arc_ChannelIdType channel_CanIf_SetPduMode = (CanIf_Arc_ChannelIdType) Controller; */
    VALIDATE( CanIf_Global.initRun, CANIF_SETPDUMODE_ID, CANIF_E_UNINIT );
    VALIDATE( channel_CanIf_SetPduMode < CANIF_CHANNEL_CNT, CANIF_SETPDUMODE_ID, CANIF_E_PARAM_CONTROLLER );
    /* M_E   CanIf_ChannelGetModeType oldMode = CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode; */
    /*(MISRA-C:2004 5.7/A) No identifier name should be reused */
    VAR(CanIf_ChannelGetModeType,AUTOMATIC) oldMode_CanIf_SetPduMode = CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode;
  /*  CanIf_ChannelGetModeType oldMode_CanIf_SetPduMode = CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode; */

    switch(PduModeRequest)
    {
    case CANIF_SET_OFFLINE:
        CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_OFFLINE;
        break;
    case CANIF_SET_RX_OFFLINE:
        if (oldMode_CanIf_SetPduMode == CANIF_GET_RX_ONLINE){
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_OFFLINE;
        } else if (oldMode_CanIf_SetPduMode == CANIF_GET_ONLINE){
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_TX_ONLINE;
        } else if (oldMode_CanIf_SetPduMode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE){
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_OFFLINE_ACTIVE;
        }
        /* M_E */
        /* (MISRA-C:2004 14.10/R) All if ... else if constructs shall be terminated with an else clause */
        else
        {

        }

        /* Other oldmodes don't care */
        break;
    case CANIF_SET_RX_ONLINE:
        if (oldMode_CanIf_SetPduMode == CANIF_GET_OFFLINE){
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_RX_ONLINE;
        } else if (oldMode_CanIf_SetPduMode == CANIF_GET_TX_ONLINE) {
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_ONLINE;
        } else if (oldMode_CanIf_SetPduMode == CANIF_GET_OFFLINE_ACTIVE){
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE;
        }
        /* M_E */
        /* (MISRA-C:2004 14.10/R) All if ... else if constructs shall be terminated with an else clause */
        else
        {

        }

        /* Other oldmodes don't care */
        break;
    case CANIF_SET_TX_OFFLINE:
        if (oldMode_CanIf_SetPduMode == CANIF_GET_TX_ONLINE){
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_OFFLINE;
        } else if (oldMode_CanIf_SetPduMode == CANIF_GET_ONLINE) {
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_RX_ONLINE;
        } else if (oldMode_CanIf_SetPduMode == CANIF_GET_OFFLINE_ACTIVE) {
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_OFFLINE;
        } else if (oldMode_CanIf_SetPduMode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) {
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_RX_ONLINE;
        }
        /* M_E */
        /* (MISRA-C:2004 14.10/R) All if ... else if constructs shall be terminated with an else clause */
        else
        {

        }

        /* Other oldmodes don't care */
        break;
    case CANIF_SET_TX_ONLINE:
        if (oldMode_CanIf_SetPduMode == CANIF_GET_OFFLINE){
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_TX_ONLINE;
        } else if (oldMode_CanIf_SetPduMode == CANIF_GET_RX_ONLINE) {
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_ONLINE;
        } else if (oldMode_CanIf_SetPduMode == CANIF_GET_OFFLINE_ACTIVE) {
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_TX_ONLINE;
        } else if (oldMode_CanIf_SetPduMode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) {
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_ONLINE;
        }
        /* M_E */
        /* (MISRA-C:2004 14.10/R) All if ... else if constructs shall be terminated with an else clause */
        else
        {

        }

        /* Other oldmodes don't care */
        break;
    case CANIF_SET_ONLINE:
        CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_ONLINE;
        break;

    case CANIF_SET_TX_OFFLINE_ACTIVE:
        if (oldMode_CanIf_SetPduMode == CANIF_GET_OFFLINE) {
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_OFFLINE_ACTIVE;
        } else if (oldMode_CanIf_SetPduMode == CANIF_GET_RX_ONLINE) {
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE;
        } else if (oldMode_CanIf_SetPduMode == CANIF_GET_TX_ONLINE) {
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_OFFLINE_ACTIVE;
        } else if (oldMode_CanIf_SetPduMode == CANIF_GET_ONLINE) {
            CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE;
        }
        /* M_E */
        /* (MISRA-C:2004 14.10/R) All if ... else if constructs shall be terminated with an else clause */
        else
        {

        }

        /* Other oldmodes don't care */
        break;
    default :
    {
        break;
    }
    }


    return E_OK;
}

/*-------------------------------------------------------------------*/

/*Std_ReturnType CanIf_GetPduMode(uint8 Controller,CanIf_ChannelGetModeType *PduModePtr) SWS_compiler*/
FUNC(Std_ReturnType,CANIF_CODE) CanIf_GetPduMode(
VAR(uint8, AUTOMATIC) Controller,
P2VAR(CanIf_ChannelGetModeType, AUTOMATIC, CANIF_APPL_DATA) PduModePtr
)
{
    /* We call this a CanIf CanIf_GetPduMode_local. Hopefully makes it easier to follow. */

	VAR(CanIf_Arc_ChannelIdType,AUTOMATIC) CanIf_GetPduMode_local = (CanIf_Arc_ChannelIdType) Controller;
   /* CanIf_Arc_ChannelIdType CanIf_GetPduMode_local = (CanIf_Arc_ChannelIdType) Controller; */

    VALIDATE( CanIf_Global.initRun, CANIF_GETPDUMODE_ID, CANIF_E_UNINIT );
    VALIDATE( CanIf_GetPduMode_local < CANIF_CHANNEL_CNT, CANIF_GETPDUMODE_ID, CANIF_E_PARAM_CONTROLLER );

    *PduModePtr = CanIf_Global.channelData[CanIf_GetPduMode_local].PduMode;

    return E_OK;
}
//#if (CANIF_ARC_RUNTIME_PDU_CONFIGURATION==STD_OFF)
//#define CANIF_ARC_RUNTIME_PDU_CONFIGURATION_2 (STD_ON) /*to avoid redefinition*/
//#endif

#if ( CANIF_ARC_RUNTIME_PDU_CONFIGURATION == STD_ON )
void CanIf_SetDynamicTxId(uint32 CanTxPduId, Can_IdType CanId)
{
    CanIf_TxPduConfigType *txEntry_CanIf_SetDynamicTxId;
    VALIDATE_NO_RV(CanIf_Global.initRun, CANIF_SETDYNAMICTX_ID, CANIF_E_UNINIT );

    /* Get the controller from L-PDU handle */
    txEntry_CanIf_SetDynamicTxId = CanIf_FindTxPduEntry(CanTxPduId); /*unresolved warning*/
    /*Misra error of  a value of type "const CanIf_TxPduConfigType *" cannot be assigned to an entity of type "CanIf_TxPduConfigType *"
     * Cannot be resolved because the defined pdu pointer cannot be const. */

    if (txEntry_CanIf_SetDynamicTxId == 0)
    {
        VALIDATE_NO_RV(FALSE, CANIF_SETDYNAMICTX_ID, CANIF_E_INVALID_TXPDUID);
      /*  return; */
    }

    /* Check that this is a dymanic PDU */
    else   if (txEntry_CanIf_SetDynamicTxId->CanIfCanTxPduType != CANIF_PDU_TYPE_DYNAMIC)
    {
        VALIDATE_NO_RV(FALSE, CANIF_SETDYNAMICTX_ID, CANIF_E_INVALID_TXPDUID);
     /*   return; */
    }

    /* Check that this is an extended or standard id */
    else  if ((((CanId & 0x80000000U) != (Can_IdType) 0) && (txEntry_CanIf_SetDynamicTxId->CanIfTxPduIdCanIdType == CANIF_CAN_ID_TYPE_29)) ||
            (((CanId & 0x80000000U) == (Can_IdType) 0) && (txEntry_CanIf_SetDynamicTxId->CanIfTxPduIdCanIdType == CANIF_CAN_ID_TYPE_11)))
    {
        /* Update the CanID */
        txEntry_CanIf_SetDynamicTxId->CanIfCanTxPduIdCanId = CanId & 0x7FFFFFFFU;
    }
    else
    {
        /* Inavlid Canid to configuration */
        VALIDATE_NO_RV(FALSE, CANIF_SETDYNAMICTX_ID, CANIF_E_PARAM_CANID);
    }

    return ;
}
#endif
//#define CANIF_ARC_RUNTIME_PDU_CONFIGURATION_2 (STD_OFF)


#if ( CANIF_TRANSCEIVER_API == STD_ON )
Std_ReturnType CanIf_SetTransceiverMode(uint8 Transceiver,
                                        CanIf_TransceiverModeType TransceiverMode)
{
    VALIDATE(FALSE, CANIF_SET_TRANSCEIVERMODE_ID, CANIF_E_NOK_NOSUPPORT);
    /* Not supported */
    return E_NOT_OK;
}

Std_ReturnType CanIf_GetTransceiverMode(uint8 Transceiver,
                                        CanIf_TransceiverModeType *TransceiverModePtr)
{
    VALIDATE(FALSE, CANIF_GET_TRANSCEIVERMODE_ID, CANIF_E_NOK_NOSUPPORT);
    /* Not supported */

    return E_NOT_OK;
}

Std_ReturnType CanIf_GetTrcvWakeupReason(uint8 Transceiver,
                                         CanIf_TrcvWakeupReasonType *TrcvWuReasonPtr)
{
    VALIDATE(FALSE, CANIF_GET_TRCVMODEREASON_ID, CANIF_E_NOK_NOSUPPORT);
    /* Not supported */

    return E_NOT_OK;
}

Std_ReturnType CanIf_SetTransceiverWakeupMode(uint8 Transceiver,
                                              CanIf_TrcvWakeupModeType *TrcvWakeupMode)
{
    VALIDATE(FALSE, CANIF_SET_TRANSCEIVERWAKEMODE_ID, CANIF_E_NOK_NOSUPPORT);
    /* Not supported */

    return E_NOT_OK;
}
#endif

#if ( CANIF_WAKEUP_EVENT_API == STD_ON )
Std_ReturnType CanIf_CheckWakeup(EcuM_WakeupSourceType WakeupSource)
{
    VALIDATE(FALSE, CANIF_CHECKWAKEUP_ID, CANIF_E_NOK_NOSUPPORT);
    /* Not supported */

    return E_NOT_OK;
}

Std_ReturnType CanIf_CheckValidation(EcuM_WakeupSourceType WakeupSource)
{
    VALIDATE(FALSE, CANIF_CHECKVALIDATION_ID, CANIF_E_NOK_NOSUPPORT);
    /* Not supported */

    return E_NOT_OK;
}
#endif

/*
 * Callback interface from driver
 */

/*void CanIf_TxConfirmation(PduIdType canTxPduId)*/

#if (CANIF_TESTING_TRANSMIT_NADAANDAHMED == 0)

FUNC(void,CANIF_CODE) CanIf_TxConfirmation(
		/*PduIdType canTxPduId*/
		VAR(uint32, AUTOMATIC) canTxPduId
		)
{
    VALIDATE_NO_RV(CanIf_Global.initRun, CANIF_TXCONFIRMATION_ID, CANIF_E_UNINIT);
    VALIDATE_NO_RV(CanIf_Global.initRun, CANIF_TXCONFIRMATION_ID, CANIF_E_UNINIT);

    VALIDATE_NO_RV((uint8)(canTxPduId < (uint16)CanIf_ConfigPtr->InitConfig->CanIfNumberOfCanTXPduIds),CANIF_TXCONFIRMATION_ID,CANIF_E_PARAM_LPDU);

        P2CONST(CanIf_TxPduConfigType,AUTOMATIC,CANIF_APPL_CONST) entry =
                &CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr[canTxPduId];
       /* const CanIf_TxPduConfigType* entry =
                &CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr[canTxPduId]; */


      //  if (entry->CanIfUserTxConfirmation != NULL) MentorTX

        if (N_M1 (CanIF_TxPDUCbkConfig_a[entry->CanIfUserTxIndex].CanIfUserTxIndication) != NULL)
        {
            CanIf_ChannelGetModeType mode_CanIf_TxConfirmation= (CanIf_ChannelGetModeType) 0 ;
            CanIf_GetPduMode(CanIf_ConfigPtr->InitConfig->CanIfHthCanControllerIdArr[entry->CanIfTxBufferRef->HthIndex], &mode_CanIf_TxConfirmation);
            /*CanIf_ConfigPtr->InitConfig->CanIfHthCanControllerIdArr[entry->CanIfTxBufferRef->HthIndex]*/
            if ((mode_CanIf_TxConfirmation == CANIF_GET_TX_ONLINE) || (mode_CanIf_TxConfirmation == CANIF_GET_ONLINE)
                    || (mode_CanIf_TxConfirmation == CANIF_GET_OFFLINE_ACTIVE) || (mode_CanIf_TxConfirmation == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) )
            {
                //entry->CanIfUserTxConfirmation(entry->CanIfTxPduId);  /* CANIF053 */ MentorTx
            	(CanIF_TxPDUCbkConfig_a[entry->CanIfUserTxIndex].CanIfUserTxIndication)(entry->CanIfTxPduId);
            	/*
            	 * pending requests and sending from Buffer :
            	 * */
            	BufferSendRequest(entry);


    #if CANIF_UNIT_TESTING == STD_ON
                if(testNumber == 0)
                    testNumber = 1;
    #endif
            }
    #if CANIF_UNIT_TESTING == STD_ON
            else {
                if(testNumber == 0) {
                    PRINT("The channel is in inappropriate mode");
                    testNumber = 8;
                }
            }
    #endif
        }
    #if CANIF_UNIT_TESTING == STD_ON
            else {
                if(testNumber == 0) {
                    PRINT("The txConfirmation call-out function wasn't be initialized");
                    testNumber = 4;
                }
            }
    #endif
        return;
}
#endif
/*void CanIf_RxIndication(uint8 Hrh, Can_IdType CanId, uint8 CanDlc,const uint8 *CanSduPtr) CANIF023 S_ */
FUNC(void,CANIF_CODE)CanIf_RxIndication(

		/*(uint8 Hrh, Can_IdType CanId, uint8 CanDlc,
		                        const uint8 *CanSduPtr)*/ /*S_CANIF023*/

		VAR(uint8, AUTOMATIC) Hrh,
		VAR(Can_IdType, AUTOMATIC) CanId,
		VAR(uint8, AUTOMATIC) CanDlc,
		P2CONST(uint8, AUTOMATIC, CANIF_APPL_DATA) CanSduPtr)
{

	VAR(uint8,AUTOMATIC) cont= (uint8) 0 ;
  /*  uint8 cont= (uint8) 0 ; */

	VAR(uint8,AUTOMATIC) check_t= (uint8) 0 ;
   /* uint8 check_t =(uint8)0; */
    VALIDATE_NO_RV(CanIf_Global.initRun, CANIF_RXINDICATION_ID, CANIF_E_UNINIT);
    VALIDATE_NO_RV(CanSduPtr != NULL, CANIF_RXINDICATION_ID, CANIF_E_PARAM_POINTER);

    /* Check PDU mode before continue processing */
    /*M_E  CanIf_ChannelGetModeType mode;*/
    /* (MISRA-C:2004 5.7/A) No identifier name should be reused ("mode") */
    VAR(CanIf_ChannelGetModeType,AUTOMATIC) mode_CanIf_RxIndication = (CanIf_ChannelGetModeType)0;
 /*   CanIf_ChannelGetModeType mode_CanIf_RxIndication = (CanIf_ChannelGetModeType)0; */

   VAR(CanIf_Arc_ChannelIdType,AUTOMATIC) channel_CanIf_RxIndication = CanIf_Arc_FindHrhChannel( (Can_Arc_HRHType) Hrh);
   /* CanIf_Arc_ChannelIdType channel_CanIf_RxIndication = CanIf_Arc_FindHrhChannel( (Can_Arc_HRHType) Hrh); */

//    /*B_W if (channel == -1)  // Invalid HRH */
//    /*pointless comparison of unsigned integer with a negative constant */
    if ((signed)channel_CanIf_RxIndication == -1)
    {
        check_t =(uint8)1;
        /* return; */
    }
//
   if (check_t==(uint8)0)
   {
    if ((CanIf_GetPduMode(channel_CanIf_RxIndication,&mode_CanIf_RxIndication)==E_OK) )
    {
        if ( ((mode_CanIf_RxIndication == CANIF_GET_OFFLINE) || (mode_CanIf_RxIndication == CANIF_GET_TX_ONLINE) ||
                (mode_CanIf_RxIndication == CANIF_GET_OFFLINE_ACTIVE)) )
        {
            /* Receiver path is disabled so just drop it */
            check_t =(uint8)1;
            /* return; */
        }
    }
    else
    {
        check_t = (uint8)1;
        /* return;*/
        /* No mode so just return */
    }
}
    if(check_t==(uint8)0)
    {

        /* M_E const CanIf_RxPduConfigType *entry= CanIf_ConfigPtr->InitConfig->CanIfRxPduConfigPtr; */
        /*  (MISRA-C:2004 5.7/A) No identifier name should be reused */
    	P2CONST(CanIf_RxPduConfigType,AUTOMATIC,CANIF_APPL_CONST) entry_CanIf_RxIndication = CanIf_ConfigPtr->InitConfig->CanIfRxPduConfigPtr;
     /*   const CanIf_RxPduConfigType *entry_CanIf_RxIndication = CanIf_ConfigPtr->InitConfig->CanIfRxPduConfigPtr; */

    	VAR(uint8,AUTOMATIC) entry_count = (uint8) 0;
      /*  uint8 entry_count = (uint8) 0 ; *//* Needed to define another variable for pointer index rather than loop variable to maintain functionality  */
        /* Find the CAN id in the RxPduList */
    	VAR(uint16,AUTOMATIC) i_CanIf_RxIndication;
       /* uint16 i_CanIf_RxIndication; */
        for (i_CanIf_RxIndication =(uint16) 0;(  (check_t==(uint8)0) && (i_CanIf_RxIndication < (uint16)CanIf_ConfigPtr->InitConfig->CanIfNumberOfCanRxPduIds) ); i_CanIf_RxIndication++)
        {
            cont=(uint8)0;

            if (CanIf_hrhConfigTypeInstance[i_CanIf_RxIndication].CanIfCanControllerHrhIdRef == Hrh)
            {
                /* Software filtering */
                if ((&entry_CanIf_RxIndication[entry_count])->CanIfCanRxPduHrhRef->CanIfHrhType == CAN_ARC_HANDLE_TYPE_BASIC)
                {
                    if ((&entry_CanIf_RxIndication[entry_count])->CanIfCanRxPduHrhRef->CanIfSoftwareFilterHrh)
                    {
                        //if ((&entry_CanIf_RxIndication[entry_count])->CanIfSoftwareFilterType == CANIF_SOFTFILTER_TYPE_MASK)
			#if (CANIF_SOFTWARE_FILTER_TYPE == CANIF_SOFTFILTER_TYPE_MASK)
                    	//{
                            if ((CanId & (&entry_CanIf_RxIndication[entry_count])->CanIfCanRxPduCanIdMask ) ==
                                    ( (&entry_CanIf_RxIndication[entry_count])->CanIfCanRxPduCanId & (&entry_CanIf_RxIndication[entry_count])->CanIfCanRxPduCanIdMask))
                            {
                                /* We found a pdu so call higher layers */
                            }
                            else
                            {
                              /*  entry_CanIf_RxIndication++; */
                                ++entry_count;
                                cont=(uint8)1;
                                /* continue; */
                                /* Go to next entry */
                            }
                       // }

							#else
                        {
                            DET_REPORTERROR(MODULE_ID_CAN, 0, CANIF_RXINDICATION_ID, CANIF_E_PARAM_HRH);
                            cont = (uint8)1;
                            /* continue; */
                            /* Not a supported filter type, so just drop the frame */
					#endif
                    }
                }
                if(cont==(uint8)0)
                {


#if (CANIF_DLC_CHECK == STD_ON)
                    if (CanDlc < (&entry_CanIf_RxIndication[entry_count])->CanIfCanRxPduDlc)
                    {
                        VALIDATE_NO_RV((uint8)FALSE, CANIF_RXINDICATION_ID, CANIF_E_PARAM_DLC);
                        check_t = (uint8) 1;
                        /* return; */
                    }
#endif

                    if(check_t == (uint8) 0)
                    {
                       // switch ((&entry_CanIf_RxIndication[entry_count])->CanIfRxUserType)
                    	switch (CanIF_RxPDUCbkConfig_a[entry_CanIf_RxIndication->CanIfRxPduCallBackInd].CanIfRxUserType)
                    	{
                        case CANIF_USER_TYPE_CAN_SPECIAL:
                        {
                            ( (CanIf_FuncTypeCanSpecial)(CanIF_RxPDUCbkConfig_a[entry_CanIf_RxIndication->CanIfRxPduCallBackInd].CanIfUserRxIndication) )(
                                    (&entry_CanIf_RxIndication[entry_count])->CanIfCanRxPduHrhRef->CanIfCanControllerHrhIdRef,
                                    (&entry_CanIf_RxIndication[entry_count])->CanIfCanRxPduId,
                                    CanSduPtr,
                                    CanDlc,
                                    CanId);

                            check_t = (uint8) 1;
                            break;

                            /*   return; */
                        }

                        case CANIF_USER_TYPE_CAN_NM:
#if defined(USE_CANNM)
                            CanNm_RxIndication((&entry_CanIf_RxIndication[entry_count])->CanIfCanRxPduId,CanSduPtr);
                            check_t=1;
                            break;
                            /* return; */

#endif
                            break;

                        case CANIF_USER_TYPE_CAN_PDUR:
                            /* Send Can frame to PDU router */
#if defined(USE_PDUR)
                        {
                            PduInfoType pduInfo;
                            pduInfo.SduLength = CanDlc;
                            pduInfo.SduDataPtr = (uint8 *)CanSduPtr;
                            PduR_CanIfRxIndication((&entry_CanIf_RxIndication[entry_count])->CanIfCanRxPduId,&pduInfo);
                        }
                        check_t = 1;
                        break;
                        /* return; */
#endif
                        break;

                        case CANIF_USER_TYPE_CAN_TP:
                            /* Send Can frame to CAN TP */
#if defined(USE_CANTP)
                        {
                            PduInfoType CanTpRxPdu;
                            CanTpRxPdu.SduLength = CanDlc;
                            CanTpRxPdu.SduDataPtr = (uint8 *)CanSduPtr;
                            CanTp_RxIndication((&entry_CanIf_RxIndication[entry_count])->CanIfCanRxPduId, &CanTpRxPdu);
                        }
                        check_t = 1;
                        break;
                        /* return; */
#endif
                        break;
                        case CANIF_USER_TYPE_J1939TP:
                            /* Send Can frame to CAN TP */
#if defined(USE_J1939TP)
                        {
                            PduInfoType J1939TpRxPdu;
                            J1939TpRxPdu.SduLength = CanDlc;
                            J1939TpRxPdu.SduDataPtr = (uint8 *)CanSduPtr;
                            J1939Tp_RxIndication((&entry_CanIf_RxIndication[entry_count])->CanIfCanRxPduId, &J1939TpRxPdu);
                        }
                        check_t = 1;
                        break;
                        /*  return; */
#endif
                        break;
                        default:
                        {
                            break;
                        }
                        }
                    }
                }
            }
                if((check_t==(uint8)0)&&(cont == (uint8)0))
                {
                 /*   entry_CanIf_RxIndication++; */
                    ++entry_count;
                }


        }

    }
        /* Did not find the PDU, something is wrong */
        if(check_t==(uint8)0)
         {
            VALIDATE_NO_RV((uint8)FALSE, CANIF_RXINDICATION_ID, CANIF_E_PARAM_LPDU);
        }
    return ;
}

//void CanIf_RxIndication( const Can_HwType* Mailbox,const PduInfoType* PduInfoPtr){
  //  CanIf_RxIndication_main(Mailbox->Hrh , Mailbox->CanId ,PduInfoPtr->CanDlc ,  PduInfoPtr->CanSduPtr);
//}

#if ( CANIF_TRANSMIT_CANCELLATION == STD_ON )
void CanIf_CancelTxConfirmation(const Can_PduType *PduInfoPtr)
{
    VALIDATE(FALSE, CANIF_CANCELTXCONFIRMATION_ID, CANIF_E_NOK_NOSUPPORT);
    VALIDATE_NO_RV(CanIf_Global.initRun, CANIF_CANCELTXCONFIRMATION_ID, CANIF_E_UNINIT);
    VALIDATE_NO_RV(PduInfoPtr != NULL, CANIF_RXINDICATION_ID, CANIF_E_PARAM_POINTER);

    const CanIf_TxPduConfigType *entry =
            CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr;

    /* Not supported */

    /* Did not find the PDU, something is wrong */
    VALIDATE_NO_RV(FALSE, CANIF_TXCONFIRMATION_ID, CANIF_E_PARAM_LPDU);
}
#endif

/*void CanIf_ControllerBusOff(uint8 Controller)*/
//FUNC(void,CANIF_CODE)CanIf_ControllerBusOff(
//		/* (uint8 Controller) */
//
//		VAR(uint8, AUTOMATIC) Controller
//		)
//
//{
//	 /*B_W CanIf_Arc_ChannelIdType channel = 0xff;*/
//	    /* enumerated type mixed with another type */
//	    /* M_E   CanIf_Arc_ChannelIdType channel =(CanIf_Arc_ChannelIdType) 0xff */
//	    /*(MISRA-C:2004 5.7/A) No identifier name should be reused ("channel") */
//		VAR(CanIf_Arc_ChannelIdType,AUTOMATIC) channel_CanIf_ControllerBusOff =(CanIf_Arc_ChannelIdType) 0xff;
//	   /* CanIf_Arc_ChannelIdType channel_CanIf_ControllerBusOff =(CanIf_Arc_ChannelIdType) 0xff; */
//
//	    VALIDATE_NO_RV( CanIf_Global.initRun, CANIF_CONTROLLER_BUSOFF_ID, CANIF_E_UNINIT );
//	    /* M_E int i ;*/
//	    /*(MISRA-C:2004 5.7/A) No identifier name should be reused ("i") */
//	    /* (MISRA-C:2004 6.3/A) typedefs that indicate size and signedness should be used in place of the basic */
//	    VAR(sint32,AUTOMATIC) i_CanIf_ControllerBusOff;
//	   /* sint32 i_CanIf_ControllerBusOff ; */
//
//	    for( i_CanIf_ControllerBusOff =(sint32) 0; i_CanIf_ControllerBusOff <(sint32) CANIF_CHANNEL_CNT; i_CanIf_ControllerBusOff++)
//	    {
//	        if(CanIf_ConfigPtr->Arc_ChannelToControllerMap[i_CanIf_ControllerBusOff] == Controller)
//	        {
//	            /* B_W channel = i; */
//	            /* enumerated type mixed with another type */
//	            channel_CanIf_ControllerBusOff = (CanIf_Arc_ChannelIdType) i_CanIf_ControllerBusOff;
//	        }
//	    }
//
//	    VALIDATE_NO_RV( Controller < CANIF_CHANNEL_CNT, CANIF_CONTROLLER_BUSOFF_ID, CANIF_E_PARAM_CONTROLLER );
//
//	    /* According to figure 35 in canif spec this should be done in */
//	    /* Can driver but it is better to do it here */
//	    CanIf_SetControllerMode(channel_CanIf_ControllerBusOff, CAN_CS_STOPPED);
//
//	    if (CanIf_DispatchConfigInstance.CanIfBusOffNotification != NULL)
//	    {
//	    	CanIf_DispatchConfigInstance.CanIfBusOffNotification(channel_CanIf_ControllerBusOff);
//	    }
//}
//
///*void CanIf_SetWakeupEvent(uint8 Controller) SWS_compiler*/
//FUNC(void,CANIF_CODE)CanIf_SetWakeupEvent(
//		/* (uint8 Controller) */
//		VAR(uint8, AUTOMATIC) Controller)
//
//
//{
//	VAR(CanIf_Arc_ChannelIdType,AUTOMATIC) channel_CanIf_SetWakeupEvent = (CanIf_Arc_ChannelIdType) 0xff;
//	   /* CanIf_Arc_ChannelIdType channel_CanIf_SetWakeupEvent = (CanIf_Arc_ChannelIdType) 0xff; */
//	    /* Misra error because VALIDATE_NO_RV expands to empty macro  */
//
//	    VALIDATE_NO_RV( CanIf_Global.initRun, CANIF_SETWAKEUPEVENT_ID, CANIF_E_UNINIT );
//	    /* M_E int i ;*/
//	    /*(MISRA-C:2004 5.7/A) No identifier name should be reused ("i") */
//	    /* (MISRA-C:2004 6.3/A) typedefs that indicate size and signedness should be used in place of the basic */
//	    VAR(sint32,AUTOMATIC) i_CanIf_SetWakeupEvent ;
//	   /* sint32 i_CanIf_SetWakeupEvent ; */
//
//	    for(i_CanIf_SetWakeupEvent =(sint32) 0; i_CanIf_SetWakeupEvent < (sint32)CANIF_CHANNEL_CNT; i_CanIf_SetWakeupEvent++)
//	    {
//	        if(CanIf_ConfigPtr->Arc_ChannelToControllerMap[i_CanIf_SetWakeupEvent] == Controller)
//	        {
//	            /* B_W channel = i; */
//	            /* enumerated type mixed with another type */
//	            channel_CanIf_SetWakeupEvent = (CanIf_Arc_ChannelIdType) i_CanIf_SetWakeupEvent;
//	        }
//	    }
//
//	    VALIDATE_NO_RV((uint8)FALSE, CANIF_SETWAKEUPEVENT_ID, CANIF_E_NOK_NOSUPPORT);
//	    VALIDATE_NO_RV( channel_CanIf_SetWakeupEvent < CANIF_CHANNEL_CNT, CANIF_SETWAKEUPEVENT_ID, CANIF_E_PARAM_CONTROLLER );
//
//	    /* Not supported */
//}

/*void CanIf_Arc_Error(uint8 Controller, Can_Arc_ErrorType Error)*/
//FUNC(void,CANIF_CODE)CanIf_Arc_Error(
//		/*(uint8 Controller, Can_Arc_ErrorType Error)*/
//		VAR(uint8, AUTOMATIC) Controller,
//		VAR(Can_Arc_ErrorType, AUTOMATIC) Error)
//
//{
//	VAR(CanIf_Arc_ChannelIdType,AUTOMATIC)  channel_CanIf_Arc_Error = (CanIf_Arc_ChannelIdType) 0xff;
//   /* CanIf_Arc_ChannelIdType channel_CanIf_Arc_Error = (CanIf_Arc_ChannelIdType) 0xff; */
//
//    VALIDATE_NO_RV( CanIf_Global.initRun, CANIF_ARCERROR_ID, CANIF_E_UNINIT );
//    /* M_E int i ;*/
//    /*(MISRA-C:2004 5.7/A) No identifier name should be reused ("i") */
//    /* (MISRA-C:2004 6.3/A) typedefs that indicate size and signedness should be used in place of the basic */
//    VAR(sint32,AUTOMATIC) i_CanIf_Arc_Error;
//   /* sint32 i_CanIf_Arc_Error ; */
//    for(i_CanIf_Arc_Error = (sint32) 0; i_CanIf_Arc_Error <(sint32) CANIF_CHANNEL_CNT; i_CanIf_Arc_Error++)
//    {
//        if(CanIf_ConfigPtr->Arc_ChannelToControllerMap[i_CanIf_Arc_Error] == Controller)
//        {
//            /* B_W channel = i; */
//            /* enumerated type mixed with another type */
//            channel_CanIf_Arc_Error = (CanIf_Arc_ChannelIdType) i_CanIf_Arc_Error;
//        }
//    }
//
//    VALIDATE_NO_RV( channel_CanIf_Arc_Error < CANIF_CHANNEL_CNT, CANIF_ARCERROR_ID, CANIF_E_PARAM_CONTROLLER );
//
//    if (CanIf_DispatchConfigInstance.CanIfErrorNotificaton != NULL)
//    {
//    	CanIf_DispatchConfigInstance.CanIfErrorNotificaton(Controller, Error);
//    }
//
//    /* Special fix for restart of bus incase of general can error i.e. connection to CanSM */
//    if (CanIf_DispatchConfigInstance.CanIfBusOffNotification != NULL)
//    {
//    	CanIf_DispatchConfigInstance.CanIfBusOffNotification(channel_CanIf_Arc_Error);
//    }
//}

/*uint8 CanIf_Arc_GetChannelDefaultConfIndex(CanIf_Arc_ChannelIdType Channel)*/
FUNC(uint8,CANIF_CODE)CanIf_Arc_GetChannelDefaultConfIndex(
		/* (CanIf_Arc_ChannelIdType Channel) */
		VAR(CanIf_Arc_ChannelIdType, AUTOMATIC) Channel)

{
	return CanIf_Config.Arc_ChannelDefaultConfIndex[Channel];
}
