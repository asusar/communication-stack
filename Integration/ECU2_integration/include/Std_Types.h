#ifndef INCLUDES_STD_TYPES_H_
#define INCLUDES_STD_TYPES_H_
#include <stdbool.h>
#include <stdint.h>

typedef enum
{
        E_NOT_OK,
        E_OK
}Std_ReturnType;


#define NULL 0
#endif /* INCLUDES_STD_TYPES_H_ */


///////////////////////////////////////////////////////////////

#ifndef STD_TYPES_H
#define STD_TYPES_H

// Autosar include files....
// TODO: we haven't really defined the autosar types yet.
//       the standard types are uint8, etc.

#include "include/Platform_Types.h" // TODO: move


#ifndef 	NULL
//lint -esym(960,20.2) // PC-Lint LINT EXCEPTION
#define	NULL	0
#endif

//typedef uint8_t uint8;
//typedef uint16_t uint16;
//typedef uint32_t uint32;


/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#define HIGH        (1u)
#define LOW         (0u)

/* Boolean Data Type */
typedef unsigned char           boolean;
typedef unsigned char           uint8;          /*           0 .. 255             */
typedef unsigned short          uint16;         /*           0 .. 65535           */
typedef unsigned long           uint32;         /*           0 .. 4294967295      */
typedef signed char             sint8;          /*        -128 .. +127            */
typedef signed short            sint16;         /*      -32768 .. +32767          */
typedef signed long             sint32;         /* -2147483648 .. +2147483647     */
typedef signed long long        sint64;
typedef unsigned long long      uint64;         /*       0..18446744073709551615  */
typedef float                   float32;
typedef double                  float64;

#define NULL 0




typedef struct {
	// TODO: not done!!
	uint16 vendorID;
	uint16 moduleID;
	uint8  instanceID;

	uint8 sw_major_version;    /**< Vendor numbers */
	uint8 sw_minor_version;    /**< Vendor numbers */
	uint8 sw_patch_version;    /**< Vendor numbers */

	uint8 ar_major_version;    /**< Autosar spec. numbers */
	uint8 ar_minor_version;    /**< Autosar spec. numbers */
	uint8 ar_patch_version;    /**< Autosar spec. numbers */
} Std_VersionInfoType;

/** make compare number... #if version > 10203  ( 1.2.3 ) */
#define STD_GET_VERSION (_major,_minor,_patch) (_major * 10000 + _minor * 100 + _patch)

/** Create Std_VersionInfoType */
// PC-Lint Exception MISRA rule 19.12
//lint -save -esym(960,19.12)
#define STD_GET_VERSION_INFO(_vi,_module) \
	if(_vi != NULL) {\
		((_vi)->vendorID =  _module ## _VENDOR_ID);\
		((_vi)->moduleID = _module ## _MODULE_ID);\
		((_vi)->sw_major_version = _module ## _SW_MAJOR_VERSION);\
		((_vi)->sw_minor_version =  _module ## _SW_MINOR_VERSION);\
		((_vi)->sw_patch_version =  _module ## _SW_PATCH_VERSION);\
		((_vi)->ar_major_version =  _module ## _AR_MAJOR_VERSION);\
		((_vi)->ar_minor_version =  _module ## _AR_MINOR_VERSION);\
		((_vi)->ar_patch_version =  _module ## _AR_PATCH_VERSION);\
	}
//lint -restore

#ifndef MIN
#define MIN(_x,_y) (((_x) < (_y)) ? (_x) : (_y))
#endif
#ifndef MAX
#define MAX(_x,_y) (((_x) > (_y)) ? (_x) : (_y))
#endif


//typedef uint8 Std_ReturnType;


#define E_NO_DTC_AVAILABLE		(Std_ReturnType)2
#define E_SESSION_NOT_ALLOWED	(Std_ReturnType)4
#define E_PROTOCOL_NOT_ALLOWED	(Std_ReturnType)5
#define E_REQUEST_NOT_ACCEPTED	(Std_ReturnType)8
#define E_REQUEST_ENV_NOK		(Std_ReturnType)9
#define E_PENDING				(Std_ReturnType)10
#define E_COMPARE_KEY_FAILED	(Std_ReturnType)11
#define E_FORCE_RCRRP			(Std_ReturnType)12

#define STD_HIGH		0x01
#define STD_LOW			0x00

#define STD_ACTIVE		0x01
#define STD_IDLE		0x00

#define STD_ON			0x01
#define STD_OFF			0x00




#endif
