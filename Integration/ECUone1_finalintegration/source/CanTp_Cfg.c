
/*
 * CanTp_Cfg.c
 *
 *  Created on: Mar 13, 2019
 *      Author: mohos
 */



#include "include/CanTp_Types.h"




 CanTp_NTaType  CanTp_NTa =
{
					 .CanTpNTa = 0,

};

 CanTp_NSaType  CanTp_NSa =
{
				     .CanTpNSa = 0,
};


 CanTp_NAeType  CanTpNAe =
{
					 .CanTpNAe = 0,

};


 CanTp_TxNPduType  CanTp_TxNPdu =
{
					.CanTpTxNPduConfirmationPduId = 0,
					// uint32 CanTpTxNPduRef;          // pointer
};


 const CanTp_TxFcNPduType  CanTp_TxFcNPdu =
{
					.CanTpTxFcNPduConfirmationPduId = 0,
					// uint16 CanTpRxFcNPduRef;  // pointer
};


 CanTp_RxFcNPduType  CanTp_RxFcNPdu =
{
		.CanTpRxFcNPduId = 0,
		// uint16 CanTpRxFcNPduRef;  // pointer

};




const CanTp_TxNSduType CanTp_TxNSdu[] =
{
		{
					.CanTpNas 			      = 				8,
					.CanTpNbs 				  = 				9,
					.CanTpNcs 				  = 				10,
					.CanTpTc			      = 				TRUE,
					.CanTpTxAddressingFormat  =  			    CANTP_STANDARD,
					.CanTpTxNSduId 			  =					0,
					.CanTpTxPaddingActivation = 				CANTP_OFF,
					.CanTpTxTaType 			  = 				CANTP_PHYSICAL,
					.CanTpTxChannel           =                 0,
					//CanTpTxNSduRef;       //pointer
					.CanTpTxNPdu 			  =					{
					             			                    .CanTpTxNPduConfirmationPduId = 0,
					             			                    // uint32 CanTpTxNPduRef;          // pointer
					                                            },
			     	.CanTpRxFcNPdu			  =				 	{
			     	              			   				 	 .CanTpRxFcNPduId = 0,
					                                            },

					.CanTpNTa				  = 				{
					         				                     .CanTpNTa = 0,

					         				},
					.CanTpNSa				  =					{
					         				                     .CanTpNSa = 0,
					         				},
					.CanTpNAe				  =			        {
					         				                     .CanTpNAe = 0,

					         				},
		},

		{
					.CanTpNas				  =					 8,
					.CanTpNbs 				  =					 9,
					.CanTpNcs 				  =					 10,
					.CanTpTc				  =					 TRUE,
					.CanTpNAe 			      = 				 {
					          			                        .CanTpNAe = 0,

					          			   },
					.CanTpTxAddressingFormat  =  				 CANTP_STANDARD,
					.CanTpTxNSduId            =					 1,
					.CanTpTxPaddingActivation =  				 CANTP_OFF,
					.CanTpTxTaType 			  =					 CANTP_PHYSICAL,
					.CanTpTxChannel            =                 1,
					//CanTpTxNSduRef;         //pointer
					.CanTpTxNPdu 			  = 			     {
					             			                     .CanTpTxNPduConfirmationPduId = 1,
					             			                     // uint32 CanTpTxNPduRef;          // pointer
					             			 },
			     	.CanTpRxFcNPdu 		      =				     {
	                                                                 .CanTpRxFcNPduId = 1,
	                                                             },
					.CanTpNTa 		          = 			     {
					          		                            .CanTpNTa = 0,

					          		       },
					.CanTpNSa			      = 			     {
					         			                         .CanTpNSa = 0,
					         			    },
		},

};




const CanTp_RxNSduType CanTp_RxNSdu[] =
{
		{
				//.CanTpRxNSdu				 = 				 0,    // why is this written here ??? do you have any idea ??
				.CanTpBs					 =				 10,
				.CanTpNar					 = 				10,
				.CanTpNbr					 = 				20,
				.CanTpNcr 					 = 				30,
				.CanTpRxAddressingFormat 	 = 				CANTP_STANDARD,    // THIS IS AN ENUMERATOR IT CAN HAVE ONE	OF THE FOLLOWING VALUES {CANTP_EXTENDED , CANTP_MIXED , CANTP_MIXED29BIT , CANTP_NORMALFIXED ,  CANTP_STANDARD}
				.CanTpRxNSduId 				 =			 	0,     //  id =0
				.CanTpRxPaddingActivation 	 =				CANTP_OFF,		 // THIS IS AN ENUMERATOR IT AN HAVE ONEOF THE FOLLOWING VALUES {CANTP_OFF, CANTP_ON}
				.CanTpRxChannel              =              2,
				.CanTpRxTaType				 =				CANTP_PHYSICAL,            // you can put either one of these values on the ENUM {CANTP_FUNCTIONAL, CANTP_PHYSICAL}
				.CanTpRxWftMax				 = 				5,
				.CanTpSTmin					 = 				TRUE,
				// .CanTpRxNSduRef 			 = 				TRUE,
		        .CanTpRxNPdu                 =              {
		                                                     .CanTpRxNPduId=0,          // id recived from canif =0
		                                                    },
				.CanTpTxFcNPdu				 =				{
				              			                    .CanTpTxFcNPduConfirmationPduId = 2,        // in case of receiving a Confirmation from canif by this id
				              			                    // uint16 CanTpRxFcNPduRef;  // pointer
				              			                    },
				.CanTpNTa 					 = 				{
				          				                     .CanTpNTa = 0,

				          				},
				.CanTpNSa					 = 				{
				         				                     .CanTpNSa = 0,
				         				},
				.CanTpNAe					 = 				{
				         				                     .CanTpNAe = 0,

				         				},

		},

		{
				//.CanTpRxNSdu 				=				 0,    // why is this written here ??? do you have any idea ??
				.CanTpBs 					= 				 20,
				.CanTpNar 					=				3,
				.CanTpNbr				    = 				4,
				.CanTpNcr					= 				6,
				.CanTpRxAddressingFormat    =  				CANTP_STANDARD,    // THIS IS AN ENUMERATOR IT CAN HAVE ONE	OF THE FOLLOWING VALUES {CANTP_EXTENDED , CANTP_MIXED , CANTP_MIXED29BIT , CANTP_NORMALFIXED ,  CANTP_STANDARD}
				.CanTpRxNSduId 				= 				1,
				.CanTpRxPaddingActivation   = 				CANTP_ON,		 // THIS IS AN ENUMERATOR IT AN HAVE ONEOF THE FOLLOWING VALUES {CANTP_OFF, CANTP_ON}
				.CanTpRxChannel             =               3,
				.CanTpRxTaType				= 				CANTP_PHYSICAL,            // you can put either one of these values on the ENUM {CANTP_FUNCTIONAL, CANTP_PHYSICAL}
				.CanTpRxWftMax				= 				5,
				.CanTpSTmin 				= 				TRUE,
				// .CanTpRxNSduRef 			=				TRUE,

				.CanTpRxNPdu                =              {
				                                            .CanTpRxNPduId=1,
				                                           },

				.CanTpTxFcNPdu 				=
				                                            {
                                                           .CanTpTxFcNPduConfirmationPduId = 3,
                                                        // uint16 CanTpRxFcNPduRef;  // pointer
				                                            },

				.CanTpNTa 					= 				{
				          				                     .CanTpNTa = 0,

				          				},
				.CanTpNSa 					= 				{
				          				                     .CanTpNSa = 0,
				          				},
				.CanTpNAe 					= 				{
				          				                     .CanTpNAe = 0,

				          				}

		}

};
















CanTp_ChannelType  CanTp_Channel =
{
				.CanTpChannelMode		 =			 CANTP_MODE_FULL_DUPLEX,  // it can also take this value (CANTP_MODE_HALF_DUPLEX)
//				.direction               =             ISO15765_RECEIVE,
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
			 .CanTpVersionInfoApi            = 				FALSE

};


/*This is only for Testing */

const CanTp_ConfigType CanTp_Config =
{
			.CanTpMainFunctionPeriod 		= 					5,
			.CanTpMaxChannelCnt     		= 					5,
//			.direction                       =                   1,
			.CanTpChannel             		=
			{
			     .CanTpChannelMode        =           CANTP_MODE_FULL_DUPLEX,  // it can also take this value (CANTP_MODE_HALF_DUPLEX)
//			     .direction               =             ISO15765_TRANSMIT,
			     .CanTpRxNSdu             =               CanTp_RxNSdu,
			     .CanTpTxNSdu             =               CanTp_TxNSdu,
			}

};
// - - - - - - - - - - - - - -



//
//CanTp_Type CanTp =
//{
//		.CanTpConfig   = 	  &CanTp_Config ,
//		.CanTp_General =      &CanTp_General,
//
//};
//

