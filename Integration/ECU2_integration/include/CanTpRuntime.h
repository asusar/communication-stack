#ifndef CanTpRuntime_H_
#define CanTpRuntime_H_

#include "CanTp_Types.h"
#include "CanTP_Cfg.h"
#include "Std_Types.h"


#define ISO15765_TPCI_MASK      		0x30
#define ISO15765_TPCI_SF        		0x00  		 /* Single Frame */
#define ISO15765_TPCI_FF        		0x10  		 /* First Frame */
#define ISO15765_TPCI_CF        		0x20  		 /* Consecutive Frame */
#define ISO15765_TPCI_FC        		0x30  		 /* Flow Control */
#define ISO15765_TPCI_DL        		0x7   		 /* Single frame data length mask */
#define ISO1positio5765_TPCI_FS_MASK    0x0F  		 /* FlowControl status mask */

//------------------------------------------------------------------------------------------

#define ISO15765_TPCI_FS_MASK   			   0x0F  /* FlowControl status mask */
//#define CANTP_RXID_LIST_SIZE  			    8
//#define CANTP_ERR                            -1
#define ISO15765_FLOW_CONTROL_STATUS_CTS        0
#define ISO15765_FLOW_CONTROL_STATUS_WAIT       1
#define ISO15765_FLOW_CONTROL_STATUS_OVFLW      2

//------------------------------------------------------------------------------------------


#define MAX_PAYLOAD_SF_STD_ADDR     7
#define MAX_PAYLOAD_SF_EXT_ADDR     6

#define MAX_PAYLOAD_FF_STD_ADDR     6
#define MAX_PAYLOAD_FF_EXT_ADDR     5

#define MAX_PAYLOAD_CF_STD_ADDR     7
#define MAX_PAYLOAD_CF_EXT_ADDR     6


//------------------------------------------------------------------------------------------
#define SEGMENT_NUMBER_MASK         0x0f



#define TIMER_DECREMENT(timer) \
        if (timer > 0) { \
            timer = timer - 1; \
        } \

#define COUNT_DECREMENT(count) \
        if (count > 0) { \
            count = count - 1; \
        } \

#define MAX_SEGMENT_DATA_SIZE       8       // Size of a CAN frame data bytes.


//------------------------------------------------------------------------------------------


typedef enum
{
    INVALID_FRAME, /* Not specified by ISO15765 - used as error return type when decoding frame. */
    SINGLE_FRAME,
    FIRST_FRAME,
    CONSECUTIVE_FRAME,
    FLOW_CONTROL_CTS_FRAME,                                 /* Clear to send */
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


typedef struct
{
    uint16 nextFlowControlCount;         // Count down to next Flow Control.
    uint16 framesHandledCount;           // Counter keeping track total frames handled.
    uint32 stateTimeoutCount;            // Counter for timeout.
    uint8 extendedAddress;               // Not always used but need to be available.
    uint8 STmin;                         // In case we are transmitters the remote node can configure this value (only valid for TX).
    uint8 BS;                            // Blocksize (only valid for TX).
    boolean NasNarPending;
    uint32 NasNarTimeoutCount;           // CanTpNas, CanTpNar.
    ISO15765TransferStateTypes state;
    // Transfer state machine. TODO: Can this be initialized here?
} ISO15765TransferControlType;


//  Container for TX or RX runtime paramters.

typedef struct
{
    ISO15765TransferControlType iso15765;
    PduInfoType pdurBuffer;                // The PDUR make an instance of this. { we edit it to be structure not a pointer }



    PduLengthType pdurBufferCount;          // Number of bytes in PDUR buffer.
    PduLengthType transferTotal;            // Total length of the PDU.
    PduLengthType transferCount;            // Counter ongoing transfer.
    PduLengthType availableDataSize;
    CanIfSduType canFrameBuffer;            // Temp storage of SDU data.   { data , ByteCount }
    CanTp_TransferInstanceMode mode;        // mode = { CANTP_RX_WAIT,CANTP_RX_PROCESSING,CANTP_TX_WAIT,CANTP_TX_PROCESSING }
    PduLengthType Buffersize;               // size of buffer in com module. (only for RX)

} CanTp_ChannelPrivateType;


typedef struct
{
    boolean initRun;
    CanTp_PaddingActivationType internalState;
    CanTp_ChannelPrivateType runtimeDataList[CANTP_NSDU_RUNTIME_LIST_SIZE];
} CanTp_RunTimeDataType;



/*********************************************************************************************************************************************/




#endif      /* CanTpRuntime_H_ */
