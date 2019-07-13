/*
 * CanTp_Types.h
 *
 *  Created on: Mar 13, 2019
 *      Author: mohos
 */

/*
 *  This file contains structures that are described in ch.10 of AUTOSAR SWS V4.3.1
 */

#ifndef CANTP_TYPES_H_
#define CANTP_TYPES_H_


#include "Std_Types.h"
#include "ComStack_Types.h"


typedef uint8 NotifResultType;

#define NTFRSLT_OK						0x00
#define NTFRSLT_E_NOT_OK				0x01
#define NTFRSLT_E_CANCELATION_NOT_OK	0x0C
#define NTFRSLT_E_WRONG_SN 				0x05
#define NTFRSLT_E_NO_BUFFER 			0x09




/************************************************************************enums***************************************************************************/


//typedef enum {
//	ISO15765_TRANSMIT,
//	ISO15765_RECEIVE
//} CanTp_DirectionType;


typedef enum
{
	CANTP_EXTENDED,       //Extended addressing format

	CANTP_MIXED,          //Mixed 11 bit addressing format

	CANTP_MIXED29BIT,     //Mixed 29 bit addressing format

	CANTP_NORMALFIXED,    //Normal fixed addressing format

	CANTP_STANDARD        //Normal addressing format


}CanTp_AddressingFormatType;




//CanTp_PaddingActivationType was named CanTpSignalTypePaddingActivation

typedef enum
{

	CANTP_OFF,
	CANTP_ON

}CanTp_PaddingActivationType;







// CanTp_TaType  structure was named CanTpSignalTypeTaType

typedef enum
{
	CANTP_FUNCTIONAL,   		 //Functional request type
	CANTP_PHYSICAL      		 //Physical request type

}CanTp_TaType;






typedef enum
{
    CANTP_MODE_FULL_DUPLEX,      //Full duplex channel.
    CANTP_MODE_HALF_DUPLEX       //Half duplex channel.

}CanTp_ChannelModeType;


typedef enum
{
	CANTP_RX_WAIT,
	CANTP_RX_PROCESSING,
	CANTP_TX_WAIT,
	CANTP_TX_PROCESSING
} CanTp_TransferInstanceMode;



/*IN comstack.h */
//
//typedef enum
//{
//	BUFREQ_OK,
//	BUFREQ_NOT_OK,
//	BUFREQ_BUSY,
//	BUFREQ_OVFL
//} BufReq_ReturnType;

/*****************************************************************************structs***************************************************************************/






typedef struct
{

	boolean CanTpChangeParameterApi;			 // This parameter, if set to true, enables the CanTp_ChangeParameterRequest Api for this Module.
	boolean CanTpDevErrorDetect;		   		 // Switches the development error detection and notification on or off.
	boolean CanTpDynIdSupport ;		    	 // Enable support for dynamic ID handling via N-PDU MetaData.
	boolean CanTpFlexibleDataRateSupport ;      // Enable support for CAN FD frames.
	boolean CanTpGenericConnectionSupport;      // Enable support for the handling of generic connections using N-SDUs with MetaData. Requires CanTpDynIdSupport.
	uint8 CanTpPaddingByte;                  // Used for the initialization of unused bytes with a certain value
	boolean CanTpReadParameterApi;				 // This parameter, if set to true, enables the CanTp_ReadParameterApi for this module.
	boolean CanTpVersionInfoApi;                // The function CanTp_GetVersionInfo is configurable (On/Off) by this configuration parameter.

}CanTp_GeneralType;



// CanTpTxNPdu_Type structure was named  CanTpSignalTypeNPdu_Type

typedef struct
{
	uint16 CanTpTxNPduConfirmationPduId;
	//const uint32 CanTpTxNPduRef;          // pointer
} CanTp_TxNPduType;




typedef struct
{
	uint16 CanTpTxFcNPduConfirmationPduId;
	//const uint16 CanTpRxFcNPduRef;  // pointer
}CanTp_TxFcNPduType;

typedef struct
{
	uint16 CanTpRxFcNPduId;
	//const uint16 CanTpRxFcNPduRef;  // pointer
}CanTp_RxFcNPduType;



typedef struct
{
	uint16 CanTpRxNPduId;
	//const uint16 CanTpRxNPduRef;  // pointer
 }CanTp_RxNPduType;



typedef struct
{
					uint8 CanTpNTa;

}CanTp_NTaType;




typedef struct
{
					uint8 CanTpNSa;

}CanTp_NSaType;




typedef struct
{
	uint8 CanTpNAe;

}CanTp_NAeType;






typedef struct
{
					const float64 CanTpNas;											// Value in second of the N_As timeout. N_As is the time for transmission of a CAN frame (any N_PDU) on the part of the sender.
					const float64 CanTpNbs;											// Value in seconds of the N_Bs timeout. N_Bs is the time of transmission until reception of the next Flow Control N_PDU.
					const float64 CanTpNcs;											// Value in seconds of the performance requirement of (N_Cs + N_As). N_Cs is the time in which CanTp is allowed to request the Tx data of a Consecutive Frame N_PDU.
					boolean CanTpTc;												// Switch for enabling Transmit Cancellation.
					CanTp_AddressingFormatType CanTpTxAddressingFormat;				// Declares which communication addressing format is supported for this TxNSdu.
					uint16 CanTpTxNSduId;											// Unique identifier to a structure that contains all useful information to process the transmission of a TxNsdu.
					const CanTp_PaddingActivationType CanTpTxPaddingActivation;		// Defines if the transmit frame use padding or not. This parameter is restricted to 8 byte N-PDUs. ( see sws for more info )
					CanTp_TaType CanTpTxTaType;										// Declares the communication type of this TxNsdu. ( see sws for more info page 88 )
					uint8 CanTpTxChannel; 											// Connection to runtime variable index. ( not included in sws )

					//	    CanTpTxNSduRef;         	//pointer					// Reference to a Pdu in the COM-Stack.

					const CanTp_TxNPduType CanTpTxNPdu;     						// Used for grouping of the ID of a PDU and the Reference to a PDU. This N-PDU produces a meta data item of type CAN_ID_32.
					CanTp_RxFcNPduType CanTpRxFcNPdu; 								// Used for grouping of the ID of a PDU and the Reference to a PDU. This N-PDU consumes a meta data item of type CAN_ID_32.
					CanTp_NTaType CanTpNTa;          								// This container is required for each RxNSdu and TxNSdu with RxTaType CANTP_PHYSICAL and CanTpAddressingFormat CANTP_EXTENDED.
					CanTp_NSaType CanTpNSa;          								// This container is required for each RxNSdu and TxNSdu with RxTaType CANTP_PHYSICAL and CanTpAddressingFormat CANTP_EXTENDED.
					CanTp_NAeType CanTpNAe;          								// This container is required for each RxNSdu and TxNSdu with AddressingFormat CANTP_MIXED or CANTP_MIXED29BIT.


}CanTp_TxNSduType;



typedef struct
{
						const uint8 CanTpBs;										// Sets the number of N-PDUs the CanTp receiver allows the sender to send, before waiting for an authorization to continue transmission of the following N-PDUs
						const float64 CanTpNar;										// Value in seconds of the N_Ar timeout. N_Ar is the time for transmission of a CAN frame (any N_PDU) on the receiver side.
						const float64 CanTpNbr;										// Value in seconds of the performance requirement for (N_Br + N_Ar). N_Br is the elapsed time between the receiving indication of a FF or CF , until the transmit request of the next FC.
						const float64 CanTpNcr;										// Value in seconds of the N_Cr timeout. N_Cr is the time until reception of the next Consecutive Frame N_PDU.
						CanTp_AddressingFormatType	CanTpRxAddressingFormat;		// Declares which communication addressing mode is supported for this RxNSdu. Definition of Enumeration values
						uint16 CanTpRxNSduId;	/*hnb3t dah ll com bs hnb3t al map bta3to   */									// Unique identifier user by the upper layer to call CanTp_CancelReceive, CanTp_ChangeParameter and CanTp_ReadParameter.
						const CanTp_PaddingActivationType CanTpRxPaddingActivation; // Defines if the receive frame uses padding or not. ( see sws for more info)
						CanTp_TaType CanTpRxTaType;									// Declares the communication type of this TxNsdu.
						uint8 CanTpRxChannel; 								// Connection to runtime variable index. ( not included in sws ) .
						const uint16 CanTpRxWftMax;									// This parameter indicates how many Flow Control wait N-PDUs can be consecutively transmitted by the receiver. It is local to the node and is not transmitted inside the FC protocol data unit.CanTpRxWftMax is used to avoid sender nodes being potentially hooked-up in case of a temporarily reception inability on the part of the receiver nodes, whereby the sender could be waiting continuously.
						const float64 CanTpSTmin;									// Sets the duration of the minimum time the CanTp sender shall wait between the transmissions of two CF N-PDUs.

					    //CanTpRxNSduRef;  // pointer								// Reference to a Pdu in the COM-Stack.

						CanTp_RxNPduType CanTpRxNPdu;   /*a7ot feh ay 7aga ana 3ayzha w mno ageb al index*/  							// Used for grouping of the ID of a PDU and the Reference to a PDU. This N-PDU consumes a meta data item of type CAN_ID_32.
						const CanTp_TxFcNPduType CanTpTxFcNPdu; 							// Used for grouping of the ID of a PDU and the Reference to a PDU. This N-PDU produces a meta data item of type CAN_ID_32.
						CanTp_NTaType CanTpNTa;           							// This container is required for each RxNSdu and TxNSdu with AddressingFormat CANTP_EXTENDED. When DynIdSupport is enabled, this container is also required for each RxNSdu with AddressingFormat CANTP_NORMALFIXED or CANTP_MIXED29BIT. When DynIdSupport is enabled and GenericConnectionSupport is not enabled, this container is also required for each TxNSdu with AddressingFormat CANTP_NORMALFIXED or CANTP_MIXED29BIT.
						CanTp_NSaType CanTpNSa;           							// This container is required for each RxNSdu and TxNSdu with RxTaType CANTP_PHYSICAL and CanTpAddressingFormat CANTP_EXTENDED. When DynIdSupport is enabled, this container is also required for each TxNSdu with AddressingFormat CANTP_NORMALFIXED or CANTP_MIXED29BIT. When DynIdSupport is enabled and GenericConnectionSupport is not enabled, this container is also required for each RxNSdu with AddressingFormat CANTP_NORMALFIXED or CANTP_MIXED29BIT.
						CanTp_NAeType CanTpNAe;           							// This container is required for each RxNSdu and TxNSdu with AddressingFormat CANTP_MIXED or CANTP_MIXED29BIT.


}CanTp_RxNSduType;





typedef struct
{

				const CanTp_ChannelModeType   CanTpChannelMode;		// The CAN Transport Layer supports half and full duplex channel modes.
//				const CanTp_DirectionType direction;			// Tx or Rx
				const CanTp_RxNSduType *CanTpRxNSdu;   			//Subcontainer
				const CanTp_TxNSduType *CanTpTxNSdu;   			//Subcontainer


}CanTp_ChannelType;











typedef struct
{

				float64 			    CanTpMainFunctionPeriod;
				uint64 					CanTpMaxChannelCnt;
//				uint8                        direction;
				const CanTp_ChannelType       CanTpChannel;

}CanTp_ConfigType;



typedef struct
{
			CanTp_ConfigType 		CanTpConfig;
			CanTp_GeneralType		CanTp_General;

}CanTp_Type;


CanTp_Type  CanTp;




////////////////////////////////////////////////////////////////////////////////



// the next lines of code should be  in CamStack_Types.h

//
//
//typedef uint16 			PduIdType;     /*karim*/
//typedef uint16 				PduLengthType;
//
//typedef float32 TPParameterType;
//
//
//
//typedef struct
//{
//	uint8 				*SduDataPtr;			// payload
//	PduLengthType 		SduLength;				// length of SDU
//} PduInfoType;






// some data type should be declared in this file.
/*

BufReq_ReturnType  ( OK )
PduIdType		   ( OK )
PduInfoType		   ( OK )
PduLengthType      ( OK )
RetryInfoType
TPParameterType    ( OK )

*/











#endif /* CANTP_TYPES_H_ */
