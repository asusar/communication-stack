
#ifndef CAN_H_
#define CAN_H_

#include "Modules.h"

#define CAN_VENDOR_ID			    VENDOR_ID_ARCCORE
#define CAN_MODULE_ID			    MODULE_ID_CAN
#define CAN_AR_MAJOR_VERSION	3
#define CAN_AR_MINOR_VERSION	1
#define CAN_AR_PATCH_VERSION	5

#define CAN_SW_MAJOR_VERSION	1
#define CAN_SW_MINOR_VERSION 	0
#define CAN_SW_PATCH_VERSION	0

#define CAN_E_PARAM_POINTER     0x01
#define CAN_E_PARAM_HANDLE     0x02
#define CAN_E_PARAM_DLC     	0x03
#define CAN_E_PARAM_CONTROLLER 0x04
// API service used without initialization
#define CAN_E_UNINIT           0x05
// Init transition for current mode
#define CAN_E_TRANSITION       0x06

#define CAN_E_DATALOST         0x07     /** @req 4.0.3/CAN395 */

/** @name Service id's */
//@{
#define CAN_INIT_SERVICE_ID                         0x00
#define CAN_MAINFUNCTION_WRITE_SERVICE_ID           0x01
#define CAN_INITCONTROLLER_SERVICE_ID               0x02
#define CAN_SETCONTROLLERMODE_SERVICE_ID            0x03
#define CAN_DISABLECONTROLLERINTERRUPTS_SERVICE_ID  0x04
#define CAN_ENABLECONTROLLERINTERRUPTS_SERVICE_ID   0x05
#define CAN_WRITE_SERVICE_ID                        0x06
#define CAN_GETVERSIONINFO_SERVICE_ID               0x07
#define CAN_MAINFUNCTION_READ_SERVICE_ID            0x08
#define CAN_MAINFUNCTION_BUSOFF_SERVICE_ID          0x09
#define CAN_MAINFUNCTION_WAKEUP_SERVICE_ID          0x0a
#define CAN_CBK_CHECKWAKEUP_SERVICE_ID              0x0b
//@}


#if defined(CFG_PPC)

/* HOH flags */
#define CAN_HOH_FIFO_MASK           (1UL<<0)
//#define CAN_HOH_EOL_MASK            (1<<9)

/* Controller flags */
#define CAN_CTRL_RX_PROCESSING_INTERRUPT        (1UL<<0)
#define CAN_CTRL_RX_PROCESSING_POLLING          0
#define CAN_CTRL_TX_PROCESSING_INTERRUPT        (1UL<<1)
#define CAN_CTRL_TX_PROCESSING_POLLING          0
#define CAN_CTRL_WAKEUP_PROCESSING_INTERRUPT    (1UL<<2)
#define CAN_CTRL_WAKEUP_PROCESSING_POLLING      0
#define CAN_CTRL_BUSOFF_PROCESSING_INTERRUPT    (1UL<<3)
#define CAN_CTRL_BUSOFF_PROCESSING_POLLING      0
#define CAN_CTRL_ACTIVATION                     (1UL<<4)

#define CAN_CTRL_LOOPBACK                       (1UL<<5)
#define CAN_CTRL_FIFO                           (1UL<<6)

#define CAN_CTRL_ERROR_PROCESSING_INTERRUPT    (1UL<<7)
#define CAN_CTRL_ERROR_PROCESSING_POLLING      0

#endif

#include "Std_Types.h"
#include "CanIf_Types.h"
#include "ComStack_Types.h"

//#include "Mcu.h" Commented1Avelabs

#define CFG_CAN_TEST
typedef struct {
	uint32 txSuccessCnt;
	uint32 rxSuccessCnt;
	uint32 txErrorCnt;
	uint32 rxErrorCnt;
	uint32 boffCnt;
	uint32 fifoOverflow;
	uint32 fifoWarning;
} Can_Arc_StatisticsType;


#if defined(CFG_CAN_TEST)
typedef struct {
	uint64_t mbMaskTx;
	uint64_t mbMaskRx;
} Can_TestType;
#endif

// uint16: if only Standard IDs are used
// uint32: if also Extended IDs are used
typedef uint32 Can_IdType;

/* Good things to know
 * L-PDU  - Link PDU
 *
 *
 */

typedef struct Can_PduType_s {
	// the CAN ID, 29 or 11-bit
	Can_IdType 	id;
	// Length, max 8 bytes
	uint8		length;
	// data ptr
	uint8 		*sdu;
	// private data for CanIf,just save and use for callback
	uint32   swPduHandle;
} Can_PduType;


typedef enum {
	CAN_T_START,
	CAN_T_STOP,
	CAN_T_SLEEP,
	CAN_T_WAKEUP
} Can_StateTransitionType;

typedef enum {
	CAN_OK,
	CAN_NOT_OK,
	CAN_BUSY
// 	CAN_WAKEUP,		// Removed in 3.0
} Can_ReturnType;

/* Error from  CAN controller */
typedef union {
     volatile uint32_t R;
     struct {
    	 volatile uint32_t:24;
         volatile uint32_t BIT1ERR:1;
         volatile uint32_t BIT0ERR:1;
         volatile uint32_t ACKERR:1;
         volatile uint32_t CRCERR:1;
         volatile uint32_t FRMERR:1;
         volatile uint32_t STFERR:1;
         volatile uint32_t TXWRN:1;
         volatile uint32_t RXWRN:1;
     } B;
 } Can_Arc_ErrorType;






 typedef enum {
      CAN_ARC_HANDLE_TYPE_BASIC,
      CAN_ARC_HANDLE_TYPE_FULL
  } Can_Arc_HohType;




#include "Can_Cfg.h"



typedef struct {

    VAR(uint8, AUTOMATIC) Hrh;
    VAR(Can_IdType, AUTOMATIC) CanId;

} Can_HwType;



#else
#include "Can_Cfg.h"

#endif /* defined(PPC) */

// Each controller has 32 hth's, so the division of 32 will give the
// controller.
#define GET_CANCONTROLLER(a) (a / HTH_DIVIDER)


void Can_Init( const Can_ConfigType *Config );
void Can_DeInit(void);

#if ( CAN_VERSION_INFO_API == STD_ON )
#define Can_GetVersionInfo(_vi) STD_GET_VERSION_INFO(_vi,CAN)
#endif

void Can_InitController( uint8 controller, const Can_ControllerConfigType *config);
Can_ReturnType Can_SetControllerMode( uint8 Controller, Can_StateTransitionType transition );
void Can_DisableControllerInterrupts( uint8 controller );
void Can_EnableControllerInterrupts( uint8 controller );
// Hth - for Flexcan, the hardware message box number... .We don't care


Can_ReturnType Can_Write( Can_Arc_HTHType hth, Can_PduType *pduInfo );

void Can_Cbk_CheckWakeup( uint8 controller );
void Can_MainFunction_Write( void );
void Can_MainFunction_Read( void );
void Can_MainFunction_BusOff( void );
void Can_MainFunction_Error( void );
void Can_MainFunction_Wakeup( void );

void Can_Arc_GetStatistics( uint8 controller, Can_Arc_StatisticsType * stat);
#if defined(CFG_CAN_TEST)
Can_TestType *Can_Arc_GetTestInfo( void  );
#endif


