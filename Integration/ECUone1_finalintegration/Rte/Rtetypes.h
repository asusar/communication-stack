#ifndef RTETYPES_HEADER_H_
#define RTETYPES_HEADER_H_

#include "include/Std_Types.h"

typedef unsigned char Boolean ;
typedef unsigned short int	UnsignedInteger_8 ;
typedef signed short int SignedInteger_8 ;
typedef unsigned int UnsignedInteger_16 ;
typedef int SignedInteger_16 ;
typedef unsigned long int  UnsignedInteger_32 ;
typedef long int SignedInteger_32 ;
typedef unsigned long long UnsignedInteger_64 ;
typedef long long  SignedInteger_64 ;
typedef float Float ;


#define seatstatusleft  0
#define seatstatusright  1
#define controlheatleft  2
#define controlheatright  3


#define RTE_E_OK     (Std_ReturnType)0
#define RTE_E_NOT_OK (Std_ReturnType)1


#endif
