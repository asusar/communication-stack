/*
 * resource.h
 *
 *  Created on: Apr 12, 2018
 *      Author: Dell
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "AutoSARConfig.h"


typedef UBaseType_t ResourceType;
typedef void * ResourceHandle_t;

StatusType GetResource ( ResourceType ResID );
StatusType ReleaseResource ( ResourceType ResID );

#if NUMBER_OF_EXTENDEDTASK > 0

    #if TASK_1_NUMBER_OF_RES_IN_TASK == 0
        extern UBaseType_t ResourcesInTask_1;
    #endif
    #if TASK_1_NUMBER_OF_RES_IN_TASK == 1
        extern UBaseType_t ResourcesInTask_1[1];
    #endif
    #if TASK_1_NUMBER_OF_RES_IN_TASK == 2
        extern UBaseType_t ResourcesInTask_1[2];
    #endif
    #if TASK_1_NUMBER_OF_RES_IN_TASK == 3
        extern UBaseType_t ResourcesInTask_1[3];
    #endif
    #if TASK_1_NUMBER_OF_RES_IN_TASK == 4
        extern UBaseType_t ResourcesInTask_1[4];
    #endif
    #if TASK_1_NUMBER_OF_RES_IN_TASK == 5
        extern UBaseType_t ResourcesInTask_1[5];
    #endif
    #if TASK_1_NUMBER_OF_RES_IN_TASK == 6
        extern UBaseType_t ResourcesInTask_1[6];
    #endif
    #if TASK_1_NUMBER_OF_RES_IN_TASK == 7
        extern UBaseType_t ResourcesInTask_1[7];
    #endif
    #if TASK_1_NUMBER_OF_RES_IN_TASK == 8
        extern UBaseType_t ResourcesInTask_1[8];
    #endif
#if NUMBER_OF_EXTENDEDTASK >= 2
    #if TASK_2_NUMBER_OF_RES_IN_TASK == 0
        extern UBaseType_t *ResourcesInTask_2;
    #endif
    #if TASK_2_NUMBER_OF_RES_IN_TASK == 1
        extern UBaseType_t ResourcesInTask_2[1];
    #endif
    #if TASK_2_NUMBER_OF_RES_IN_TASK == 2
        extern UBaseType_t ResourcesInTask_2[2];
    #endif
    #if TASK_2_NUMBER_OF_RES_IN_TASK == 3
        extern UBaseType_t ResourcesInTask_2[3];
    #endif
    #if TASK_2_NUMBER_OF_RES_IN_TASK == 4
        extern UBaseType_t ResourcesInTask_2[4];
    #endif
    #if TASK_2_NUMBER_OF_RES_IN_TASK == 5
        extern UBaseType_t ResourcesInTask_2[5];
    #endif
    #if TASK_2_NUMBER_OF_RES_IN_TASK == 6
        extern UBaseType_t ResourcesInTask_2[6];
    #endif
    #if TASK_2_NUMBER_OF_RES_IN_TASK == 7
        extern UBaseType_t ResourcesInTask_2[7];
    #endif
    #if TASK_2_NUMBER_OF_RES_IN_TASK == 8
        extern UBaseType_t ResourcesInTask_2[8];
    #endif
#endif
#if NUMBER_OF_EXTENDEDTASK >= 3
    #if TASK_3_NUMBER_OF_RES_IN_TASK == 0
        extern UBaseType_t ResourcesInTask_3;
    #endif
    #if TASK_3_NUMBER_OF_RES_IN_TASK == 1
        extern UBaseType_t ResourcesInTask_3[1];
    #endif
    #if TASK_3_NUMBER_OF_RES_IN_TASK == 2
        extern UBaseType_t ResourcesInTask_3[2];
    #endif
    #if TASK_3_NUMBER_OF_RES_IN_TASK == 3
        extern UBaseType_t ResourcesInTask_3[3];
    #endif
    #if TASK_3_NUMBER_OF_RES_IN_TASK == 4
        extern UBaseType_t ResourcesInTask_3[4];
    #endif
    #if TASK_3_NUMBER_OF_RES_IN_TASK == 5
        extern UBaseType_t ResourcesInTask_3[5];
    #endif
    #if TASK_3_NUMBER_OF_RES_IN_TASK == 6
        extern UBaseType_t ResourcesInTask_3[6];
    #endif
    #if TASK_3_NUMBER_OF_RES_IN_TASK == 7
        extern UBaseType_t ResourcesInTask_3[7];
    #endif
    #if TASK_3_NUMBER_OF_RES_IN_TASK == 8
        extern UBaseType_t ResourcesInTask_3[8];
    #endif
#endif
#if NUMBER_OF_EXTENDEDTASK >= 4
    #if TASK_4_NUMBER_OF_RES_IN_TASK == 0
        extern UBaseType_t ResourcesInTask_4;
    #endif
    #if TASK_4_NUMBER_OF_RES_IN_TASK == 1
        extern UBaseType_t ResourcesInTask_4[1];
    #endif
    #if TASK_4_NUMBER_OF_RES_IN_TASK == 2
        extern UBaseType_t ResourcesInTask_4[2];
    #endif
    #if TASK_4_NUMBER_OF_RES_IN_TASK == 3
        extern UBaseType_t ResourcesInTask_4[3];
    #endif
    #if TASK_4_NUMBER_OF_RES_IN_TASK == 4
        extern UBaseType_t ResourcesInTask_4[4];
    #endif
    #if TASK_4_NUMBER_OF_RES_IN_TASK == 5
        extern UBaseType_t ResourcesInTask_4[5];
    #endif
    #if TASK_4_NUMBER_OF_RES_IN_TASK == 6
        extern UBaseType_t ResourcesInTask_4[6];
    #endif
    #if TASK_4_NUMBER_OF_RES_IN_TASK == 7
        extern UBaseType_t ResourcesInTask_4[7];
    #endif
    #if TASK_4_NUMBER_OF_RES_IN_TASK == 8
        extern UBaseType_t ResourcesInTask_4[8];
    #endif
#endif
#if NUMBER_OF_EXTENDEDTASK >= 5
    #if TASK_5_NUMBER_OF_RES_IN_TASK == 0
        extern UBaseType_t ResourcesInTask_5;
    #endif
    #if TASK_5_NUMBER_OF_RES_IN_TASK == 1
        extern UBaseType_t ResourcesInTask_5[1];
    #endif
    #if TASK_5_NUMBER_OF_RES_IN_TASK == 2
        extern UBaseType_t ResourcesInTask_5[2];
    #endif
    #if TASK_5_NUMBER_OF_RES_IN_TASK == 3
        extern UBaseType_t ResourcesInTask_5[3];
    #endif
    #if TASK_5_NUMBER_OF_RES_IN_TASK == 4
        extern UBaseType_t ResourcesInTask_5[4];
    #endif
    #if TASK_5_NUMBER_OF_RES_IN_TASK == 5
        extern UBaseType_t ResourcesInTask_5[5];
    #endif
    #if TASK_5_NUMBER_OF_RES_IN_TASK == 6
        extern UBaseType_t ResourcesInTask_5[6];
    #endif
    #if TASK_5_NUMBER_OF_RES_IN_TASK == 7
        extern UBaseType_t ResourcesInTask_5[7];
    #endif
    #if TASK_5_NUMBER_OF_RES_IN_TASK == 8
        extern UBaseType_t ResourcesInTask_5[8];
    #endif
#endif
#if NUMBER_OF_EXTENDEDTASK >= 6
    #if TASK_6_NUMBER_OF_RES_IN_TASK == 0
        extern UBaseType_t ResourcesInTask_6;
    #endif
    #if TASK_6_NUMBER_OF_RES_IN_TASK == 1
        extern UBaseType_t ResourcesInTask_6[1];
    #endif
    #if TASK_6_NUMBER_OF_RES_IN_TASK == 2
        extern UBaseType_t ResourcesInTask_6[2];
    #endif
    #if TASK_6_NUMBER_OF_RES_IN_TASK == 3
        extern UBaseType_t ResourcesInTask_6[3];
    #endif
    #if TASK_6_NUMBER_OF_RES_IN_TASK == 4
        extern UBaseType_t ResourcesInTask_6[4];
    #endif
    #if TASK_6_NUMBER_OF_RES_IN_TASK == 5
        extern UBaseType_t ResourcesInTask_6[5];
    #endif
    #if TASK_6_NUMBER_OF_RES_IN_TASK == 6
        extern UBaseType_t ResourcesInTask_6[6];
    #endif
    #if TASK_6_NUMBER_OF_RES_IN_TASK == 7
        extern UBaseType_t ResourcesInTask_6[7];
    #endif
    #if TASK_6_NUMBER_OF_RES_IN_TASK == 8
        extern UBaseType_t ResourcesInTask_6[8];
    #endif
#endif
#if NUMBER_OF_EXTENDEDTASK >= 7
    #if TASK_7_NUMBER_OF_RES_IN_TASK == 0
        extern UBaseType_t ResourcesInTask_7;
    #endif
    #if TASK_7_NUMBER_OF_RES_IN_TASK == 1
        extern UBaseType_t ResourcesInTask_7[1];
    #endif
    #if TASK_7_NUMBER_OF_RES_IN_TASK == 2
        extern UBaseType_t ResourcesInTask_7[2];
    #endif
    #if TASK_7_NUMBER_OF_RES_IN_TASK == 3
        extern UBaseType_t ResourcesInTask_7[3];
    #endif
    #if TASK_7_NUMBER_OF_RES_IN_TASK == 4
        extern UBaseType_t ResourcesInTask_7[4];
    #endif
    #if TASK_7_NUMBER_OF_RES_IN_TASK == 5
        extern UBaseType_t ResourcesInTask_7[5];
    #endif
    #if TASK_7_NUMBER_OF_RES_IN_TASK == 6
        extern UBaseType_t ResourcesInTask_7[6];
    #endif
    #if TASK_7_NUMBER_OF_RES_IN_TASK == 7
        extern UBaseType_t ResourcesInTask_7[7];
    #endif
    #if TASK_7_NUMBER_OF_RES_IN_TASK == 8
        extern UBaseType_t ResourcesInTask_7[8];
    #endif
#endif
#if NUMBER_OF_EXTENDEDTASK >= 8
    #if TASK_8_NUMBER_OF_RES_IN_TASK == 0
        extern UBaseType_t ResourcesInTask_8;
    #endif
    #if TASK_8_NUMBER_OF_RES_IN_TASK == 1
        extern UBaseType_t ResourcesInTask_8[1];
    #endif
    #if TASK_8_NUMBER_OF_RES_IN_TASK == 2
        extern UBaseType_t ResourcesInTask_8[2];
    #endif
    #if TASK_8_NUMBER_OF_RES_IN_TASK == 3
        extern UBaseType_t ResourcesInTask_8[3];
    #endif
    #if TASK_8_NUMBER_OF_RES_IN_TASK == 4
        extern UBaseType_t ResourcesInTask_8[4];
    #endif
    #if TASK_8_NUMBER_OF_RES_IN_TASK == 5
        extern UBaseType_t ResourcesInTask_8[5];
    #endif
    #if TASK_8_NUMBER_OF_RES_IN_TASK == 6
        extern UBaseType_t ResourcesInTask_8[6];
    #endif
    #if TASK_8_NUMBER_OF_RES_IN_TASK == 7
        extern UBaseType_t ResourcesInTask_8[7];
    #endif
    #if TASK_8_NUMBER_OF_RES_IN_TASK == 8
        extern UBaseType_t ResourcesInTask_8[8];
    #endif
#endif
#if NUMBER_OF_EXTENDEDTASK >= 9
    #if TASK_9_NUMBER_OF_RES_IN_TASK == 0
        extern UBaseType_t ResourcesInTask_9;
    #endif
    #if TASK_9_NUMBER_OF_RES_IN_TASK == 1
        extern UBaseType_t ResourcesInTask_9[1];
    #endif
    #if TASK_9_NUMBER_OF_RES_IN_TASK == 2
        extern UBaseType_t ResourcesInTask_9[2];
    #endif
    #if TASK_9_NUMBER_OF_RES_IN_TASK == 3
        extern UBaseType_t ResourcesInTask_9[3];
    #endif
    #if TASK_9_NUMBER_OF_RES_IN_TASK == 4
        extern UBaseType_t ResourcesInTask_9[4];
    #endif
    #if TASK_9_NUMBER_OF_RES_IN_TASK == 5
        extern UBaseType_t ResourcesInTask_9[5];
    #endif
    #if TASK_9_NUMBER_OF_RES_IN_TASK == 6
        extern UBaseType_t ResourcesInTask_9[6];
    #endif
    #if TASK_9_NUMBER_OF_RES_IN_TASK == 7
        extern UBaseType_t ResourcesInTask_9[7];
    #endif
    #if TASK_9_NUMBER_OF_RES_IN_TASK == 8
        extern UBaseType_t ResourcesInTask_9[8];
    #endif
#endif
#if NUMBER_OF_EXTENDEDTASK >= 10
    #if TASK_10_NUMBER_OF_RES_IN_TASK == 0
        extern UBaseType_t ResourcesInTask_10;
    #endif
    #if TASK_10_NUMBER_OF_RES_IN_TASK == 1
        extern UBaseType_t ResourcesInTask_10[1];
    #endif
    #if TASK_10_NUMBER_OF_RES_IN_TASK == 2
        extern UBaseType_t ResourcesInTask_10[2];
    #endif
    #if TASK_10_NUMBER_OF_RES_IN_TASK == 3
        extern UBaseType_t ResourcesInTask_10[3];
    #endif
    #if TASK_10_NUMBER_OF_RES_IN_TASK == 4
        extern UBaseType_t ResourcesInTask_10[4];
    #endif
    #if TASK_10_NUMBER_OF_RES_IN_TASK == 5
        extern UBaseType_t ResourcesInTask_10[5];
    #endif
    #if TASK_10_NUMBER_OF_RES_IN_TASK == 6
        extern UBaseType_t ResourcesInTask_10[6];
    #endif
    #if TASK_10_NUMBER_OF_RES_IN_TASK == 7
        extern UBaseType_t ResourcesInTask_10[7];
    #endif
    #if TASK_10_NUMBER_OF_RES_IN_TASK == 8
        extern UBaseType_t ResourcesInTask_10[8];
    #endif
#endif

#endif


#endif /* RESOURCE_H_ */
