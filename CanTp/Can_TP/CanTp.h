#ifndef CanTp_H_
#define CanTp_H_




#include "CanTp_Types.h"


#define MAX_SEGMENT_DATA_SIZE		8 		// Size of a CAN frame data bytes.


/* From Arch code */


#define ISO15765_TPCI_MASK      0x30
#define ISO15765_TPCI_SF        0x00  /* Single Frame */
#define ISO15765_TPCI_FF        0x10  /* First Frame */
#define ISO15765_TPCI_CF        0x20  /* Consecutive Frame */
#define ISO15765_TPCI_FC        0x30  /* Flow Control */
#define ISO15765_TPCI_DL        0x7   /* Single frame data length mask */
#define ISO1positio5765_TPCI_FS_MASK   0x0F  /* Flowcontrol status mask */

//------------------------------------------------------------------------------------------

#define ISO15765_TPCI_MASK      0x30
#define ISO15765_TPCI_SF        0x00  /* Single Frame */
#define ISO15765_TPCI_FF        0x10  /* First Frame */
#define ISO15765_TPCI_CF        0x20  /* Consecutive Frame */
#define ISO15765_TPCI_FC        0x30  /* Flow Control */
#define ISO15765_TPCI_DL        0x7   /* Single frame data length mask */
#define ISO15765_TPCI_FS_MASK   0x0F  /* Flowcontrol status mask */
#define CANTP_RXID_LIST_SIZE    8
#define CANTP_ERR                              -1
#define ISO15765_FLOW_CONTROL_STATUS_CTS        0
#define ISO15765_FLOW_CONTROL_STATUS_WAIT       1
#define ISO15765_FLOW_CONTROL_STATUS_OVFLW      2

//------------------------------------------------------------------------------------------


#define MAX_PAYLOAD_SF_STD_ADDR		7
#define MAX_PAYLOAD_SF_EXT_ADDR		6

#define MAX_PAYLOAD_FF_STD_ADDR		6
#define MAX_PAYLOAD_FF_EXT_ADDR		5

#define MAX_PAYLOAD_CF_STD_ADDR		7
#define MAX_PAYLOAD_CF_EXT_ADDR		6


//------------------------------------------------------------------------------------------
#define SEGMENT_NUMBER_MASK			0x0f



#define TIMER_DECREMENT(timer) \
		if (timer > 0) { \
			timer = timer - 1; \
		} \

#define COUNT_DECREMENT(count) \
		if (count > 0) { \
			count = count - 1; \
		} \


//------------------------------------------------------------------------------------------


typedef enum {
	INVALID_FRAME, /* Not specified by ISO15765 - used as error return type when decoding frame. */
	SINGLE_FRAME,
	FIRST_FRAME,
	CONSECUTIVE_FRAME,
	FLOW_CONTROL_CTS_FRAME, 								/* Clear to send */
	FLOW_CONTROL_WAIT_FRAME,
	FLOW_CONTROL_OVERFLOW_FRAME
} ISO15765FrameType;




typedef enum
{
	UNINITIALIZED,
	IDLE,
	SF_OR_FF_RECEIVED_WAITING_PDUR_BUFFER,
	RX_WAIT_CONSECUTIVE_FRAME,
	RX_WAIT_SDU_BUFFER,

	TX_WAIT_STMIN,       /* waits stmin */
	TX_WAIT_TRANSMIT,
	TX_WAIT_FLOW_CONTROL,
	TX_WAIT_TX_CONFIRMATION
} ISO15765TransferStateTypes;


typedef struct
{
	uint8 data[MAX_SEGMENT_DATA_SIZE];
	PduLengthType byteCount;
} CanIfSduType;


typedef struct {
	uint16 nextFlowControlCount; 		 // Count down to next Flow Control.
	uint16 framesHandledCount;			 // Counter keeping track total frames handled.
	uint32 stateTimeoutCount; 			 // Counter for timeout.
	uint8 extendedAddress; 				 // Not always used but need to be available.
	uint8 STmin; 						 // In case we are transmitters the remote node can configure this value (only valid for TX).
	uint8 BS; 					   		 // Blocksize (only valid for TX).
	bool NasNarPending;
	uint32 NasNarTimeoutCount;			 // CanTpNas, CanTpNar.
	ISO15765TransferStateTypes state;
	// Transfer state machine. TODO: Can this be initialized here?
} ISO15765TransferControlType;


//	Container for TX or RX runtime paramters.

typedef struct
{
	ISO15765TransferControlType iso15765;
	PduInfoType *pdurBuffer;				// The PDUR make an instance of this.
	PduLengthType pdurBufferCount;  		// Number of bytes in PDUR buffer.
	PduLengthType transferTotal;	    	// Total length of the PDU.
	PduLengthType transferCount;			// Counter ongoing transfer.
	CanIfSduType canFrameBuffer;			// Temp storage of SDU data.   { data , ByteCount }
	CanTp_TransferInstanceMode mode;        // mode = { CANTP_RX_WAIT,CANTP_RX_PROCESSING,CANTP_TX_WAIT,CANTP_TX_PROCESSING }

} CanTp_ChannelPrivateType;


// Two initiate Functions ---------------------------------------------------------------------------

static void initTx15765RuntimeData(CanTp_ChannelPrivateType *txRuntimeParams)
{
	txRuntimeParams->iso15765.state = IDLE;
	txRuntimeParams->iso15765.NasNarPending = FALSE;
	txRuntimeParams->iso15765.framesHandledCount = 0;
	txRuntimeParams->iso15765.nextFlowControlCount = 0;
	txRuntimeParams->pdurBufferCount = 0;
	txRuntimeParams->transferTotal = 0;
	txRuntimeParams->transferCount = 0;
	txRuntimeParams->mode = CANTP_TX_WAIT;
	txRuntimeParams->pdurBuffer = NULL;
}

static void initRx15765RuntimeData(CanTp_ChannelPrivateType *rxRuntimeParams)
{

	rxRuntimeParams->iso15765.state = IDLE;
	rxRuntimeParams->iso15765.NasNarPending = FALSE;
	rxRuntimeParams->iso15765.framesHandledCount = 0;
	rxRuntimeParams->iso15765.nextFlowControlCount = 0;
	rxRuntimeParams->pdurBufferCount = 0;
	rxRuntimeParams->transferTotal = 0;
	rxRuntimeParams->transferCount = 0;
	rxRuntimeParams->mode = CANTP_RX_WAIT;
	rxRuntimeParams->pdurBuffer = NULL;
}




// - - - - - - - - - - - - - -

typedef struct
{
	bool initRun;
	CanTp_PaddingActivationType internalState;
	CanTp_ChannelPrivateType runtimeDataList[CANTP_NSDU_RUNTIME_LIST_SIZE];
} CanTp_RunTimeDataType;


CanTp_RunTimeDataType CanTpRunTimeData =			// Global object
{ 		.initRun = FALSE,
		.internalState = CANTP_OFF,
};



//prototypes of some functions used in sws .

/* This Function initate the global parameters of the CanTp Module and move the state to CanTp_ON if there is No Error */
void CanTp_Init( const CanTp_ConfigType* CfgPtr );


//void CanTp_GetVersionInfo( Std_VersionInfoType* versioninfo );



/* This Function move the state to CanTp_OFF*/
void CanTp_Shutdown( void );


Std_ReturnType CanTp_Transmit( PduIdType TxPduId, const PduInfoType* PduInfoPtr );

////////////////////////////////////////////////////////

// all of the following functions can't be found in the reference code of the company in the .h files

Std_ReturnType CanTp_CancelTransmit( PduIdType TxPduId );  // this one wasn't in the refrence file of the company

Std_ReturnType CanTp_CancelReceive( PduIdType RxPduId ); // also this one

Std_ReturnType CanTp_ChangeParameter( PduIdType id, TPParameterType parameter, uint16 value ); // and this

Std_ReturnType CanTp_ReadParameter( PduIdType id, TPParameterType parameter, uint16* value );

void CanTp_MainFunction( void );

///////////////////////////////////////Helper Functions not in sws/////////////////////////////////////////////////////////////////

static void handleConsecutiveFrame(const CanTp_RxNSduType *rxConfig,CanTp_ChannelPrivateType *rxRuntime, const PduInfoType *rxPduData);
static void handleFlowControlFrame(const CanTp_TxNSduType *txConfig,CanTp_ChannelPrivateType *txRuntime, const PduInfoType *txPduData);
static void sendFlowControlFrame(const CanTp_RxNSduType *rxConfig, CanTp_ChannelPrivateType *rxRuntime, BufReq_ReturnType flowStatus);
void CanTp_RxIndication(PduIdType CanTpRxPduId,const PduInfoType *CanTpRxPduPtr);
static BufReq_ReturnType copySegmentToPduRRxBuffer(const CanTp_RxNSduType *rxConfig,CanTp_ChannelPrivateType *rxRuntime, uint8 *segment,PduLengthType segmentSize,PduLengthType *bytesWrittenSuccessfully);

/* this function coping data and length to Rx_runtime.canFrameBufferData if segementsize < MAX_SEGMENT_DATA_SIZE and return True if copying Done */
static bool copySegmentToLocalRxBuffer(CanTp_ChannelPrivateType *rxRuntime, uint8 *segment,PduLengthType segmentSize);

/* This Fuction is used to get the length of the PDU from N_PCI */
static PduLengthType getPduLength(const CanTp_AddressingFormatType *formatType,const ISO15765FrameType iso15765Frame, const PduInfoType *CanTpRxPduPtr);
static void handleSingleFrame(const CanTp_RxNSduType *rxConfig,CanTp_ChannelPrivateType *rxRuntime, const PduInfoType *rxPduData);







#endif
