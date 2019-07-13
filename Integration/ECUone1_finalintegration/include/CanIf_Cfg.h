/*
 * CanIf_Cfg.h
 *
 *  Created on: Jun 23, 2019
 *      Author: leenovoz510
 */

#ifndef CANIF_CFG_H_
#define CANIF_CFG_H_


#define CANIF_CONTROLLER_ID_Controller_1    (CANIF_Channel_1)


typedef enum 
{
	CANIF_Channel_1,
    CANIF_Channel_2,
    CANIF_Channel_3,
	CANIF_CHANNEL_CNT
} CanIf_ChannelIdType;


//typedef enum {
//	CAN_ARC_HANDLE_TYPE_BASIC,
//	CAN_ARC_HANDLE_TYPE_FULL
//} Can_Arc_HohType;

typedef enum {
    CAN_TP ,
    CDD,
    CAN_NM,
    J1939TP,
    PDUR,
    XCP,
    J1939NM,
    CAN_TSYN
}CanIfRxPduUserRxConfirmationUL;

typedef enum{
    USE_PDUR,
    USE_TP
}User_RxIndication;

///* This Enum should exists in Can_Cfg.h */
//typedef enum {
//	HWObj_1 = 0,
//	HWObj_2,
//	HWObj_3,
//	HWObj_4,
//	HWObj_5,
//	NUM_OF_HRHS
//} Can_Arc_HRHType;
//
//typedef enum {
//    HWObj_6 = 0,
//    HWObj_7,
//    HWObj_8,
//    HWObj_9,
//    HWObj_10,
//    NUM_OF_HTHS
//} Can_Arc_HTHType;

//////////////////////////// already in can_cfg.h ///////////////////////////

// typedef enum {
//     DCAN1 = 0,
//     CAN_CTRL_1 = 0,
//     DCAN2 = 1,
//     CAN_CTRL_2 = 1,
//     DCAN3 = 2,
//     CAN_CTRL_3 = 2,
//     CAN_CONTROLLER_CNT = 3
// }CanControllerIdType;

typedef enum 
{
    BINARY,
    INDEX,
    LINEAR,
    TABLE,
    MASK
    
}SoftwareFilterType ;


typedef enum {
    CANIF_WAKEUP_SUPPORT_CONTROLLER,
    CANIF_WAKEUP_SUPPORT_NO_WAKEUP,
    CANIF_WAKEUP_SUPPORT_TRANSCEIVER
} CanIf_WakeupSupportType;

//typedef enum
//{
//    FALSE = 0,
//    TRUE
//
//}bool;

typedef enum {
    DYNAMIC,
    STATIC

} CanIfTxPduType;

typedef enum {
    HWObj_1,
    HWObj_2,
    HWObj_3,
    HWObj_4,
    HWObj_5,
    NUM_OF_HRHS
} Can_HRHType;


#endif /* CANIF_CFG_H_ */
