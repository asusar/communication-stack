/*
 * PduR_cfg.h
 *
 *  Created on: Jun 24, 2019
 *      Author: lenovo
 */

#ifndef PDUR_CFG_H_
#define PDUR_CFG_H_


 #include"stdint.h"

// if value of any index equals 0 is not used
// it will not be accesed in the run time

 #define vcom  \
   55,\
   -1,\
   6,\
   8,\
   12

 #define com_type  \
   CanIF,\
   CanIF,\
   CanIF,\
   canTP

 #define com_real  \
   0,\
   8,\
   1,\
   3,\
   2

 #define vcantp_TXcopy_com   \
   20,\
   14


 #define rcantp_TXcopy_com   \
   0,\
   2

 #define vcantp_com_rx  \
   10,\
   0,\
   0,\
   14,\

 #define rcantp_com_rx  \
   1,\
   0,\
   0,\
   99,\

 #define vcanf_R  \
   33,\
   0,\
   10,\
   0,\
   0,\
   0,\
   0

 #define rcanf_R  \
   1,\
   0,\
   66,\
   0,\
   0,\
   0,\
   0


#endif /* PDUR_CFG_H_ */
