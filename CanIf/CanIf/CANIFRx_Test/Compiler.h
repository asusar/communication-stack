
#ifndef COMPILER_H
#define COMPILER_H

/** \brief AUTOSAR compiler abstraction header - Spansion FCR4
 **
 ** This file contains compiler specific declarations for the
 ** platform Spansion FCR4 using the compiler IAR for ARM architectures
 **
 ** See "Specification of Compiler Abstraction"
 **
 ** Product: SW-MCAL40-DRV-FCR4
 **
 ** Copyright, © 2012, 2013 Spansion LLC
 **
 ** ALL RIGHTS RESERVED. No part of this publication may be copied and provided
 ** to any third party in any form or by any means, unless expressly agreed to
 ** in written form by Spansion. All trademarks used in this document are the
 ** property of their respective owners.
 **
 ** For further provisions please refer to the respective License Agreement.
*/


/*==================[inclusions]=============================================*/

#include "Compiler_Cfg.h" /* module specific memory and pointer classes */

/*==================[macros]=================================================*/

/*------------------[Autosar compiler vendor idenfitication]-----------------*/

#if (defined COMPILER_VENDOR_ID) /* to prevent double definition */
#error COMPILER_VENDOR_ID already defined
#endif /* if (defined COMPILER_VENDOR_ID) */

/** \brief Vendor ID of the dedicated implementation of this module */
#define COMPILER_VENDOR_ID 12U /* Fujitsu */

/*------------------[Autosar specification version]--------------------------*/

#if (defined COMPILER_AR_RELEASE_MAJOR_VERSION) /* to prevent double definition */
#error COMPILER_AR_RELEASE_MAJOR_VERSION already defined
#endif /* if (defined COMPILER_AR_RELEASE_MAJOR_VERSION) */

#define COMPILER_AR_RELEASE_MAJOR_VERSION 2U /** \brief major version number */

#if (defined COMPILER_AR_RELEASE_MINOR_VERSION) /* to prevent double definition */
#error COMPILER_AR_RELEASE_MINOR_VERSION already defined
#endif /* if (defined COMPILER_AR_RELEASE_MINOR_VERSION) */

#define COMPILER_AR_RELEASE_MINOR_VERSION 0U /** \brief minor version number */

#if (defined COMPILER_AR_RELEASE_REVISION_VERSION) /* to prevent double definition */
#error COMPILER_AR_RELEASE_REVISION_VERSION already defined
#endif /* if (defined COMPILER_AR_RELEASE_REVISION_VERSION) */

#define COMPILER_AR_RELEASE_REVISION_VERSION 1U /** \brief patch version number */

/*------------------[Autosar module software version]------------------------*/

#if (defined COMPILER_SW_MAJOR_VERSION) /* to prevent double definition */
#error COMPILER_SW_MAJOR_VERSION already defined
#endif /* if (defined COMPILER_SW_MAJOR_VERSION) */

#define COMPILER_SW_MAJOR_VERSION 1U /** \brief major version number */

#if (defined COMPILER_SW_MINOR_VERSION) /* to prevent double definition */
#error COMPILER_SW_MINOR_VERSION already defined
#endif /* if (defined COMPILER_SW_MINOR_VERSION) */

#define COMPILER_SW_MINOR_VERSION 0U /** \brief minor version number */

#if (defined COMPILER_SW_PATCH_VERSION) /* to prevent double definition */
#error COMPILER_SW_PATCH_VERSION already defined
#endif /* if (defined COMPILER_SW_PATCH_VERSION) */

#define COMPILER_SW_PATCH_VERSION 0U /** \brief patch version number */

/*------------------[compiler symbol]----------------------------------------*/

#if (defined COMPILER_SYMBOL_IAREWARM_C_FCR4) /* to prevent double definition */
#error COMPILER_SYMBOL_IAREWARM_C_FCR4 already defined
#endif /* if (defined COMPILER_SYMBOL_IAREWARM_C_FCR4) */

/** \brief compiler symbol for IAR Compiler for FCR4 */
#define COMPILER_SYMBOL_IAREWARM_C_FCR4 1U

/*------------------[storage classes]----------------------------------------*/

#if (defined AUTOMATIC) /* to prevent double definition */
#error AUTOMATIC already defined
#endif /* if (defined AUTOMATIC) */

/** \brief definition of an automatic memory class
 **
 ** To be used for local non static variables */
#define AUTOMATIC

#if (defined STATIC) /* to prevent double definition */
#error STATIC already defined
#endif /* if (defined STATIC) */

/** \brief abstraction of compiler keyword 'static
 **
 ** values: 'static' or empty */
#define STATIC static

#if (defined INLINE) /* to prevent double definition */
#error INLINE already defined
#endif /* if (defined INLINE) */

/** \brief abstraction of compiler keyword 'inline'
 **
 ** values: 'inline' or empty */
#define INLINE

#if (defined TYPEDEF) /* to prevent double definition */
#error TYPEDEF already defined
#endif /* if (defined TYPEDEF) */

/** \brief definition of TYPEDEF
 **
 ** values: empty */
#define TYPEDEF

/*------------------[null pointer constant]----------------------------------*/

#if (defined NULL_PTR) /* to prevent double definition */
#error NULL_PTR already defined
#endif /* if (defined NULL_PTR) */

/** \brief abstraction of the null pointer constant */
#define NULL_PTR ((P2VAR(void, AUTOMATIC, BASE_DATA)) 0)

/*------------------[macros for functions]-----------------------------------*/

#if (defined FUNC) /* to prevent double definition */
#error FUNC already defined
#endif /* if (defined FUNC) */

/** \brief abstraction for function declaration and definition
 **
 ** This macro abstracts the declaration and definition of functions
 ** and ensures the correct syntax of function declaration as
 ** required by the specific compiler.
 **
 ** \param[in] rettype return type of the function
 ** \param[in] memclass classification of the function itself */
#define FUNC(rettype, memclass) memclass rettype


#if (defined ISR_NATIVE) /* to prevent double definition */
#error ISR_NATIVE already defined
#endif /* if (defined ISR_NATIVE) */
/* SWS_compiler */


#if (defined FUNC_P2VAR) /* to prevent double definition */
#error FUNC_P2VAR already defined
#endif /* if (defined FUNC_P2VAR) */

#define FUNC_P2VAR(rettype, ptrclass, memclass) ptrclass rettype * memclass

#if (defined FUNC_P2CONST) /* to prevent double definition */
#error FUNC_P2CONST already defined
#endif /* if (defined FUNC_P2VAR) */

#define FUNC_P2CONST(rettype, ptrclass, memclass) const ptrclass rettype * memclass


#define ISR_NATIVE(x)     __irq void  x(void)

/*------------------[macros for pointers]------------------------------------*/

#if (defined P2VAR) /* to prevent double definition */
#error P2VAR already defined
#endif /* if (defined P2VAR) */

/** \brief abstraction for pointers in RAM pointing to RAM
 **
 ** This macro abstracts the declaration and definition of pointers
 ** in RAM pointing to variables in RAM.
 **
 ** The pointer itself is modifiable.
 ** The pointer's target is modifiable.
 **
 ** \param[in] ptrtype type of the referenced variable
 ** \param[in] memclass classification of the pointer's variable itself
 ** \param[in] defines the classification of the pointer's distance */
#define P2VAR(ptrtype, memclass, ptrclass) ptrclass ptrtype * memclass

#if (defined P2CONST) /* to prevent double definition */
#error P2CONST already defined
#endif /* if (defined P2CONST) */

/** \brief abstraction for pointers in RAM pointing to ROM
 **
 ** This macro abstracts the declaration and definition of pointers
 ** in RAM pointing to constants in ROM.
 **
 ** The pointer itself is modifiable.
 ** The pointer's target is not modifiable (read only).
 **
 ** \param[in] ptrtype type of the referenced constant
 ** \param[in] memclass classification of the pointer's variable itself
 ** \param[in] defines the classification of the pointer's distance */
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype ptrclass * memclass

#if (defined CONSTP2VAR) /* to prevent double definition */
#error CONSTP2VAR already defined
#endif /* if (defined CONSTP2VAR) */

/** \brief abstraction for pointers in ROM pointing to RAM
 **
 ** This macro abstracts the declaration and definition of pointers
 ** in ROM pointing to variables in RAM.
 **
 ** The pointer is not modifiable. (read only).
 ** The pointer's target is modifiable.
 **
 ** \param[in] ptrtype type of the referenced variable
 ** \param[in] memclass classification of the pointer's variable itself
 ** \param[in] defines the classification of the pointer's distance */
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrclass ptrtype * const memclass

#if (defined CONSTP2CONST) /* to prevent double definition */
#error CONSTP2CONST already defined
#endif /* if (defined CONSTP2CONST) */

/** \brief abstraction for pointers in ROM pointing to ROM
 **
 ** This macro abstracts the declaration and definition of pointers
 ** in ROM pointing to constants in ROM.
 **
 ** The pointer itself is not modifiable (read only).
 ** The pointer's target is not modifiable (read only).
 **
 ** \param[in] ptrtype type of the referenced constant
 ** \param[in] memclass classification of the pointer's variable itself
 ** \param[in] defines the classification of the pointer's distance */
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrclass ptrtype * const memclass

#if (defined P2FUNC) /* to prevent double definition */
#error P2FUNC already defined
#endif /* if (defined P2FUNC) */

/** \brief abstraction for declaration and definition of function pointers
 **
 ** This macro abstracts the declaration and definition of pointers
 ** to functions.
 **
 ** \param[in] rettype return type of the function
 ** \param[in] ptrclass defines the classification of the pointer's distance
 ** \param[in] function name respectively name of the defined type
 ** */
#define P2FUNC(rettype, ptrclass, fctname) rettype ptrclass (* fctname)

/*------------------[keywords for constants]---------------------------------*/

#if (defined CONST) /* to prevent double definition */
#error CONST already defined
#endif /* if (defined CONST) */

/** \brief abstraction for declaration and definition of constants
 **
 ** This macro abstracts the declaration and definition of constants.
 **
 ** \param[in] consttype type of the constant
 ** \param[in] memclass classification of the constant itself */
#define CONST(consttype, memclass) memclass const consttype

/*------------------[keywords for variables]---------------------------------*/

#if (defined VAR) /* to prevent double definition */
#error VAR already defined
#endif /* if (defined VAR) */

/** \brief abstraction for the declaration and definition of variables
 **
 ** This macro abstracts the declaration and definition of variables.
 **
 ** \param[in] vartype type of the variable
 ** \param[in] memclass classification of the variable itself */
#define VAR(vartype, memclass) memclass vartype

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

/** @} doxygen end group definition */
#endif /* if !defined( COMPILER_H ) */
/*==================[end of file]============================================*/
