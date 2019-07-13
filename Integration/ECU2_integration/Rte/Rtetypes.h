#ifndef RTETYPES_HEADER_H_
#define RTETYPES_HEADER_H_

#include "include/Std_Types.h"

typedef unsigned char Boolean ;
typedef unsigned char 	UnsignedInteger_8 ;
typedef signed char  SignedInteger_8 ;
typedef unsigned short UnsignedInteger_16 ;
typedef short SignedInteger_16 ;
typedef unsigned long  UnsignedInteger_32 ;
typedef long SignedInteger_32 ;
typedef unsigned long long UnsignedInteger_64 ;
typedef long long  SignedInteger_64 ;
typedef float Float ;
//typedef unsigned int Std_ReturnType ;


#define passengeronleft  0
#define passengeronright  1
#define heatleft  2
#define heatright  3


#define RTE_E_OK     (Std_ReturnType)0
#define RTE_E_NOT_OK (Std_ReturnType)1


#endif
