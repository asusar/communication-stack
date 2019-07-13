
/*
 * CanTp_Cfg.c
 *
 *  Created on: Mar 13, 2019
 *      Author: mohos
 */



#include "CanTp_Types.h"





const CanTp_NTaType  CanTp_NTa =
{
					 .CanTpNTa = 0,

};

const CanTp_NSaType  CanTp_NSa =
{
				     .CanTpNSa = 0,
};


const CanTp_NAeType  CanTpNAe =
{
					 .CanTpNAe = 0,

};


const CanTp_TxNPduType  CanTp_TxNPdu =
{
					.CanTpTxNPduConfirmationPduId = 0,
					//const uint32 CanTpTxNPduRef;          // pointer
};


const CanTp_TxFcNPduType  CanTp_TxFcNPdu =
{
					.CanTpTxFcNPduConfirmationPduId = 0,
					//const uint16 CanTpRxFcNPduRef;  // pointer
};


const CanTp_RxFcNPduType  CanTp_RxFcNPdu =
{
		.CanTpRxFcNPduId = 0,
		//const uint16 CanTpRxFcNPduRef;  // pointer

};




CanTp_TxNSduType CanTp_TxNSdu[] =
{
		{
					.CanTpNas 			      = 				0,
					.CanTpNbs 				  = 				0,
					.CanTpNcs 				  = 				0,
					.CanTpTc			      = 				FALSE,
					.CanTpTxAddressingFormat  =  			    CANTP_EXTENDED,
					.CanTpTxNSduId 			  =					0,
					.CanTpTxPaddingActivation = 				CANTP_ON,
					.CanTpTxTaType 			  = 				CANTP_PHYSICAL,
					.CanTpTxChannel           =                 2,
					//CanTpTxNSduRef;       //pointer
					.CanTpTxNPdu 			  =					CanTp_TxNPdu,
			//		.CanTpRxFcNPdu			  =				 	CanTp_RxFcNPdu,
					.CanTpNTa				  = 				CanTp_NTa,
					.CanTpNSa				  =					CanTp_NSa,
					.CanTpNAe				  =			        CanTpNAe,
		},

		{
					.CanTpNas				  =					 0,
					.CanTpNbs 				  =					 0,
					.CanTpNcs 				  =					 0,
					.CanTpTc				  =					 TRUE,
					.CanTpNAe 			      = 				 CanTpNAe,
					.CanTpTxAddressingFormat  =  				 CANTP_STANDARD,
					.CanTpTxNSduId            =					 0,
					.CanTpTxPaddingActivation =  				 CANTP_OFF,
					.CanTpTxTaType 			  =					 CANTP_PHYSICAL,
					.CanTpTxChannel            =                 1,
					//CanTpTxNSduRef;         //pointer
					.CanTpTxNPdu 			  = 			     CanTp_TxNPdu,
			//		.CanTpRxFcNPdu 		      =				     CanTp_TxFcNPdu,
					.CanTpNTa 		          = 			     CanTp_NTa,
					.CanTpNSa			      = 			     CanTp_NSa,
		},

};




CanTp_RxNSduType CanTp_RxNSdu[] =
{
		{
				//.CanTpRxNSdu				 = 				 0,    // why is this written here ??? do you have any idea ??
				.CanTpBs					 =				 0,
				.CanTpNar					 = 				FALSE,
				.CanTpNbr					 = 				FALSE,
				.CanTpNcr 					 = 				FALSE,
				.CanTpRxAddressingFormat 	 = 				CANTP_EXTENDED,    // THIS IS AN ENUMERATOR IT CAN HAVE ONE	OF THE FOLLOWING VALUES {CANTP_EXTENDED , CANTP_MIXED , CANTP_MIXED29BIT , CANTP_NORMALFIXED ,  CANTP_STANDARD}
				.CanTpRxNSduId 				 =			 	3,
				.CanTpRxPaddingActivation 	 =				CANTP_OFF,		 // THIS IS AN ENUMERATOR IT AN HAVE ONEOF THE FOLLOWING VALUES {CANTP_OFF, CANTP_ON}
				.CanTpRxChannel              =              2,
				.CanTpRxTaType				 =				CANTP_FUNCTIONAL,            // you can put either one of these values on the ENUM {CANTP_FUNCTIONAL, CANTP_PHYSICAL}
				.CanTpRxWftMax				 = 				5,
				.CanTpSTmin					 = 				TRUE,
				// .CanTpRxNSduRef 			 = 				TRUE,
		//		.CanTpRxNPdu 				 =				CanTp_RxNPdu,
				.CanTpTxFcNPdu				 =				CanTp_TxFcNPdu,
				.CanTpNTa 					 = 				CanTp_NTa,
				.CanTpNSa					 = 				CanTp_NSa,
				.CanTpNAe					 = 				CanTpNAe,

		},

		{
				//.CanTpRxNSdu 				=				 0,    // why is this written here ??? do you have any idea ??
				.CanTpBs 					= 				 0,
				.CanTpNar 					=				FALSE,
				.CanTpNbr				    = 				FALSE,
				.CanTpNcr					= 				FALSE,
				.CanTpRxAddressingFormat    =  				CANTP_EXTENDED,    // THIS IS AN ENUMERATOR IT CAN HAVE ONE	OF THE FOLLOWING VALUES {CANTP_EXTENDED , CANTP_MIXED , CANTP_MIXED29BIT , CANTP_NORMALFIXED ,  CANTP_STANDARD}
				.CanTpRxNSduId 				= 				3,
				.CanTpRxPaddingActivation   = 				CANTP_ON,		 // THIS IS AN ENUMERATOR IT AN HAVE ONEOF THE FOLLOWING VALUES {CANTP_OFF, CANTP_ON}
				.CanTpRxChannel             =               2,
				.CanTpRxTaType				= 				CANTP_PHYSICAL,            // you can put either one of these values on the ENUM {CANTP_FUNCTIONAL, CANTP_PHYSICAL}
				.CanTpRxWftMax				= 				5,
				.CanTpSTmin 				= 				TRUE,
				// .CanTpRxNSduRef 			=				TRUE,
		//		.CanTpRxNPdu				=				CanTp_TxNPdu,
				.CanTpTxFcNPdu 				=   			CanTp_TxFcNPdu,
				.CanTpNTa 					= 				CanTp_NTa,
				.CanTpNSa 					= 				CanTp_NSa,
				.CanTpNAe 					= 				CanTpNAe,

		}

};
















CanTp_ChannelType const CanTp_Channel =
{
				.CanTpChannelMode		 =			 CANTP_MODE_FULL_DUPLEX,  // it can also take this value (CANTP_MODE_HALF_DUPLEX)
				.direction               =             IS015765_TRANSMIT,
				.CanTpRxNSdu			 = 				 CanTp_RxNSdu,
				.CanTpTxNSdu			 = 				 CanTp_TxNSdu,
};









CanTp_GeneralType CanTp_General =
{
			 .CanTpChangeParameterApi        = 			    FALSE,
			 .CanTpDevErrorDetect            = 				FALSE,
			 .CanTpDynIdSupport 		     = 				FALSE,
			 .CanTpFlexibleDataRateSupport   =		        TRUE,
			 .CanTpGenericConnectionSupport  = 	        	FALSE,
			 .CanTpPaddingByte               = 				10,
			 .CanTpReadParameterApi          = 				FALSE,
			 .CanTpVersionInfoApi            = 				FALSE,

};


/*This is only for Testing */

CanTp_ConfigType CanTp_Config =
{
			.CanTpMainFunctionPeriod 		= 					1000,
			.CanTpMaxChannelCnt     		= 					5,
			.CanTpChannel             		= 					CanTp_Channel

};


//
//CanTp_Type CanTp =
//{
//		.CanTpConfig   = 	  &CanTp_Config ,
//		.CanTp_General =      &CanTp_General,
//
//};
//

