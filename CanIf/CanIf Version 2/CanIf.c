#include "include/CanIf.h"
#include "include/CanIf_Types.h"
#include "include/CanIf_Cfg.h"
#include "include/ComStack_types.h"
#include "include/Std_Types.h"
#include "include/Can_GeneralTypes.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "include/PduR.h"
#include "include/CanIf_CanTp.h"
#include "include/PduR_CanIf.h"


#if defined(USE_PDUR)
#include "PduR.h"
#endif

#if defined(USE_COM)
#include "Com.h"
#endif

#define CanIfPrivateSoftwareFilterType MASK
#define CanIfPrivateDataLengthCheck FALSE

uint8 canif_cantp_value [] =  {canIf_Cantp_rx};
uint8 canif_PduR_Value[]   =   {vcanf};
uint8 canif_Comfrimation_Value[] = {canIf_Comfrimation_Value} ;

CanIf_ConfigType *CanIf_ConfigPtr;

CanIfPrivateCfg *CanIfPrivateCfgInst;

//sint8 RxPdu_Index;

/* typedef struct
{
    Can_ControllerStateType  Controller_Mode;
    CanIf_PduModeType  PduMode;
}CanIf_ChannelPrivateType; //CanIf_ChannelModesType

typedef struct
{
    boolean initRun;
    CanIf_ChannelPrivateType channelData[CANIF_CHANNEL_CNT];
}CanIf_GlobalType;
 */

CanIf_GlobalType CanIf_Global;

/*Array with the size of amount of all the buffers to indicate how much of the buffer is full*/
//uint8 CanIf_Pdu_BufferIndex[NUM_OF_HTHS];


CanIfInitCfg CanIF_UnInitConfig = {0,0,0,0,0,NULL,NULL,NULL};
//CanIf_ConfigType*   Config_UnInit = {NULL,&CanIF_UnInitConfig,NULL,NULL};

CanIfRxPduCfg *CanIfRxPduCfg_Arr;

void CanIf_Init(const CanIf_ConfigType* ConfigPtr){
     CanIf_ConfigPtr = ConfigPtr;
     uint8 i = (uint8)0;

    for ( i = (uint8)0; i <  CANIF_CHANNEL_CNT; i++)
    {
        CanIf_Global.channelData[i].Controller_Mode = CAN_CS_STOPPED;
        CanIf_Global.channelData[i].PduMode = CANIF_OFFLINE;
    }

    CanIf_Global.initRun = (uint8)TRUE;

}

//void CanIf_UnInit(void)
//{
//    CanIf_ConfigPtr = &Config_UnInit;
//    uint8 i_UnInit ;
//    for ( i_UnInit = (uint8)0; i_UnInit <  CANIF_CHANNEL_CNT; i_UnInit++)
//    {
//        CanIf_Global.channelData[i_UnInit].Controller_Mode = CAN_CS_UNINIT;
//        CanIf_Global.channelData[i_UnInit].PduMode = CANIF_OFFLINE;
//    }
//    CanIf_Global.initRun = (uint8) FALSE;
//}


Std_ReturnType CanIf_SetPduMode(uint8 ControllerId, CanIf_PduModeType PduModeRequest){
    Std_ReturnType toRet;
    CanIf_ChannelIdType channel_CanIf_SetPduMode = (CanIf_ChannelIdType) ControllerId;
    //CanIf_PduModeType oldMode_CanIf_SetPduMode = CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode;
    if(CanIf_Global.initRun == 0){
        return E_NOT_OK;
    }
    if(channel_CanIf_SetPduMode >= CANIF_CHANNEL_CNT){
        return E_NOT_OK;
    }
    switch(PduModeRequest){
    case CANIF_OFFLINE:
        CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_OFFLINE;
        break;
    case CANIF_TX_OFFLINE:
        CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_TX_OFFLINE;
        break;
        //CANIF_TX_OFFLINE_ACTIVE transmit confirmation not supported
    case CANIF_ONLINE:
        CanIf_Global.channelData[channel_CanIf_SetPduMode].PduMode = CANIF_ONLINE;
        break;
    default:
        break;
    }
    toRet = E_OK;
    return toRet;
}

Std_ReturnType CanIf_GetPduMode(uint8 ControllerId, CanIf_PduModeType* PduModePtr){
    Std_ReturnType toRet;
    CanIf_ChannelIdType CanIf_GetPduMode_local = (CanIf_ChannelIdType)ControllerId;
    if(CanIf_Global.initRun == 0){
        return E_NOT_OK;
    }
    if(CanIf_GetPduMode_local >= CANIF_CHANNEL_CNT){
        return E_NOT_OK;
    }

    *PduModePtr = CanIf_Global.channelData[CanIf_GetPduMode_local].PduMode;

    toRet = E_OK;
    return toRet;
}

Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, Can_ControllerStateType ControllerMode){
    CanIf_ChannelIdType channel_CanIf_SetControllerMode = (CanIf_ChannelIdType) ControllerId;
    if(CanIf_Global.initRun == 0){
        return E_NOT_OK;
    }
    if(channel_CanIf_SetControllerMode >= CANIF_CHANNEL_CNT){
        return E_NOT_OK;
    }

    switch (ControllerMode){
            case CAN_CS_STARTED:
                CanIf_SetPduMode(channel_CanIf_SetControllerMode, CANIF_ONLINE);
                CanIf_Global.channelData[channel_CanIf_SetControllerMode].Controller_Mode = CAN_CS_STARTED;
                return Can_SetControllerMode(ControllerId, CAN_T_START);
            case CAN_CS_STOPPED:
                CanIf_SetPduMode(channel_CanIf_SetControllerMode, CANIF_OFFLINE);
                CanIf_Global.channelData[channel_CanIf_SetControllerMode].Controller_Mode = CAN_CS_STOPPED;
                return Can_SetControllerMode(ControllerId, CAN_T_STOP);
            case CAN_CS_UNINIT:
                //just fall through
                break;
            //case CAN_CS_SLEEP:
            default:
                break;
    }

       return E_OK;
 }

Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, Can_ControllerStateType* ControllerModePtr){
    Std_ReturnType toRet = E_OK;
    CanIf_ChannelIdType channel_CanIf_GetControllerMode = (CanIf_ChannelIdType) ControllerId;
    if(CanIf_Global.initRun == 0){
        return E_NOT_OK;
    }
    if(channel_CanIf_GetControllerMode >= CANIF_CHANNEL_CNT){
        return E_NOT_OK;
    }
    if(ControllerModePtr == NULL){
        return E_NOT_OK;
    }
    *ControllerModePtr = CanIf_Global.channelData[channel_CanIf_GetControllerMode].Controller_Mode;

    return toRet;
}

const CanIfTxPduCfg * CanIf_FindTxPduEntry(PduIdType TxPduId){
    if(TxPduId >= (PduIdType) CanIf_ConfigPtr->InitConfig->CanIfMaxTxPduCfg ){
        return (CanIfTxPduCfg *) NULL;
    }
    uint32 index,i ;
    for (i=0;i<CanIf_ConfigPtr->InitConfig->CanIfMaxTxPduCfg;i++){
        if (TxPduId == CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr->CanIfTxPduId ){
            index = i;
            break;
        }
    }
    return &CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr[index];
}

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr){
    Std_ReturnType toRet = E_OK;
    Can_PduType canPdu;
    const CanIfTxPduCfg * txEntry;
    Can_ControllerStateType csMode = (Can_ControllerStateType) 0;
    CanIf_PduModeType pduMode = (CanIf_PduModeType) 0;
    if(CanIf_Global.initRun == 0){
        return E_NOT_OK;
    }
    if(PduInfoPtr == 0){
        return E_NOT_OK;
    }
    txEntry = CanIf_FindTxPduEntry(TxPduId);
    if (txEntry == 0){
        return E_NOT_OK;
    }
    //CanIf_ChannelIdType channel_CanIf_Transmit = CanIf_ConfigPtr->InitConfig->CanIfHohConfigPtr->CanIfHthCfgPtr[txEntry->CanIfTxPduBufferRef->CanIfBufferHthRef->CanIfHthCanCtrlIdRef->CanIfCtrlId];
    //waiting to get controller id
    CanIf_ChannelIdType channel_CanIf_Transmit = (CanIf_ChannelIdType) txEntry->CanIfTxPduBufferRef->CanIfBufferHthRef->CanIfHthCanCtrlIdRef->CanIfCtrlId;
    if (CanIf_GetControllerMode(channel_CanIf_Transmit, &csMode) == E_NOT_OK){
        return E_NOT_OK;
    }
    if (csMode != CAN_CS_STARTED){
        return E_NOT_OK;
    }
    if (CanIf_GetPduMode(channel_CanIf_Transmit, &pduMode) == E_NOT_OK){
        return E_NOT_OK;
    }
    if (pduMode != CANIF_ONLINE){
        return E_NOT_OK;
    }
    //txEntry->CanIfTxPduBufferRef->CanIfBufferHthRef;
    canPdu.id = txEntry->CanIfTxPduCanId;
    //canPdu.length = txEntry->CanIfTxPduRef->SduLength;
    canPdu.length = PduInfoPtr->SduLength;
    canPdu.swPduHandle = TxPduId;
    //canPdu.sdu = txEntry->CanIfTxPduRef->SduDataPtr;
    canPdu.sdu = PduInfoPtr->SduDataPtr;
    //waiting to know who to get HTH id
    toRet= Can_Write(txEntry->CanIfTxPduBufferRef->CanIfBufferHthRef->CanIfHthIdSymRef->CanObjectId,&canPdu);
    return toRet;
}

CanIf_ChannelIdType CanIf_FindHrhChannel (Can_HRHType HRH)
{
    CanIfHrhCfg* HRHCfg;
    sint8 HRHCfg_Counter = 0;
    CanIf_ChannelIdType To_Return;
    uint8 check = 0;


    HRHCfg = CanIf_ConfigPtr->InitConfig->CanIfHohConfigPtr->CanIfHrhCfgPrt;
    uint8 len = sizeof(HRHCfg)/sizeof(HRHCfg[0]);

    do
    {
        if((HRHCfg[HRHCfg_Counter].CanIfHrhIdSymRef->HOH) == HRH)
        {
            check = 1;
            To_Return = HRHCfg[HRHCfg_Counter].CanIfHrhCanCtrlIdRef->CanIfCtrlId;
            //RxPdu_Index = HRHCfg_Counter;

        }
        HRHCfg_Counter++;

    }while((check==(uint8) 0) && HRHCfg_Counter<len);

    return To_Return;
}


sint8 CanIf_FindRxPduEntry(const Can_HwType* Mailbox){
     uint8 i ;
     sint8 to_return = -1;
     for(i=0;i< CanIf_ConfigPtr->InitConfig->CanIfMaxRxPduCfg;i++)
     {
         if (Mailbox->id == CanIf_ConfigPtr->InitConfig->CanIfRxPduConfigPtr[i].CanIfRxPduCanId){
             to_return = i;
             break;
         }
     }
     return to_return;

}


CanIfRxPduUserRxConfirmationUL Get_User_RxIndication_Name(sint8 i){
    CanIfRxPduUserRxConfirmationUL to_return = CanIf_ConfigPtr->InitConfig->CanIfRxPduConfigPtr[i].CanIfRxPduUserRxIndicationUL_i;
    return to_return;
}

void Get_User_RxIndication(CanIfRxPduUserRxConfirmationUL user,uint16 i){
    CanIfRxPduCfg_Arr = CanIf_ConfigPtr->InitConfig->CanIfRxPduConfigPtr;

    if (user == PDUR)
    {
        CanIfRxPduCfg_Arr[i].CanIfRxPduUserRxIndicationName = USE_PDUR;
    }

    else if (user == CAN_TP)
    {
        CanIfRxPduCfg_Arr[i].CanIfRxPduUserRxIndicationName = USE_TP;
    }

    //return &CanIfRxPduCfg_Arr[i]->CanIfRxPduUserRxIndicationName;
}

//void CanTp_CanIfRxIndication (uint16 CanTpId ,PduInfoType* TpPdu)
//{
//    UARTprintf("%d & %d", CanTpId, TpPdu);
//}

//void PduR_CanIfRxIndication (uint16 PduRId ,PduInfoType* PduR)
//{
//    uint8* data = PduR->SduDataPtr;
//
//    UARTprintf("%u , %d", PduRId, (data));
//}

void
CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType *PduInfoPtr)
{
    uint8 cont = 0;
    uint8 check_t = 0;
    CanIf_PduModeType mode_CanIf_RxIndication = (CanIf_PduModeType) 0;
    uint8 CanIfRxPduCfg_i;

    uint8 CanIfRxPduCfg_index = 0;
    CanIf_ChannelIdType channel_CanIf_RxIndication = (CanIf_ChannelIdType) CanIf_FindHrhChannel(Mailbox->hoh);

    sint8 RxPdu_Index = CanIf_FindRxPduEntry(Mailbox);

    CanIfPrivateCfg *CanIfPrivateCfgArr = &CanIfPrivateCfgInst;
    CanIfRxPduCfg* CanIfRxPduCfg_Arr = CanIf_ConfigPtr->InitConfig->CanIfRxPduConfigPtr;

    //CanIfRxPduCfg_index = CanIf_FindRxPduCfgIndex(Mailbox->controllerlId);

    if ((signed)channel_CanIf_RxIndication == -1)
   {
       check_t =(uint8)1;
   }

    while (check_t==(uint8)0)
    {
        if((CanIf_GetPduMode(channel_CanIf_RxIndication,&mode_CanIf_RxIndication))==E_OK)
        {
            if(((mode_CanIf_RxIndication == CANIF_OFFLINE) || (mode_CanIf_RxIndication == CANIF_TX_OFFLINE) ||
                    (mode_CanIf_RxIndication == CANIF_TX_OFFLINE_ACTIVE)))
            {
                {
                    check_t =(uint8)1;
                }
            }
        }
        for (CanIfRxPduCfg_i =(uint16) 0;(  (check_t==(uint8)0) && (CanIfRxPduCfg_i < (uint16)CanIf_ConfigPtr->InitConfig->CanIfMaxRxPduCfg) ); CanIfRxPduCfg_i++)
        {
            if(((&CanIfRxPduCfg_Arr[CanIfRxPduCfg_i])->CanIfRxPduHrhIdRef->CanIfHrhIdSymRef->CanHandleType) == BASIC)

            {
               //if((&CanIfPrivateCfgInst[CanIfRxPduCfg_i])->CanIfPrivateSoftwareFilterType == MASKTYPE)
                if(CanIfPrivateSoftwareFilterType == MASK)
                {
                    if ((Mailbox->id & (&CanIfRxPduCfg_Arr[CanIfRxPduCfg_i])->CanIfRxPduCanIdMask ) ==
                            ( (&CanIfRxPduCfg_Arr[CanIfRxPduCfg_i])->CanIfRxPduCanId & (&CanIfRxPduCfg_Arr[CanIfRxPduCfg_i])->CanIfRxPduCanIdMask))
                    {
                        cont = (uint8) 0;
                    }
                    else
                    {
                        cont=(uint8)1;
                    }
                }


         }
        if( cont == 0)
        {

   //if((&CanIfPrivateCfgInst[CanIfRxPduCfg_i])->CanIfPrivateDataLengthCheck == TRUE)
            if(CanIfPrivateDataLengthCheck  == TRUE)
            {//stated in the SWS
                if (PduInfoPtr->SduLength < (&CanIfRxPduCfg_Arr[RxPdu_Index])->CanIfRxPduDataLength)
                {

                    check_t = (uint8) 1;
                }
            }


                 CanIfRxPduUserRxConfirmationUL USER_NAME = Get_User_RxIndication_Name(RxPdu_Index);
                //Get_User_RxIndication(CanIfRxPduCfg_Arr[RxPdu_Index].CanIfRxPduUserRxIndicationUL_i, RxPdu_Index);

                switch(USER_NAME)
                {
                case CAN_TP:
                {
                    PduInfoType CanTpRxPdu;
                    CanTpRxPdu.SduLength = PduInfoPtr->SduLength;
                    CanTpRxPdu.SduDataPtr = (uint8 *)PduInfoPtr->SduDataPtr;
                    CanTp_RxIndication(canif_cantp_value[RxPdu_Index],&CanTpRxPdu);

                    check_t = 1;
                    break;
                }

                case PDUR:
                {

                    PduInfoType pduInfo;
                    pduInfo.SduLength = PduInfoPtr->SduLength;
                    pduInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
                    uint8 arr[8] = pduInfo.SduDataPtr;

                    PduR_CanIfRxIndication(canif_PduR_Value[RxPdu_Index],&pduInfo);

                    check_t = 1;
                    break;
                }

                }
           }
        }

    }

    check_t = (uint8)1;

}

void CanIf_TxConfirmation(PduIdType CanTxPduId){
    const CanIfTxPduCfg * txEntry;
    txEntry = CanIf_FindTxPduEntry(CanTxPduId);
    uint32 index,i ;
       for (i=0;i<CanIf_ConfigPtr->InitConfig->CanIfMaxTxPduCfg;i++){
           if (CanTxPduId == CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr->CanIfTxPduId ){
               index = i;
               break;
           }
       }

    switch(txEntry->CanIfTxPduUserTxConfirmationUL_i){
    case CAN_TP:
        //UARTprintf("canifffffff");

        CanTp_TxConfirmation(canif_Comfrimation_Value[index], E_OK);

        break;
    }
}




