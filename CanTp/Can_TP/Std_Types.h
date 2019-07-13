#ifndef Std_Types_H_
#define Std_Types_H_

#define TRUE   1
#define FALSE  0
#define NULL   0

typedef unsigned char           bool;
typedef unsigned char         	uint8;          /*           0 .. 255             */
typedef unsigned short        	uint16;         /*           0 .. 65535           */
typedef unsigned long         	uint32;         /*           0 .. 4294967295      */
typedef signed char           	sint8;          /*        -128 .. +127            */
typedef signed short          	sint16;         /*      -32768 .. +32767          */
typedef signed long           	sint32;         /* -2147483648 .. +2147483647     */
typedef signed long long      	sint64;
typedef unsigned long long    	uint64;         /*       0..18446744073709551615  */
typedef float                 	float32;
typedef double                	float64;
//typedef uint16 					PduIdType;        		  /*karim*/   Farag commented this line as it should be in CanTp_Types.h





typedef uint8 Std_ReturnType;            // (return bta3 el E_OK we ba2y el 7gat ele zayo) for more info go to 8.3.5 in SWS 4.3.1
typedef uint16 Std_VersionInfoType;     /* (lsa ht2kd an al pointer 2 bytes)  we will make sure of the size of the pointer; is it unint 16 or 32 or 8 ....ect */

#define E_OK 					(Std_ReturnType)0
#define E_NOT_OK 				(Std_ReturnType)1


#endif
