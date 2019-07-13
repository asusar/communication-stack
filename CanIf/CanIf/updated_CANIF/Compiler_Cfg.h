/*
 * Compiler_Cfg.h
 *
 *  Created on: Nov 14, 2017
 *      Author: Mina.Henry
 */

#ifndef COMPILER_CFG_H_
#define COMPILER_CFG_H_


/*================================== CANIF ===================================*/

/* Memory type to be used for code */
#define CANIF_CODE

/* Memory type to be used for Global or Static Constants */
#define CANIF_CONST

/* Memory type to be used for the reference on application data (expected to be
   in RAM or ROM) passed via API */
#define CANIF_APPL_DATA

/* Memory type to be used for the reference on application constants(expected
   to be certainly in ROM, for instance pointer of init function) passed via
   API */
#define CANIF_APPL_CONST

/* Memory type to be used for the reference on application functions (e.g. call
   back function pointers) */
#define CANIF_APPL_CODE

/* Memory type to be used for all global or static variables that are never
   initialized */
#define CANIF_VAR_NOINIT

/* Memory type to be used for all global or static variables that are
   initialized only after power on reset */
#define CANIF_VAR_POWER_ON_INIT

/* Memory type to be used for all global or static variables that have at least
   one of the following properties
   1. accessed bitwise
   2. frequently used
   3. High number of access in source code */
#define CANIF_VAR_FAST

/* Memory type to be used for all global or static variables that are
   initialized after every reset */
#define CANIF_VAR

#endif /* COMPILER_CFG_H_ */
