
 /*******************************************************
 *
 * File Name: ComStack_Types.h
 *
 * Author: AUTOSAR COM Team 
 * 
 * Date Created: 6 March 2019	
 * 
 * Version	: 01	
 * 
 ********************************************************/

#ifndef COMSTACK_TYPES_H_
#define COMSTACK_TYPES_H_


#include <stdint.h>
//#include "Std_Types.h"
#include "include/Com_Types.h"

/*typedef uint8_t bool;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
*/
//typedef void * RetryInfoType ;
typedef uint32 TPParameterType ;
typedef uint32 PduIdType ;
typedef uint32 PduLengthType ;

typedef enum
{
    BUFREQ_OK,                         //: success
    BUFREQ_E_NOT_OK,                   //: development error detected
    BUFREQ_E_BUSY,                     //: all buffers in use
    BUFREQ_E_OVFL                     // : requested buffer too large
}BufReq_ReturnType ;


typedef struct
{
         uint8 *           SduDataPtr;
         uint8 *           MetaDataPtr;
         PduLengthType     SduLength;
} PduInfoType;
typedef enum
{
	TP_DATACONF,
	TP_DATARETRY,
	TP_CONFPENDING,
	TP_NORETRY,
} TpDataStateType;

typedef struct
{
	TpDataStateType TpDataState;
	PduLengthType TxTpDataCnt;
} RetryInfoType;

typedef uint8 NotifResultType;

#define NTFRSLT_OK						0x00
#define NTFRSLT_E_NOT_OK				0x01
#define NTFRSLT_E_CANCELATION_NOT_OK	0x0C
#define NTFRSLT_E_WRONG_SN 				0x05
#define NTFRSLT_E_NO_BUFFER 			0x09


// TODO, more

typedef uint8 BusTrcvErrorType;


#define BUSTRCV_NO_ERROR	0x00
#define BUSBUSTRCV_E_ERROR	0x01


#define COMSTACKTYPE_AR_MINOR_VERSION		1
#define COMSTACKTYPE_AR_MAJOR_VERSION		0
#define COMSTACKTYPE_AR_PATCH_VERSION		0

typedef uint8 NetworkHandleType;

#endif /* COMSTACK_TYPES_H_ */

