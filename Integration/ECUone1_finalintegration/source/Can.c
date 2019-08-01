#include "include/Can.h"
#include "include/CanIf_Cbk.h"
#pragma diag_push
#pragma CHECK_MISRA("none")
#include "include/PortingHW.h"
#include "Timer0A.h"

#pragma RESET_MISRA("all")

static void config_transmit_objects(void);
static inline const CanHardwareObject* Can_FindTxHoh(Can_HwHandleType hth);
static void Recieve_objects_config (void);
void Can0_InterruptHandler(void);
void Can1_InterruptHandler(void);



static uint8_t Int_enable_in_start_mode[NUM_OF_CAN_CONTROLLERS];
static uint8_t Int_disable_in_stop_mode[NUM_OF_CAN_CONTROLLERS];
static uint8_t state_transition_flag[2]={0U,0U};






/*[SWS_Can_00401] Several transmit hardware objects (defined by "CanHwObjectCount")
shall be assigned by one HTH to represent one transmit entity to the upper layer.*/



struct  Can_objectCheck Message_Confirmation[NUM_OF_HOH][Max_CanHwObjectCount];

/*[SWS_Can_00016] The Can module shall call CanIf_TxConfirmation to indicate a successful transmission.
It shall either called by the TX-interrupt service routine of the corresponding HW resource or inside the
Can_MainFunction_Write  in case of polling mode.*/

static Can_ControllerStateType Can_ControllerMode [NUM_OF_CAN_CONTROLLERS];

static uint8_t CanDevolpmentErrorType;

static uint8_t IntDisableCount[NUM_OF_CAN_CONTROLLERS];
static uint8_t IntEnableCount[NUM_OF_CAN_CONTROLLERS];

static Can_StateType CanUnitState = CAN_UNINIT ;



/*[SWS_Can_00103] After power-up/reset, the Can module shall be in the state
CAN_UNINIT.*/

/*All global data with read purpose only should be declared constant.[SRS_BSW_309] */

const Mcu_PerClockConfigType McuPerClockConfigData [NUM_OF_CAN_CONTROLLERS]= SYSCTL_PERIPH;
const Can_ConfigType MailboxCfg_MAP = hohMap;
const Can_ConfigType CanContainer= UserCANCfg;




 static void config_transmit_objects(void)
 {
 uint8_t controller0_transmitObjects_counter =0U;
 uint8_t controller1_transmitObjects_counter =0U;

 uint8_t index0;
 uint8_t index1;
 for (index0=0U;index0<NUM_OF_HOH;index0++)
 {
     if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index0].CanObjectType==transmit)
     {
         if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index0].CanControllerRef==&CanContainer.CanConfigSet
                 .CanController[0])
         {
             for(index1=0U;index1<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index0].CanHwObjectCount;index1++)
             {
                 controller0_transmitObjects_counter ++;
                 Message_Confirmation[index0][index1].mail_box=controller0_transmitObjects_counter;

             }
         }
         else{
             for(index1=0U;index1<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index0].CanHwObjectCount;index1++)
              {
                 controller1_transmitObjects_counter ++;
                 Message_Confirmation[index0][index1].mail_box=controller1_transmitObjects_counter;

              }
             }

     }else{
             /*MISRA*/
          }
   }
 }

static inline const CanHardwareObject* Can_FindTxHoh(Can_HwHandleType hth)
{
    const CanHardwareObject *MAP;
    MAP = &MailboxCfg_MAP.CanConfigSet.CanHardwareObject[hth];
    return MAP;

}
static void Recieve_objects_config (void)
{
/*This function configures message objects to be used for receiving data depending on your generated configuration
 from our tool*/

uint8_t index2,index3;
uint8_t controller0_receiveObjects_counter =32U;
uint8_t controller1_receiveObjects_counter =32U;
tCANMsgObject CANMessage;




      for(index2=0U;index2<NUM_OF_HOH;index2++)
    {
        if( MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index2].CanObjectType==receive)

        {
            if( MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index2].CanControllerRef==&CanContainer.CanConfigSet
                            .CanController[0])
          {
            for(index3=0U;index3<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index2].CanHwObjectCount;index3++)
            {

              Message_Confirmation[index2][index3].mail_box = controller0_receiveObjects_counter;
              CANMessage.ui32MsgID= MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index2].CanHwFilter.CanHwFilterCode;
              CANMessage.ui32MsgLen=8U;
              CANMessage.ui32MsgIDMask= MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index2].CanHwFilter.CanHwFilterMask;
              if(CanContainer.CanConfigSet.CanHardwareObject[index2].CanIdType==EXTENDED)
                {
                    CANMessage.ui32Flags =CANMessage.ui32Flags= MSG_OBJ_RX_INT_ENABLE| MSG_OBJ_USE_ID_FILTER|MSG_OBJ_EXTENDED_ID;
                }else{

                                CANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE|MSG_OBJ_USE_ID_FILTER;;
                     }


              CANMessageSet( MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index2].CanControllerRef->CanControllerBaseAddress,
                            controller0_receiveObjects_counter, &CANMessage, MSG_OBJ_TYPE_RX);

              /* clearing EOB bit for message object to protect data being received from being
                                       written on before CPU reads it*/

              CAN0_IF1MCTL_R &= ((uint32_t)(~(uint32_t)0x8U));/*MISRA violation*/
/*casting pointer to integral type unavoidable when addressing memory mapped registers
 or other hardware specific features.*/

              CAN0_IF1CRQ_R =controller0_receiveObjects_counter;/*MISRA violation*/
/*casting pointer to integral type unavoidable when addressing memory mapped registers
or other hardware specific features.*/


                  controller0_receiveObjects_counter--;
            }

        }  else{

                             for(index3=0U;index3< MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index2].CanHwObjectCount;index3++)
                             {
                               Message_Confirmation[index2][index3].mail_box = controller1_receiveObjects_counter;
                               CANMessage.ui32MsgID= MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index2].CanHwFilter.CanHwFilterCode;
                               CANMessage.ui32MsgLen=8U;
                               CANMessage.ui32MsgIDMask= MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index2].CanHwFilter.CanHwFilterMask;

                               /* clearing EOB bit for message object to protect data being received from being
                                written on before CPU reads it*/
                               if( MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index2].CanIdType==EXTENDED)
                                {
                                 CANMessage.ui32Flags =CANMessage.ui32Flags= MSG_OBJ_RX_INT_ENABLE| MSG_OBJ_USE_ID_FILTER|MSG_OBJ_EXTENDED_ID;
                                }else{

                                        CANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE|MSG_OBJ_USE_ID_FILTER;
                                     }

       CANMessageSet( MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index2].CanControllerRef->CanControllerBaseAddress,
                     controller1_receiveObjects_counter, &CANMessage, MSG_OBJ_TYPE_RX);

                               CAN1_IF1MCTL_R&=((uint32_t)(~(uint32_t)0x8U));/*MISRA violation*/
                               /*casting pointer to integral type unavoidable when addressing memory mapped registers
                                or other hardware specific features.*/
                               CAN1_IF1CRQ_R =controller1_receiveObjects_counter;/*MISRA violation*/
                               /*casting pointer to integral type unavoidable when addressing memory mapped registers
                                or other hardware specific features.*/

                                   controller1_receiveObjects_counter--;
      }
       }
  }else{}
 }
}
/*[SWS_Can_00031] The function Can_MainFunction_Write shall perform the polling of TX confirmation when CanTxProcessingis
set to POLLING or mixed. In case of mixed processing only the hardware objects for which CanHardwareObjectUsesPolling is set
 to TRUE shall be polled (SRS_BSW_00432, SRS_BSW_00373, SRS_SPAL_00157)*/


#if (CanTxProcessing0==POLLING || CanTxProcessing0==mixed ) ||   (CanTxProcessing1==POLLING || CanTxProcessing1==mixed )

void  Can_Main_Function_Write(void)
{
    uint8_t index4,index5;
    uint16_t POLLING_REGISTER;


       while(1)
       {
          CAN0_IF1CMSK_R&=((uint32_t)(~(uint32_t)0x80U));
          CAN1_IF1CMSK_R&=((uint32_t)(~(uint32_t)0x80U));
          /*MISRA violation*/
         /*casting pointer to integral type unavoidable when addressing memory mapped registers
          or other hardware specific features.*/
       for(index4=0U;index4< NUM_OF_HOH;index4++)
         {
               if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index4].CanObjectType==transmit)
               {
                   if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index4].CanControllerRef== &CanContainer.CanConfigSet
                           .CanController[0])
                   {
#if (CanTxProcessing0==POLLING || CanTxProcessing0==mixed )

#if  CanTxProcessing0==mixed
                  if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index4].CanHardwareObjectUsesPolling)
                  {
#endif

                     for(index5=0U;index5<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index4].CanHwObjectCount;index5++)
                                   {
                                      if(Message_Confirmation[index4][index5].Confirmation==un_confirmed)
                                      {
                                         CAN0_IF1CRQ_R=Message_Confirmation[index4][index5].mail_box;
                                         /*MISRA violation*/

                                         /*CanObjectId +j+1*/
                                         POLLING_REGISTER=((uint16_t)((uint16_t)CAN0_IF1MCTL_R));
                                         POLLING_REGISTER|=0xFEFFU;
                                         /*MISRA violation*/
                                         /*casting pointer to integral type unavoidable when addressing memory mapped
                                           registers or other hardware specific features.*/

                                    if(POLLING_REGISTER==0xFEFFU)/*Message_Confirmation[i][j]=un_confirmed*/
                                      {
                                        Message_Confirmation[index4][index5].Confirmation=confirmed;/*when it comes to poll again it wouldn't find
                                        it un_confirmed except when another transmission was requested again*/
                                        /*GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^0x04U;*/

                                         /*test only*/

                                       /* CanIf_TxConfirmation(Message_Confirmation[i][j].PduId)*/

                                      /*[SWS_Can_00016] ⌈The Can module shall call CanIf_TxConfirmation to indicate a
                                      successful transmission.It shall either called by the TX-interrupt service routine
                                      of the corresponding HW resource or inside the Can_MainFunction_Write in case of
                                      polling mode.*/


                                        /*7.8 Notification concept*/

                                        /*CanDrv must store the all in HTHs pending L-PDU Ids in an array
                                        organized perTH to avoid new search of the L-PDU ID for call of
                                       CanIf_TxConfirmation().*/
                                      } else{}
                                   }else{}
                                  }
#if  CanTxProcessing0==mixed
                                 }else{}
#endif
                              }
#endif
                            else
                                {
#if (CanTxProcessing1==POLLING || CanTxProcessing1==mixed )

#if  CanTxProcessing1==mixed
                  if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index4].CanHardwareObjectUsesPolling)
                  {
#endif
                                   for(index5=0U;index5<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index4].CanHwObjectCount;index5++)
                                     {
                                          if(Message_Confirmation[index4][index5].Confirmation==un_confirmed)
                                          {   /* must be checked herer*/
                                               CAN1_IF1CRQ_R=Message_Confirmation[index4][index5].mail_box;

                                               POLLING_REGISTER=((uint16_t)((uint16_t)CAN1_IF1MCTL_R));
                                               POLLING_REGISTER|=0xFEFFU;
                                               /*MISRA violation */


                                            if(POLLING_REGISTER==0xFEFFU)/*&&Message_Confirmation[i][j]=un_confirmed*/
                                             {

                                                 Message_Confirmation[index4][index5].Confirmation=confirmed;
                                                  /*when it comes to poll again it wouldn't findit un_confirmed except when
                                                    another transmission was requested again*/

                                                         /* CanIf_TxConfirmation(Message_Confirmation[i][j].PduId)*/

                                          /*[SWS_Can_00016] ⌈The Can module shall call CanIf_TxConfirmation to indicate a
                                          successful transmission.It shall either called by the TX-interrupt service routine
                                          of the corresponding HW resource or inside the Can_MainFunction_Write in case of
                                          polling mode.*/


                                                /*7.8 Notification concept*/

                                               /*CanDrv must store the all in HTHs pending L-PDU Ids in an array
                                                organized perTH to avoid new search of the L-PDU ID for call of
                                                CanIf_TxConfirmation().*/
                                          }
                                        else{}
                                   }else{}
                                 }
#if  CanTxProcessing1==mixed
                                 }else{}
#endif

#endif
        }
         /*[SWS_Can_00016]The Can module shall call CanIf_TxConfirmation to indicate a successful transmission.
         It shall either called by the TX-interrupt service routine of the corresponding HW resource or inside
         the Can_MainFunction_Write in case of polling mode.}*/

  }else{}
 }
    }
}

#endif


/*[SWS_Can_00108] The function Can_MainFunction_Read shall perform the polling of RX indications when CanRxProcessing
 is set to POLLING or mixed.In case of mixed processing only the hardware objects for which CanHardwareObjectUses
 Polling is set to TRUE shall be polled.(SRS_BSW_00432, SRS_SPAL_00157)*/

#if (CanRxProcessing0==POLLING || CanRxProcessing0==mixed ) ||   (CanRxProcessing1==POLLING || CanRxProcessing1==mixed )

void  Can_Main_Function_Read(void)
{
    uint8_t index6,index7;
    uint16_t POLLING_Register;
    tCANMsgObject received_CANMessage;
    uint8_t rx_MsgData0[8U];
    PduInfoType rx_PduInfo;
    Can_HwType Rx_Mailbox;
    received_CANMessage.pui8MsgData=rx_MsgData0;
/*    while(1)
        {*/
    CAN0_IF1CMSK_R&=((uint32_t)(~(uint32_t)0x80U));
    CAN1_IF1CMSK_R&=((uint32_t)(~(uint32_t)0x80U));

         for(index6=0U; index6< NUM_OF_HOH;index6++)
           {

                 if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index6].CanObjectType==receive)
                 {

                     if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index6].CanControllerRef==&CanContainer
                             .CanConfigSet.CanController[0])
                       {
#if (CanRxProcessing0==POLLING || CanRxProcessing0==mixed )

#if  CanRxProcessing0==mixed
                  if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index6].CanHardwareObjectUsesPolling)
                  {
#endif


                    for(index7=0U;index7<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index6].CanHwObjectCount;index7++)
                        {

                          CAN1_IF1CRQ_R=  Message_Confirmation[index6][index7].mail_box;
                          POLLING_Register=((uint16_t)((uint16_t)CAN0_IF1MCTL_R));
                          POLLING_Register|=0x7FFFU;
                            if( POLLING_Register==0xFFFFU)
                              {

                            /*[SWS_Can_00279] On L-PDU reception, the Can module shall call the RX indication callback
                             function CanIf_RxIndication with ID ,Hoh, abstract CanIf ControllerId in parameter Mailbox,
                             and the Data Lengthand pointer to the L-SDU buffer in parameter PduInfoPtr.*/

                                    CANMessageGet(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index6].
                                                  CanControllerRef->CanControllerBaseAddress,
                                                  Message_Confirmation[index6][index7].mail_box
                                                  , &received_CANMessage, 0U);
/*                                    UARTprintf("Msg ID=0x%08X len=%u data=0x",
                                               received_CANMessage.ui32MsgID, received_CANMessage.ui32MsgLen);*/

                                           UARTprintf("%02X \n",received_CANMessage.pui8MsgData[0]);

                                            Rx_Mailbox.hoh=index6 ;
                                            Rx_Mailbox.id= received_CANMessage.ui32MsgID ;
                                            Rx_Mailbox.controllerlId =MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index6]
                                                                     .CanControllerRef->CanControllerId;
                                            rx_PduInfo.SduLength  = received_CANMessage.ui32MsgLen;
                                            rx_PduInfo.SduDataptr = received_CANMessage.pui8MsgData;

                                            CanIf_RxIndication(&Rx_Mailbox,&rx_PduInfo);
                                        }
                                        else{}
                                     }
#if  CanRxProcessing0==mixed
                                 }else{}
#endif

#endif
      }
                     else{

  #if (CanRxProcessing1==POLLING || CanRxProcessing1==mixed )

  #if  CanRxProcessing1==mixed
                    if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index6].CanHardwareObjectUsesPolling)
                    {
  #endif

                                 for(index7=0U;index7<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index6].CanHwObjectCount;index7++)
                                     {

                                       CAN1_IF1CRQ_R=  Message_Confirmation[index6][index7].mail_box;
                                       POLLING_Register=((uint16_t)((uint16_t)CAN0_IF1MCTL_R));
                                       POLLING_Register|=0x7FFFU;
                                         if( POLLING_Register==0xFFFFU)
                                           {

                                         /*[SWS_Can_00279] On L-PDU reception, the Can module shall call the RX indication callback
                                          function CanIf_RxIndication with ID ,Hoh, abstract CanIf ControllerId in parameter Mailbox,
                                          and the Data Lengthand pointer to the L-SDU buffer in parameter PduInfoPtr.*/
                                                   PduInfoType received_PduInfo;
                                                 CANMessageGet(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index6].
                                                               CanControllerRef->CanControllerBaseAddress,
                                                               Message_Confirmation[index6][index7].mail_box
                                                               ,&received_CANMessage, 0U);
                                               UARTprintf("Msg ID=0x%08X len=%u data=0x",
                                                            received_CANMessage.ui32MsgID, received_CANMessage.ui32MsgLen);

                                                     UARTprintf("%02X \n",received_CANMessage.pui8MsgData[0]);

                                                      Rx_Mailbox.hoh=index6 ;
                                                      Rx_Mailbox.id= received_CANMessage.ui32MsgID ;
                                                      Rx_Mailbox.controllerlId =MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index6]
                                                                                  .CanControllerRef->CanControllerId;
                                                         received_PduInfo.SduLength  = received_CANMessage.ui32MsgLen;
                                                         received_PduInfo.SduDataptr = received_CANMessage.pui8MsgData;

                                                         /*CanIf_RxIndication(&Rx_Mailbox,&received_PduInfo);*/
                                                     } else{}

                                                  }

#if  CanRxProcessing0==mixed
                                 }else{}
#endif

#endif
           }
      }else{}

 }
 /*  }*/
}
#endif



void Can_MainFunction_Mode( void )
{

    /*[SWS_Can_00369]  The function Can_MainFunction_Mode shall implement the polling
        of CAN status register flags to detect transition of CAN Controller state. Compare to chapter 7.3.2.*/
 static   Can_ControllerStateType previous_state_0=CAN_CS_STOPPED;
 static   Can_ControllerStateType previous_state_1=CAN_CS_STOPPED;
 uint8_t Register_Check;

    while(1){
              /*while loop is eliminated for test only*/
        if(state_transition_flag[0])
        {
                if(Can_ControllerMode[0U]!=previous_state_0)

                {    state_transition_flag[0]=0U;
                    Register_Check=((uint8_t)((uint8_t)CAN0_CTL_R));
                      Register_Check&=1U;
                    if(Can_ControllerMode [0U]== CAN_CS_STARTED)
                    {
                        if(Register_Check==0U )
                     {/*void CanIf_ControllerModeIndication(0U,Can_ControllerMode [0U])*/
                       previous_state_0=Can_ControllerMode[0U];
                     }
                    else{}
                    }
                    else if(Can_ControllerMode [0U]== CAN_CS_STOPPED)
                    {
                        if(Register_Check==1U )
                         {/*void CanIf_ControllerModeIndication(0U,Can_ControllerMode [0U])*/
                           previous_state_0=Can_ControllerMode[0U];
                         }
                       else if(Can_ControllerMode [0U]== CAN_CS_SLEEP)
                       {

                            if(Register_Check==1U )
                          {
                                /*void CanIf_ControllerModeIndication(0U,Can_ControllerMode [0U])*/
                                 previous_state_0=Can_ControllerMode[0U];
                          }else{}
                       }else{}
                    }else{}

                }else{}
        }
    if(state_transition_flag[1])
     {
        if(Can_ControllerMode[1U]!=previous_state_1)
            {
                         state_transition_flag[1]=0U;
                         Register_Check=((uint8_t)((uint8_t)CAN1_CTL_R));
                         Register_Check&=1U;
                        if(Can_ControllerMode[1U]== CAN_CS_STARTED)
                        { /*[SWS_Can_00370] ⌈The function Can_Mainfunction_Mode shall poll a flag of the CAN status
                         register until the flag signals that the change takes effect and notify the upper layer with
                          function CanIf_ControllerModeIndicationabout a successful state transition referring to the
                           corresponding CAN controller with the abstract CanIf ControllerId.*/
                            if(Register_Check==0U)
                         {/*void CanIf_ControllerModeIndication(0U,Can_ControllerMode [1U])*/
                           previous_state_1=Can_ControllerMode[1U];
                         }else{}
                        }
                        else if(Can_ControllerMode [1U]== CAN_CS_STOPPED)
                        {
                            if(Register_Check==1U)
                             {
                                /*void CanIf_ControllerModeIndication(0U,Can_ControllerMode [1U])*/
                              /*[SWS_Can_00373] ⌈The function Can_Mainfunction_Mode shall call the function
                               CanIf_ControllerModeIndication to notify the upper layer about a successful state transition
                               of the corresponding CAN controller referred byabstract CanIf ControllerId in case the state
                                transition was triggered by function Can_SetControllerMode.*/
                               previous_state_1=Can_ControllerMode[1U];
                             }else{}
                             }
                              else if(Can_ControllerMode [1U]==CAN_CS_SLEEP)
                              {
                                       if(Register_Check==1U)
                                    {
                                     /*void CanIf_ControllerModeIndication(0U,Can_ControllerMode [0U])*/
                                       previous_state_1=Can_ControllerMode[1U];
                                    }else{}
                              }else{}
            }else{}

  }else{}


}

}
#if (CanBusoffProcessing0==POLLING || CanBusoffProcessing1==POLLING )
void Can_MainFunction_BusOff(void)
{
    uint32_t status;
    while(1)
    {
#if CanBusoffProcessing0==POLLING
        status= CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        status&=0x80U;
                if(status==CAN_STS_BOFF)
                {
                    Can_ControllerMode [0U]=CAN_CS_STOPPED;
                      /*CanIf_ControllerBusOff(0U)*/
                 }else{}
#endif
#if CanBusoffProcessing1==POLLING
                status= CANStatusGet(CAN1_BASE, CAN_STS_CONTROL);
                status&=0x80U;
                   if(status==CAN_STS_BOFF)
                      {
                       Can_ControllerMode [1U]=CAN_CS_STOPPED;
                                      /*CanIf_ControllerBusOff(1U)*/
                      }else{}
#endif
    }
}
#endif

Std_ReturnType Can_GetControllerErrorState( uint8_t ControllerId, Can_ErrorStateType* ErrorStatePtr )

{
   static Can_ErrorStateType  ErrorState[ NUM_OF_CAN_CONTROLLERS];
   uint8_t error_status;
 if(CanUnitState==CAN_UNINIT)
 {
     CanDevolpmentErrorType=CAN_E_UNINIT;
     return E_NOT_OK;/*justification*/
 }
 else{
         if(ControllerId >= NUM_OF_CAN_CONTROLLERS)
         {
               CanDevolpmentErrorType=CAN_E_PARAM_CONTROLLER;
               return E_NOT_OK;
         }
             else{
                   if(ErrorStatePtr==NULL)
                   {
                       CanDevolpmentErrorType=CAN_E_PARAM_POINTER;
                       return E_NOT_OK;
                   }
                   else{

                            if(ControllerId==0U)
                            {
                                error_status=CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
                                error_status&=0xE0U;

                               if(error_status==BOFF)
                               {
                                 *ErrorStatePtr=CAN_ERRORSTATE_BUSOFF;
                                 return E_OK;/*must be handled with os*/
                               }
                                else if(error_status==EWARN)
                                {
                                   *ErrorStatePtr= CAN_ERRORSTATE_ACTIVE;
                                   return E_OK;
                                }

                                 else if(error_status==EPASS)
                                     {
                                        *ErrorStatePtr=CAN_ERRORSTATE_PASSIVE;
                                        return E_OK;
                                     }
                               else
                               {

                               }

                            }
                         else if(ControllerId==1U)
                            {
                             error_status= CANStatusGet(CAN1_BASE, CAN_STS_CONTROL);
                             error_status&=0xE0U;
                                if(ErrorState[1U]==BOFF)
                                    {
                                      *ErrorStatePtr=CAN_ERRORSTATE_BUSOFF;
                                      return E_OK;

                                    }
                                    else if(ErrorState[1U]==EWARN)
                                     {
                                        *ErrorStatePtr=CAN_ERRORSTATE_PASSIVE;
                                         return E_OK;
                                     }

                                    else if( ErrorState[1U]==EPASS)
                                          {
                                             *ErrorStatePtr=CAN_ERRORSTATE_PASSIVE;
                                             return E_OK;
                                          }
                                    else{

                                        }
                               }else{}
             }
          }
     }
}

Std_ReturnType Can_Write(Can_HwHandleType HTH , Can_PduType* PduInfo)
{

    tCANMsgObject  sCANMessage;
    struct Can_objectCheck temp;
    uint8_t i;
    uint8_t j;
    uint32_t REGISTER_1;
    uint32_t REGISTER_2;
    Std_ReturnType return_value0;



   /* [SWS_Can_00100] Several TX hardware objects with unique HTHs may be configured. The
    CanIf module provides the HTH as parameter of the TX request.*/

    /*[SWS_Can_00276] The function Can_Write shall store the swPduHandle that is given
    inside the parameter PduInfo until the Can module calls the CanIf_TxConfirmation
    for this request where the swPduHandle is given as parameter.*/
  /*canTxPDUid_confirmation[pdu_id]=un_sent;*/
  if(CanUnitState==CAN_UNINIT)

  {
       /*[SWS_Can_00216] If development error detection for the Can module is enabled: The function
       Can_Write shall raise the error CAN_E_UNINIT and shall return E_NOT_OK if the driver is not yet initia_lized.*/
       CanDevolpmentErrorType=CAN_E_UNINIT;
       return E_NOT_OK;
  }
  else{
       const CanHardwareObject *hohobj = Can_FindTxHoh(HTH);

       if(hohobj->CanObjectType==receive)
       {
        /*[SWS_Can_00217] ⌈If development error detection for the Can module is enabled: The function Can_Write
        shall raise the errorCAN_E_PARAM_HANDLE and shall return E_NOT_OK if the parameter Hth is not a
        configured Hardware transmit Handle.*/
           CanDevolpmentErrorType=CAN_E_PARAM_HANDLE;
        return E_NOT_OK;
       }
      else{
            if(PduInfo==NULL)
            {

                /*[SWS_CAN_00219] ⌈If development error detection for CanDrv is enabled: Can_Write()
                  shall raise CAN_E_PARAM_POINTER and shall return E_NOT_OK if the parameter PduInfo
                  is a null pointer.*/
                  CanDevolpmentErrorType=CAN_E_PARAM_POINTER;
                return E_NOT_OK;

            }
            else{
                 if(PduInfo->sdu==NULL)
                 {
                   if(hohobj->CanTriggerTransmitEnable==FALSE)
                   {
                       /*[SWS_CAN_00505] ⌈If development error detection for CanDrv is enabled: Can_Write()
                        shall raise CAN_E_PARAM_POINTER and shall return E_NOT_OK if the trigger transmit
                        API is disabled for this hardware object (CanTriggertransmitEnable = FALSE) and
                        the SDU pointer inside PduInfo is a null pointer.*/
                       CanDevolpmentErrorType=CAN_E_PARAM_POINTER;
                       return E_NOT_OK;
                   }
                   else{

                       /*SWS_CAN_00504] If the trigger transmit API is enabled for the hardware object,
                       Can_Write() shall interpret a null pointer as SDU (Can_PduType.Can_SduPtrType = NULL)
                       as request for using the trigger transmit interface. If so and the hardware object is
                       free, Can_Write() shall call CanIf_Triggertransmit() with the maximum size
                       of the message buffer to acquire the PDU's data.*/
                       if(Message_Confirmation[HTH][0].Confirmation==confirmed)
                       {
                           /*CanIf_Triggertransmit(PduIdType TxPduId,PduInfoType* PduInfoPtr)*/
                           /*if(CanIf_Triggertransmit(PduIdType TxPduId,PduInfoType* PduInfoPtr)==E_NOT_OK.)
                           { return E_NOT_OK;}
                           [SWS_CAN_00506] Can_Write() shall return E_NOT_OK if the trigger transmit API
                           (CanIf_Triggertransmit()) returns E_NOT_OK.

                                    dependent on upper layer
                           else{

                               }*/
                       }
                       else{
                           return CAN_BUSY;
                          }
                 }
                }
                else{
                    if(PduInfo->length>8U)
                    {
                        CanDevolpmentErrorType=CAN_E_PARAM_DATA_LENGTH;
                         return  E_NOT_OK;
                     /*[SWS_Can_00218] ⌈The function Can_Write shall return E_NOT_OK and if development error detection
                      for the CAN module is enabled shall raise the error CAN_E_PARAM_DATA_LENGTH,
                      If the length is more than 8 byte*/
                    }
                    else
                    {
                      if(hohobj->CanHandleType==BASIC)
                      {
#if CanMultiplexedTransmission
                       /*sw flag is important here as when cancelling all pending temporary to do not disturb our logic
                         so we can depend on hardware to check message is pending or not*/
                      /*[SWS_Can_00402] ⌈The Can module shall support multiplexed transmission mechanisms*/
                      /*[SWS_Can_00403] ⌈The Can module shall support multiplexed transmission for devices,
                        which send L-PDUs in order of L-PDU priority.*/
                      for(i=0U;i<hohobj->CanHwObjectCount;i++)/*here i cancel all my transmission requests for this HOH to
                                                              protect my swapping logic from distotion*/
                       {
                          if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[i].CanControllerRef== &CanContainer.CanConfigSet
                                                                                        .CanController[0])
                         {
                          CAN0_IF1MCTL_R&=((uint32_t)(~(uint32_t)0x100U));
                          CAN0_IF1CMSK_R&=((uint32_t)(~(uint32_t)0x80U));
                          CAN0_IF1CRQ_R=Message_Confirmation[HTH][i].mail_box;
                         }else{
                                   CAN1_IF1MCTL_R&=((uint32_t)(~(uint32_t)0x100U));
                                   CAN1_IF1CMSK_R&=((uint32_t)(~(uint32_t)0x80U));
                                   CAN1_IF1CRQ_R=Message_Confirmation[HTH][i].mail_box;
                             }
                       }
#endif
#if CanMultiplexedTransmission
                            for(i=(hohobj->CanHwObjectCount-1U);i>=0U;i--)

#endif
#if !(CanMultiplexedTransmission)
                           for(i=0U;i<=(hohobj->CanHwObjectCount-1U);i++)
#endif
                           {
                                if(Message_Confirmation[HTH][i].Confirmation==confirmed)
                                {

#if CanMultiplexedTransmission
                                  if(i==(hohobj->CanHwObjectCount-1U))
                                {
#endif

                                      Message_Confirmation[HTH][i].Confirmation=un_confirmed;

                                            Message_Confirmation[HTH][i].PduId=PduInfo->swPduHandle;
                                            sCANMessage.ui32MsgID = PduInfo->id;
                                            sCANMessage.ui32MsgLen = PduInfo->length;
                                            if(PduInfo->length<1U)
                                            {
                                                sCANMessage.ui32MsgLen = 1U;
                                            }

                                            else{
                                                sCANMessage.ui32MsgLen=PduInfo->length;

                                                }
                                            sCANMessage.pui8MsgData =PduInfo->sdu;

                                            /*[SWS_CAN_00502]  If PduInfo->SduLength does not match possible DLC values CanDrv
                                            shall use the next higher valid DLC for transmission with initialisation of unused bytes
                                            to the value of the corresponding CanFdPaddingValue (see ECUC_Can_00485).*/

                                           /* [SWS_Can_00059] Data mapping by CAN to memory is defined in a way that the
                                              CAN data byte which is sent out first is array element 0, the CAN data byte which
                                              is sent out last is array element 7 or 63 in case of CAN FD.
                                             N.B:Our TIVA c doesn't support FD*/


                                             
                                            sCANMessage.ui32MsgIDMask = 0U;
                                            if(hohobj->CanIdType==EXTENDED)
                                            {
                                                sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE|MSG_OBJ_EXTENDED_ID;
                                            }else{

                                                sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
                                                 }


                                            CANMessageSet(hohobj->CanControllerRef->CanControllerBaseAddress,
                                                          Message_Confirmation[HTH][i].mail_box, &sCANMessage, MSG_OBJ_TYPE_TX);
                                            Message_Confirmation[HTH][i].PduId=PduInfo->swPduHandle;
                                            return  E_OK;/*add break here when u clear multi exit points of function*/

#if CanMultiplexedTransmission
                                  }

                                  else
                                  {

                                      Message_Confirmation[HTH][i].PduId=PduInfo->swPduHandle;
                                      Message_Confirmation[HTH][i].Confirmation=un_confirmed;
                                     for(j=i;j<(hohobj->CanHwObjectCount-1U);j++)
                                   {

                                     if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[i].CanControllerRef== &CanContainer.CanConfigSet
                                                               .CanController[0])
                                         {
                                             CAN0_IF1CMSK_R&=((uint32_t)(~(uint32_t)0x80U));
                                             CAN0_IF1CRQ_R=Message_Confirmation[HTH][j+1].mail_box;
                                             if(hohobj->CanIdType==STANDARD)
                                             {
                                               REGISTER_1=CAN0_IF1ARB2_R;
                                               sCANMessage.ui32MsgID=REGISTER_1 &0xFFFU;
                                               sCANMessage.ui32MsgID=sCANMessage.ui32MsgID>>2U;

                                             }
                                             else /*for mixed or extended */
                                             {
                                               REGISTER_1=CAN0_IF1ARB2_R;
                                               REGISTER_1&=0xFFFU;
                                               REGISTER_2=CAN0_IF1ARB1_R;
                                               sCANMessage.ui32MsgID=sCANMessage.ui32MsgID=REGISTER_1+REGISTER_2;
                                             }
                                             sCANMessage.pui8MsgData[0U]=CAN0_IF1DA1_R;
                                             sCANMessage.pui8MsgData[1U]=CAN0_IF1DA1_R>>8;
                                             sCANMessage.pui8MsgData[2U]=CAN0_IF1DA2_R;
                                             sCANMessage.pui8MsgData[3U]=CAN0_IF1DA2_R>>8;
                                             sCANMessage.pui8MsgData[4U]=CAN0_IF1DB1_R;
                                             sCANMessage.pui8MsgData[5U]=CAN0_IF1DB1_R>>8;
                                             sCANMessage.pui8MsgData[6U]=CAN0_IF1DB2_R;
                                             sCANMessage.pui8MsgData[7U]=CAN0_IF1DB2_R>>8;
                                             REGISTER_1=CAN0_IF1MCTL_R;
                                             sCANMessage.ui32MsgLen=REGISTER_1 & 0xFU;
                                             sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
                                         }
                                     else{
                                              CAN1_IF1CMSK_R&=((uint32_t)(~(uint32_t)0x80U));
                                              CAN1_IF1CRQ_R=Message_Confirmation[HTH][j+1].mail_box;
                                              if(hohobj->CanIdType==STANDARD)
                                              {
                                                REGISTER_1=CAN1_IF1ARB2_R;
                                                sCANMessage.ui32MsgID=REGISTER_1 &0xFFFU;
                                              }
                                              else
                                              {
                                                REGISTER_1=CAN1_IF1ARB2_R;
                                                REGISTER_1&=0xFFFU;
                                                REGISTER_2=CAN1_IF1ARB1_R;
                                                sCANMessage.ui32MsgID=REGISTER_1+REGISTER_2;

                                              }
                                               sCANMessage.pui8MsgData[0U]=CAN1_IF1DA1_R;
                                               sCANMessage.pui8MsgData[1U]=CAN1_IF1DA1_R>>8;
                                               sCANMessage.pui8MsgData[2U]=CAN1_IF1DA2_R;
                                               sCANMessage.pui8MsgData[3U]=CAN1_IF1DA2_R>>8;
                                               sCANMessage.pui8MsgData[4U]=CAN1_IF1DB1_R;
                                               sCANMessage.pui8MsgData[5U]=CAN1_IF1DB1_R>>8;
                                               sCANMessage.pui8MsgData[6U]=CAN1_IF1DB2_R;
                                               sCANMessage.pui8MsgData[7U]=CAN1_IF1DB2_R>>8;
                                              sCANMessage.ui32MsgLen=CAN1_IF1MCTL_R & 0xFU;
                                              sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
                                             }

                                     if(PduInfo->id >= sCANMessage.ui32MsgID)
                                            /*we swap between message objects of same HOH in case of requested id is higher priority
                                             than ID stored in higher priotrity object by that we are preventing priority inversion*/
                                            {

                                                   if(hohobj->CanIdType==EXTENDED)
                                                   {
                                                       sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE|MSG_OBJ_EXTENDED_ID;
                                                   }else{

                                                           sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
                                                        }

                                                CANMessageSet(hohobj->CanControllerRef->CanControllerBaseAddress,
                                                              Message_Confirmation[HTH][j].mail_box, &sCANMessage, MSG_OBJ_TYPE_TX);

                                               temp.PduId=Message_Confirmation[HTH][j+1].PduId;

                                               Message_Confirmation[HTH][j+1].PduId=Message_Confirmation[HTH][j].
                                                                                                      PduId=PduInfo->swPduHandle;
                                               Message_Confirmation[HTH][j].PduId=temp.PduId;

                                           temp.Confirmation=Message_Confirmation[HTH][j+1].Confirmation;

                                           Message_Confirmation[HTH][j+1].Confirmation=Message_Confirmation[HTH][j].Confirmation;
                                           Message_Confirmation[HTH][j].Confirmation= temp.Confirmation;

                                           }

                                   else{

                                           break;
                                       }
                                   }

                                     Message_Confirmation[HTH][j].PduId=PduInfo->swPduHandle;
                                     sCANMessage.ui32MsgID = PduInfo->id;
                                     sCANMessage.ui32MsgLen = PduInfo->length;
                                    if(PduInfo->length<1U)
                                        {
                                            sCANMessage.ui32MsgLen = 1U;
                                        }
                                    else
                                        {
                                          sCANMessage.ui32MsgLen=PduInfo->length;
                                        }
                                    sCANMessage.pui8MsgData =PduInfo->sdu;
                                    sCANMessage.ui32MsgIDMask = 0U;

                                    if(hohobj->CanIdType==EXTENDED)
                                    {
                                        sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE|MSG_OBJ_EXTENDED_ID;
                                    }else{

                                            sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
                                         }

                                    CANMessageSet(hohobj->CanControllerRef->CanControllerBaseAddress,
                                    Message_Confirmation[HTH][j].mail_box , &sCANMessage, MSG_OBJ_TYPE_TX);
                                    return  E_OK;
                                  }

#endif
                                }
                                else
                                 {
                                     if(i==0U)
                                     {
                                         return  CAN_BUSY;/*add break here when u clear multi exit points of function*/

                                     }else{}
                                 }
                            }

                      /*[SWS_Can_00011] The Can module shall directly copy the data from the upper
                      layer buffers. It is the responsibility of the upper layer to keep the buffer consistent until return
                      of function call*/

                      }
                      else
                      {
                           /*FULL CAN*/
                       if(Message_Confirmation[HTH][0].Confirmation==confirmed)
                       {
                                       Message_Confirmation[HTH][0].Confirmation=un_confirmed; /*this is the right logic
                                         but depends on OSEK*/
                                       Message_Confirmation[HTH][0].PduId=PduInfo->swPduHandle;
            /*[SWS_Can_00276] ⌈The function Can_Write shall store the swPduHandle that is given inside the parameter
             PduInfo until the Can module calls the CanIf_TxConfirmation for this request where
             the swPduHandle is given as parameter*/

                            /*Message_Confirmation[HTH][0].Confirmation=un_confirmed*/
                            sCANMessage.ui32MsgID = PduInfo->id;
                            sCANMessage.ui32MsgLen = PduInfo->length;
                            if(PduInfo->length<1U)
                            {
                                sCANMessage.ui32MsgLen = 1U;
                            }

                            else{
                                sCANMessage.ui32MsgLen=PduInfo->length;

                                }
                            sCANMessage.pui8MsgData =PduInfo->sdu;

                            /*[SWS_CAN_00502]  If PduInfo->SduLength does not match possible DLC values CanDrv
                            shall use the next higher valid DLC for transmission with initialisation of unused bytes
                            to the value of the corresponding CanFdPaddingValue (see ECUC_Can_00485).

                             [SWS_Can_00059] Data mapping by CAN to memory is defined in a way that the
                              CAN data byte which is sent out first is array element 0, the CAN data byte which
                              is sent out last is array element 7 or 63 in case of CAN FD.
                              N.B:Our tiva c doesn't support FD*/

                            sCANMessage.ui32MsgIDMask = 0U;
                            sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;

                            if(hohobj->CanIdType==EXTENDED)
                            {
                                sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE|MSG_OBJ_EXTENDED_ID;
                            }else{

                                    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
                                 }
                            CANMessageSet(hohobj->CanControllerRef->CanControllerBaseAddress,
                                          Message_Confirmation[HTH][0U].mail_box, &sCANMessage, MSG_OBJ_TYPE_TX);
                            return  E_OK;
                           }
                                   else
                                   {

                                       /*[SWS_Can_00213] The function Can_Write shall perform no actions if the
                                         hardware transmit object is busy with another transmit request.for an L-PDU:
                                       1. The transmission of the other L-PDU shall not be cancelled
                                       and the function Can_Write is left without any actions.
                                       2. The function Can_Write shall return CAN_BUSY.*/

                                       return CAN_BUSY;

                                       /*[SWS_Can_00214] The function Can_Write shall return CAN_BUSY if
                                        a preemptive call of Can_Write has been issued, that could not be
                                        handled reentrant (i.e. a call with the same HTH).*/
          }
         }
        }
       }
     }
    }
  }
}

/*  Note: this function should loop on the array of BaudRateConfiguration to detect
the matched ID with the input BaudRateConfigID and then it should set the controller BaudRate value
since we will use only one ID in out case.. the loop and the array of BR configuration has been cancelled.
Sarea */

#if CanSetBaudrateApi
Std_ReturnType Can_SetBaudrate(uint8_t Controller,uint16_t BaudRateConfigID )

{

  uint32_t index8;
  tCANBitClkParms Bit_Time_Parameters;
 if(CanUnitState == CAN_READY)
 {

   if(Controller <= (NUM_OF_CAN_CONTROLLERS -1U))
    {
            for (index8=0U;index8<=Max_num_of_baudrates;index8++)
                  {
               if(index8==Max_num_of_baudrates)
                 {
                          /* [SWS_CAN_00493] If development error detection for the Can module is enabled:
                         The function Can_SetBaudrate shall raise the error CAN_E_PARAM_BAUDRATE
                                and return E_NOT_OK if the parameter BaudRateConfigID has an invalid value.*/
                     CanDevolpmentErrorType=CAN_E_PARAM_BAUDRATE;
                     return E_NOT_OK ;
                  }
              else{
                        if(  CanContainer.CanConfigSet.CanController[Controller]
                               .CanControllerBaudrateConfig[index8].CanControllerBaudRateConfigID == BaudRateConfigID)
                         {

                             Bit_Time_Parameters.ui32SyncPropPhase1Seg=CanContainer.CanConfigSet.
                                     CanController[Controller].CanControllerBaudrateConfig[index8].CanControllerSeg1+
                                     CanContainer.CanConfigSet.CanController[Controller].CanControllerBaudrateConfig[index8].
                                     CanControllerPropSeg;
                             Bit_Time_Parameters.ui32Phase2Seg=CanContainer.CanConfigSet.CanController[Controller].
                                                        CanControllerBaudrateConfig[index8].CanControllerSeg2;
                             Bit_Time_Parameters.ui32SJW=CanContainer.CanConfigSet.CanController[Controller].
                                     CanControllerBaudrateConfig[index8].CanControllerSyncJumpWidth;

                                                          /*uint32_t x;
                                                          x= SysCtlClockGet();*/
                          Bit_Time_Parameters.ui32QuantumPrescaler=SysCtlClockGet()/((Bit_Time_Parameters.ui32SyncPropPhase1Seg
                                  +Bit_Time_Parameters.ui32Phase2Seg+1U)*
                          CanContainer.CanConfigSet.CanController[Controller].CanControllerBaudrateConfig[index8].CanControllerBaudRate*1000U);


                                  CANBitTimingSet(CanContainer.CanConfigSet.CanController[Controller].
                                   CanControllerBaseAddress, &Bit_Time_Parameters);
                                  if( Can_ControllerMode [Controller]==CAN_CS_STOPPED||Can_ControllerMode [Controller]==CAN_CS_SLEEP)
                                  {
                                     CANDisable(CanContainer.CanConfigSet.CanController[Controller].
                                   CanControllerBaseAddress);
                                  }else{
                                          /*MISRA*/
                                        }
                                    break;
                         }   else{}
                   }
                  }
                                            return E_OK ;
                     }
                  else{

                 /*[SWS_CAN_00494] If development error detection for the Can module is enabled
                 the function Can_SetBaudrate shall raise the error CAN_E_PARAM_CONTROLLER and
                 return E_NOT_OK if the parameter Controller is out of range.*/
                 CanDevolpmentErrorType=CAN_E_PARAM_CONTROLLER;
                 return E_NOT_OK ;
                 }
             }
else
{
      /*  [SWS_CAN_00492] If development error detection for the Can module is enabled:
       Specification of CAN Driver
        The function Can_SetBaudrate shall raise the error CAN_E_UNINIT and return
       E_NOT_OK if the driver is not yet init_ialized.*/

CanDevolpmentErrorType=CAN_E_UNINIT;
return E_NOT_OK ;
 }
}
#endif

void Can_DisableControllerInterrupts(uint8_t Controller)

{
    if(CanUnitState==CAN_UNINIT)
    {
        CanDevolpmentErrorType=CAN_E_UNINIT;
    }
    else{
         if(Controller >= NUM_OF_CAN_CONTROLLERS)
         {
             CanDevolpmentErrorType= CAN_E_PARAM_CONTROLLER;
         }
         else{
                   IntDisableCount[Controller]++;


              if(IntEnableCount[Controller] >= 1U)
              {

                       IntEnableCount[Controller]--;


                   if(IntEnableCount[Controller] ==0U)

                {   /*The function Can_DisableControllerInterrupts shall access the CAN controller registers to disable all interrupts
                       for that CAN controller only, if interrupts for that CAN Controller are enabled.*/
                       /*In our case it can be enabled by start_mode*/
                      /*reseting the flag*/
                 if(Controller == 0U)
                 {
                 /* set interrupt enable, status interrupt enable, error interrupt enable to disable interrupts."*/

                     IntDisable(INT_CAN0);

                 }
                 else if(Controller == 1U)
                 {
                     /* set interrupt enable, status interrupt enable, error interrupt enable to disable interrupts."*/

                     IntDisable(INT_CAN1);

                 }

                 else{
                         /*MISRA*/
                     }
           }
  }
     else  if(Int_enable_in_start_mode[Controller]==1U)
  {
      /*The function Can_DisableControllerInterrupts shall access the CAN controller registers to disable all interrupts
           for that CAN controller only, if interrupts for that CAN Controller are enabled.*/
           /*In our case it can be enabled by start_mode*/
           Int_enable_in_start_mode[Controller]=0U;/*reseting the flag*/

     if(Controller == 0U)
     {
     /* set interrupt enable, status interrupt enable, error interrupt enable to disable interrupts."*/

         IntDisable(INT_CAN0);

     }
     else if(Controller == 1U)
     {
         /* set interrupt enable, status interrupt enable, error interrupt enable to disable interrupts."*/

         IntDisable(INT_CAN1);

     }

     else{
             /*MISRA*/
         }
  }else{/*MISRA*/}
 }
}
}



void Can_EnableControllerInterrupts(uint8_t Controller)
{
   if(CanUnitState==CAN_UNINIT)
   {
       CanDevolpmentErrorType=CAN_E_UNINIT;
   }
   else{
            if(Controller >= NUM_OF_CAN_CONTROLLERS)
            {
                CanDevolpmentErrorType= CAN_E_PARAM_CONTROLLER;
            }
            else{
                IntEnableCount[Controller]++;

               if(Int_disable_in_stop_mode[Controller]==0U)
              {
                if(IntDisableCount[Controller] >= 1U)

                    /* [SWS_Can_00208] The function Can_EnableControllerInterrupts shall perform no action when
                      Can_DisableControllerInterrupts has not been called before.*/

               {

                    /*[SWS_Can_00202] When Can_DisableControllerInterrupts has been called several times,
                   Can_EnableControllerInterrupts must be called as many times before the interrupts are re-enabled.*/
                   IntDisableCount[Controller]--;

                  if(IntDisableCount[Controller]==0U)
                  {
                    if(Controller == 0U)
                    {
                    /* set interrupt enable, status interrupt enable, error interrupt enable to disable interrupts."*/
                        CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
                        IntEnable(INT_CAN0);
                        IntDisableCount[Controller]--;
                    }
                    else if(Controller == 1U)
                    {
                        /* set interrupt enable, status interrupt enable, error interrupt enable to disable interrupts."*/
                        CANIntEnable(CAN1_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
                        IntEnable(INT_CAN1);
                        IntDisableCount[Controller]--;
                    }

                    else{
                            /*MISRA*/
                        }
              }else{
                     /*MISRA*/
                   }
      }
   }else{/*MISRA*/}
 }
}
}
Std_ReturnType Can_SetControllerMode( uint8_t Controller,
                                      Can_StateTransitionType Transition )
{    uint8_t index9,index10;

/*[SWS_Can_00370] The function Can_Mainfunction_Mode shall poll a flag of the CAN status
register until the flag signals that the change takes effect and notify the upper layer with
function CanIf_ControllerModeIndication about a successful state transition referring to
the corresponding CAN controller with the abstract CanIf ControllerId.*/

if(CanUnitState == CAN_UNINIT)
    {
        CanDevolpmentErrorType=CAN_E_UNINIT;
        return E_NOT_OK;
    }
 else{

        if(Controller>= NUM_OF_CAN_CONTROLLERS)
        {
        CanDevolpmentErrorType=CAN_E_PARAM_CONTROLLER;
        return E_NOT_OK;
        }
        else{
                 /* Can_ControllerStateType x;*/

/*   [SWS_Can_00409]  When the function Can_SetControllerMode (CAN_CS_STARTED) is entered and the
                CAN controller is not in state STOPPED it shall detect a invalid state transition*/
                  if(((Transition == CAN_T_START) && ( Can_ControllerMode [Controller]!=CAN_CS_STOPPED))||
                                         ((Transition == CAN_T_SLEEP) && (Can_ControllerMode [Controller]!= CAN_CS_STOPPED)))
                    {
                       CanDevolpmentErrorType=CAN_E_TRANSITION;
                       return E_NOT_OK;
                    }
                   else{
                       state_transition_flag[Controller]=1;

                           switch(Transition){
                            case CAN_T_START :
                    /*no interrupt if enabled will affect start mode so no need to apply[SWS_Can_00197]
                   [SWS_Can_00261] The function Can_SetControllerMode(CAN_CS_STARTED) shall set the
                   hardware registers in a way that makes the CAN controller participating on the network.*/
                         if(Controller == 0U)
                         {
                             Int_disable_in_stop_mode[Controller]=0U;
                        /* [SWS_Can_00384] Each time the CAN controller state machine is triggered with the state
                         transition value CAN_CS_STARTED, the function Can_SetControllerMode shall re-initialise
                         the CAN controller with the same controller configuration set previously used by functions
                         Can_SetBaudrate or Can_Init.*/

                        /*[SWS_Can_00196]The function Can_SetControllerMode shall enable interrupts that are
                          needed in the new state.*/
                             if(IntDisableCount[0U]==0U)
                                 /*[SWS_Can_00204] The Can module shall track all individual enabling and disabling of
                                   interrupts in other functions (i.e. Can_SetControllerMode) , so that the correct
                                   interrupt enable state can be restored.*/
                                 {
                                     CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
                                     IntEnable(INT_CAN0);
                                     CANEnable(CAN0_BASE);
                                     Int_enable_in_start_mode[Controller]=1U;
                                 }
                            else {
                                   CANEnable(CAN0_BASE);
                                 }

                            /* state transition shall be detected here {Can_Mainfunction_Mode must be implemented}*/
                        }
                        else if(Controller == 1U)
                        {
                            Int_disable_in_stop_mode[Controller]=0U;
                            if(IntDisableCount[1U]==0U)
                                /*SWS_Can_00425] Enabling of CAN interrupts shall not be executed,
                              when CAN interrupts have been disabled by function Can_DisableControllerInterrupts.*/
                                {
                                  CANIntEnable(CAN1_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
                                  IntEnable(INT_CAN1);
                                  CANEnable(CAN1_BASE);
                                  Int_enable_in_start_mode[Controller]=1U;
                                 /* [SWS_Can_00261] ⌈The function Can_SetControllerMode(CAN_CS_STARTED) shall set
                                    the hardware registers in a way that makes the CAN controller participating
                                     on the network.*/
                                }
                           else {
                                   CANEnable(CAN1_BASE);
                                }
                        }
                        else
                        {
                            /* MISRA */
                        }
                     /* setting the new mode to STARTED */
                     Can_ControllerMode[Controller] = CAN_CS_STARTED;
                     break;

                    case CAN_T_STOP :
                       /* [SWS_Can_00197] ⌈The function Can_SetControllerMode shall disable interrupts that are not
                        allowed in the new state. */
                    if(Controller == 0U)
                    {
                        if(IntDisableCount[0U]>=1U)
                            /*Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled
                            by function Can_disableControllerInterrupts.*/
                           {

                                 CANDisable(CAN0_BASE);

                           }
                          else
                              {
                                CANDisable (CAN0_BASE);
                                CANIntDisable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
                               Int_disable_in_stop_mode[Controller]=1U;

                                 /* [SWS_Can_00263] The function Can_SetControllerMode(CAN_CS_STOPPED) shall set the
                                    bits inside the CAN hardware such that the CAN controller stops participating on the
                                    network.*/
                               }
                                 /*[SWS_Can_00282] ⌈The function Can_SetControllerMode(CAN_CS_STOPPED)
                                 shall cancel pending messages.*/

                            for(index9=0U;index9<NUM_OF_HOH;index9++)
                            {
                                if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index9].CanControllerRef== &CanContainer.CanConfigSet
                                        .CanController[0U])
                                {
                                    if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index9].CanObjectType==transmit)
                                    {
                                for(index10=0U;index10<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index9].CanHwObjectCount;index10++)
                                {
                                CAN0_IF1MCTL_R&=((uint32_t)(~(uint32_t)0x100U));
                                CAN0_IF1CMSK_R &= ((uint32_t)(~(uint32_t)0x80U));
                                CAN0_IF1CRQ_R =((uint32_t)((uint32_t) Message_Confirmation[index9][index10].mail_box));
                                }
                               }else{}
                             }else{}
                            }
                           }

                    else if(Controller == 1U)
                    {
                        if(IntDisableCount[1U]>=1U)

                                   {

                                         CANDisable (CAN1_BASE);
                                   }

                              else {
                                      CANIntDisable(CAN1_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
                                      CANDisable (CAN1_BASE);
                                      Int_disable_in_stop_mode[Controller]=1U;

                                   }
                                 for(index9=0U;index9<NUM_OF_HOH;index9++)
                              {
                                if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index9].CanControllerRef==
                                        &CanContainer.CanConfigSet.CanController[1U])
                                {
                                  if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index9].CanObjectType==transmit)
                                 {
                                  for(index10=0U;index10<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index9].CanHwObjectCount;index10++)
                                  {
                                  CAN1_IF1MCTL_R&=((uint32_t)(~(uint32_t)0x100U));
                                  CAN1_IF1CMSK_R &=((uint32_t)(~(uint32_t)0x80U));
                                  CAN1_IF1CRQ_R =((uint32_t)((uint32_t) Message_Confirmation[index9][index10].mail_box));

                                  }
                                 }else{}
                               }else{}
                              }
                            }
                    else
                    {
                        /*MISRA*/
                    }
                    Can_ControllerMode[Controller] = CAN_CS_STOPPED;
                    /* array for the current state for each controller*/
                    break;
                    case CAN_T_SLEEP :
                    /*[SWS_Can_00258] When the CAN hardware does not support sleep mode and is triggered to
                     transition into SLEEP state, the Can module shall emulate a logical SLEEP state from which it
                    returns only, when it is triggered by software to transition into STOPPED state.*/
                   /*[SWS_Can_00404] The CAN hardware shall remain in state STOPPED, while the logical SLEEP state is active.
                   [SWS_Can_00290] If the CAN HW does not support a sleep mode, the function
                     Can_SetControllerMode(CAN_CS_SLEEP) shall set the CAN controller to the logical sleep mode.*/
                /* [SWS_Can_00197] The function Can_SetControllerMode shall disable interrupts that are not
                                     allowed in the new state. */
                                 if(Controller == 0U)
                                 {
                                     if(IntDisableCount[0U]>=1U)
                                         /*Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled
                                         by function Can_disableControllerInterrupts.*/
                                        {

                                              CANDisable(CAN0_BASE);

                                        }
                                       else
                                           {
                                             CANDisable (CAN0_BASE);
                                             CANIntDisable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
                                            Int_disable_in_stop_mode[Controller]=1U;

                                              /* [SWS_Can_00263] The function Can_SetControllerMode(CAN_CS_STOPPED) shall set the
                                                 bits inside the CAN hardware such that the CAN controller stops participating on the
                                                 network.*/
                                            }
                                              /*[SWS_Can_00282] The function Can_SetControllerMode(CAN_CS_STOPPED)
                                              shall cancel pending messages.*/

                                         for(index9=0U;index9<NUM_OF_HOH;index9++)
                                         {
                                             if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index9].CanControllerRef== &CanContainer.CanConfigSet
                                                     .CanController[0U])
                                             {
                                                 if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index9].CanObjectType==transmit)
                                                 {
                                             for(index10=0U;index10<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index9].CanHwObjectCount;index10++)
                                             {
                                               CAN0_IF1MCTL_R&=((uint32_t)(~(uint32_t)0x100U));
                                               CAN0_IF1CMSK_R &=((uint32_t)(~(uint32_t)0x80U));
                                               CAN0_IF1CRQ_R =((uint32_t)((uint32_t) Message_Confirmation[index9][index10].mail_box));
                                             }
                                            }else{}
                                          }else{}
                                         }
                                        }

                                 else if(Controller == 1U)
                                 {
                                     if(IntDisableCount[1U]>=1U)

                                                {

                                                      CANDisable (CAN1_BASE);
                                                }

                                           else {
                                                   CANIntDisable(CAN1_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
                                                   CANDisable (CAN1_BASE);
                                                   Int_disable_in_stop_mode[Controller]=1U;

                                                }
                                              for(index9=0U;index9<NUM_OF_HOH;index9++)
                                           {
                                             if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index9].CanControllerRef==
                                                     &CanContainer.CanConfigSet.CanController[1U])
                                             {
                                               if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index9].CanObjectType==transmit)
                                              {
                                               for(index10=0U;index10<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index9].CanHwObjectCount;index10++)
                                               {
                                               CAN1_IF1MCTL_R&=((uint32_t)(~(uint32_t)0x100U));
                                               CAN1_IF1CMSK_R &=((uint32_t)(~(uint32_t)0x80U));
                                               CAN1_IF1CRQ_R =((uint32_t)((uint32_t) Message_Confirmation[index9][index10].mail_box));

                                               }
                                              }else{}
                                            }else{}
                                           }
                                         }
                                 else
                                 {
                                     /*MISRA*/
                                 }
                                  Can_ControllerMode[Controller] = CAN_CS_SLEEP;
                                 /* array for the current state for each controller*/
                                 break;

                        default: {break;}
     }
    }
   }
 }
/*[SWS_Can_00262] The function Can_SetControllerMode(CAN_CS_STARTED) shall wait for
 limited time until the CAN controller is fully operational. Compare to SWS_Can_00398.*/

/*[SWS_Can_00264] The function Can_SetControllerMode(CAN_CS_STOPPED) shall wait for
a limited time until the CAN controller is really switched off. Compare to SWS_Can_00398.*/
Timer0A_Init();
while ((TIMER0_RIS_R & 0x1) == 0){}
TIMER0_ICR_R = 0x1U;
return E_OK;
}

Std_ReturnType Can_GetControllerMode( uint8_t Controller, Can_ControllerStateType* ControllerModePtr)
{
    if(Controller > NUM_OF_CAN_CONTROLLERS-1U)
    {
    CanDevolpmentErrorType=CAN_E_PARAM_CONTROLLER; /*optional*/
    }
    else{

         if(ControllerModePtr==NULL)
         {
             CanDevolpmentErrorType=CAN_E_PARAM_POINTER; /*optional*/
             }
         else{
                if(CanUnitState == CAN_READY )
                {
                    /*[SWS_Can_91015] The service Can_GetControllerMode shall return
                            the mode of the requested CAN controller.*/
                        if(Controller==0U)
                            {
                                *ControllerModePtr=Can_ControllerMode [0U];
                                return E_OK;
                            }
                        else
                            {

                                *ControllerModePtr= Can_ControllerMode [1U];
                                return E_OK;
                            }
                    }
                   else{
                        CanDevolpmentErrorType=CAN_E_UNINIT;
                        return E_NOT_OK;
                        /*[SWS_Can_91016] If development error detection for the Can module is enabled:
                        The function Can_GetControllerMode shall raise the error CAN_E_UNINIT and return
                        E_NOT_OK if the driver is not yet initialized.*/
                       }
       }
    }
}

void Can0_InterruptHandler(void) {

        uint32_t ui32Status0;
        uint32_t status0;
        uint8_t index12, index11 ;
        tCANMsgObject received_CANMessage1;
        uint8_t rx_MsgData1[8U]={0U};
        PduInfoType received_PduInfo0;
        Can_HwType Rx_Mailbox0;
        received_CANMessage1.pui8MsgData=rx_MsgData1;
        /* Read the CAN interrupt status to find the cause of the interrupt */
        ui32Status0 = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
        /* If the cause is a controller status interrupt, then get the status*/
        if(ui32Status0 == CAN_INT_INTID_STATUS)
        {
            CANIntClear(CAN0_BASE, ui32Status0);
            status0= CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
                        status0&=0x80U;
                          if(status0==CAN_STS_BOFF)
                          {
                            /*[SWS_Can_00020]  triggered by hardware if the CAN controller reaches bus-off state
                             The CanIf module is notified with the function CanIf_ControllerBusOff after bus off detection*/
                              Can_ControllerMode [0U]=CAN_CS_STOPPED;
                        /*CanIf_ControllerBusOff(0U)*/

                           /* [SWS_Can_00272] After bus-off detection, the CAN controller shall transition to the
                                        state STOPPED and the Can module shall ensure that the CAN controller
                                        doesn't participate on the network anymore.*/
                         /* [SWS_Can_00273] After bus-off detection, the Can module shall cancel still pending messages.*/


                          }else{/*MISRA*/}
        }
        else if((ui32Status0>= 0x01U) && (ui32Status0<= 0x20U))
        {
            /* if it is a object successful receive or object transmit*/
            CANIntClear(CAN0_BASE, ui32Status0);


                                                          /*FOR TEST ONLY*/
    for(index12=0U;index12< NUM_OF_HOH;index12++)
            {
                if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index12].CanControllerRef==&CanContainer
                                                                      .CanConfigSet.CanController[0])
                {
                          if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index12].CanObjectType==transmit)
                          {
                                for(index11=0U;index11<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index12].CanHwObjectCount;index11++)
                                {

                                    if(Message_Confirmation[index12][index11].mail_box==ui32Status0)
                                    {

                                        Message_Confirmation[index12][index11].Confirmation=confirmed;/*when it comes to poll again it wouldn't find
                                        it un_confirmed except when another transmission was requested again*/
                                       /*test only*/

//                                        CanIf_TxConfirmation(Message_Confirmation[index12][index].PduId);
                                    }else{}
                              }
                         }

                      else { /*reception*/

                            for(index11=0U;index11<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index12].CanHwObjectCount;index11++)
                               {

                                if(Message_Confirmation[index12][index11].mail_box==ui32Status0)
                                 {
                                /*interrupt handling should be deferred*/
                                      /*[SWS_Can_00396] ⌈The RX-interrupt service routine of the corresponding HW resource or
                                      the function Can_MainFunction_Read in case of polling mode shall call the callback function
                                       CanIf_RxIndication.*/

                                            CANMessageGet(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index12].
                                                          CanControllerRef->CanControllerBaseAddress,
                                                          Message_Confirmation[index12][index11].mail_box, &received_CANMessage1, 0U);
                                                    Rx_Mailbox0.hoh=index12;
                                                    Rx_Mailbox0.id= received_CANMessage1.ui32MsgID ;
                                                    Rx_Mailbox0.controllerlId =MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index12]
                                                                                             .CanControllerRef->CanControllerId;
                                                    received_PduInfo0.SduLength  = received_CANMessage1.ui32MsgLen;
                                /* [SWS_Can_00060] Data mapping by CAN to memory is defined in a way that the CAN data byte
                                  which is received first is array element 0 the CAN data byte which is received last is array element 7*/
                                                   received_PduInfo0.SduDataPtr = received_CANMessage1.pui8MsgData;
                                                  GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^0x04U;
                                                   CanIf_RxIndication(&Rx_Mailbox0,&received_PduInfo0);
                               }else{/*MISRA*/}
                             }
                        }
                   }else{/*MISRA*/}
             }
 }
        else{
                /*MISRA*/
            }
}
void Can1_InterruptHandler(void) {

        uint32_t ui32Status1;
        uint32_t status1;
        uint8_t index13, index14 ;
        tCANMsgObject received_CANMessage2;
        PduInfoType received_PduInfo1;
        Can_HwType Rx_Mailbox1;
        uint8_t rx_MsgData2[8U]={0U};
        received_CANMessage2.pui8MsgData=rx_MsgData2;
        /* Read the CAN interrupt status to find the cause of the interrupt */
        ui32Status1 = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
        /* If the cause is a controller status interrupt, then get the status*/
        if(ui32Status1 == CAN_INT_INTID_STATUS)
        {
            CANIntClear(CAN0_BASE, ui32Status1);
            status1= CANStatusGet(CAN1_BASE, CAN_STS_CONTROL);
                        status1&=0x80U;
                          if(status1==CAN_STS_BOFF)
                          {
                            /*[SWS_Can_00020]  triggered by hardware if the CAN controller reaches bus-off state
                             The CanIf module is notified with the function CanIf_ControllerBusOff after bus off detection*/

                              Can_ControllerMode [1U]=CAN_CS_STOPPED;
                           /* [SWS_Can_00272] After bus-off detection, the CAN controller shall transition to the
                                        state STOPPED and the Can module shall ensure that the CAN controller
                                        doesn't participate on the network anymore.*/
                         /* [SWS_Can_00273] After bus-off detection, the Can module shall cancel still pending messages.*/

                            /*CanIf_ControllerBusOff(1U)*/

                          }else{/*MISRA*/}
        }
        else if((ui32Status1>= 0x01U) && (ui32Status1<= 0x20U))
        {
            /* if it is a object successful receive or object transmit*/
            CANIntClear(CAN1_BASE, ui32Status1);

            //GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^0x04U;
                                                          /*FOR TEST ONLY*/
    for(index13=0U;index13< NUM_OF_HOH;index13++)
            {
                if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index13].CanControllerRef==&CanContainer
                                                                      .CanConfigSet.CanController[1])
                {
                          if(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index13].CanObjectType==transmit)
                          {
                                for(index14=0U;index14<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index13].CanHwObjectCount;index14++)
                                {

                                    if(Message_Confirmation[index13][index14].mail_box==ui32Status1)
                                    {

                                        Message_Confirmation[index13][index14].Confirmation=confirmed;/*when it comes to poll again it wouldn't find
                                        it un_confirmed except when another transmission was requested again*/
                                       /*test only*/

                                       /* CanIf_TxConfirmation(Message_Confirmation[i][j].PduId)*/
                                    }else{}
                              }
                         }

                      else { /*reception*/

                            for(index14=0U;index14<MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index13].CanHwObjectCount;index14++)
                               {

                                if(Message_Confirmation[index13][index14].mail_box==ui32Status1)
                                 {
                                /*interrupt handling should be deferred*/
                                      /*[SWS_Can_00396] ⌈The RX-interrupt service routine of the corresponding HW resource or
                                      the function Can_MainFunction_Read in case of polling mode shall call the callback function
                                       CanIf_RxIndication.*/

                                            CANMessageGet(MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index13].
                                                          CanControllerRef->CanControllerBaseAddress,
                                                          Message_Confirmation[index13][index14].mail_box, &received_CANMessage2, 0U);
                                                    Rx_Mailbox1.hoh=index13;
                                                    Rx_Mailbox1.id= received_CANMessage2.ui32MsgID ;
                                                    Rx_Mailbox1.controllerlId =MailboxCfg_MAP.CanConfigSet.CanHardwareObject[index13]
                                                                                             .CanControllerRef->CanControllerId;
                                                    received_PduInfo1.SduLength  = received_CANMessage2.ui32MsgLen;
                                /* [SWS_Can_00060] Data mapping by CAN to memory is defined in a way that the CAN data byte
                                  which is received first is array element 0 the CAN data byte which is received last is array element 7*/
                                                   received_PduInfo1.SduDataPtr = received_CANMessage2.pui8MsgData;
                                                   GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^0x04U;
                                                 CanIf_RxIndication(&Rx_Mailbox1,&received_PduInfo1);
                               }else{/*MISRA*/}
                             }
                        }
                   }else{/*MISRA*/}
             }
 }
        else{
                /*MISRA*/
            }
}












void Can_Init(Can_ConfigType* Config)
{
    tCANBitClkParms Bit_Time_Parameters0; /* structure containing bit time parameters*/
    if(CanUnitState == CAN_UNINIT)

        /*[SWS_Can_00246]  The function Can_Init shall change the module state to
            CAN_READY, after initialising all controllers inside the HW Unit.*/
    {


        if  ((Can_ControllerMode [0U]== CAN_CS_UNINIT) && ( Can_ControllerMode[1U]== CAN_CS_UNINIT))
            {

                uint8_t index15, index16 ;
                for (index15 = 0U; index15<NUM_OF_CAN_CONTROLLERS; index15++)
                {      /*[SWS_Can_00245]  The function Can_Init shall initialize all CAN controllers
                                                          according to their configuration.*/
                    SysCtlPeripheralEnable(Config->CanConfigSet.CanController[index15].CanCpuClockRef[index15].AHBClocksEnable);
                    while(!SysCtlPeripheralReady(Config->CanConfigSet.CanController[index15].CanCpuClockRef[index15].AHBClocksEnable)){};
                    CANInit(Config->CanConfigSet.CanController[index15].CanControllerBaseAddress);
                    /*VIP related to unsent objects*/

                          Bit_Time_Parameters0.ui32SyncPropPhase1Seg=(CanContainer.CanConfigSet.CanController[index15].
                                    CanControllerDefaultBaudrate->CanControllerSeg1) + (CanContainer.CanConfigSet.CanController[index15].
                                            CanControllerDefaultBaudrate->CanControllerPropSeg);
                              Bit_Time_Parameters0.ui32Phase2Seg=CanContainer.CanConfigSet.CanController[index15].
                                      CanControllerDefaultBaudrate->CanControllerSeg2;
                              Bit_Time_Parameters0.ui32SJW=CanContainer.CanConfigSet.CanController[index15].
                                      CanControllerDefaultBaudrate->CanControllerSyncJumpWidth;
                              /*uint32_t x;
                              x= SysCtlClockGet();*/
                              Bit_Time_Parameters0.ui32QuantumPrescaler= SysCtlClockGet()/((Bit_Time_Parameters0.ui32SyncPropPhase1Seg
                                      +Bit_Time_Parameters0.ui32Phase2Seg+1U)
                                      *Config->CanConfigSet.CanController[index15].CanControllerDefaultBaudrate->CanControllerBaudRate*1000U);
                              CANBitTimingSet(CanContainer.CanConfigSet.CanController[index15].CanControllerBaseAddress,
                                                         &Bit_Time_Parameters0);
                              CANDisable(CanContainer.CanConfigSet.CanController[index15].CanControllerBaseAddress);

                            /*CAN0_CTL_R|=0x80;
                            CAN0_TST_R|=0x10;*/

                            /*Int_DisableCount[i]=1;*/

                          /*Can_DisableControllerInterrupts(i);*//*responsible for incrementing disableinterrupt
                          so that can enable_interrupt can execute*/
                        if(index15==0U)
                        {
                            /* One-time writable registers that require
                            initialisation directly after reset shall be initialised by the startup code.*/

                              CANIntRegister(Config->CanConfigSet.CanController[index15].CanControllerBaseAddress,
                                       (&Can0_InterruptHandler));
                        }
                        else {
                                CANIntRegister(Config->CanConfigSet.CanController[index15].CanControllerBaseAddress,
                                               (&Can1_InterruptHandler));
                             }
                }

                CanUnitState = CAN_READY ;
                /*[SWS_Can_00250] The function Can_Init shall initialize:  static variables, including flags,
                  Common setting for the complete CAN HW unitCAN controller specific settings for each CAN controller
                  [SWS_Can_00246] The function Can_Init shall change the module state to
                  CAN_READY, after initialising all controllers inside the HW
                  Unit.*/
                config_transmit_objects();
                Recieve_objects_config();


        /* after you have configured some/all the can controllers in your module set this general flag*/
        for(index16 = 0U; index16<NUM_OF_CAN_CONTROLLERS; index16++)
            /* which means that you have made your module ready , used soon as check*/
        {
                /* only function can_Init can change controller state from uninit to stopped*/
                Can_ControllerMode [index16]=CAN_CS_STOPPED;
              /*responsible for incrementing disable_interrupt so that can enable_interrupt can execute
            [SWS_Can_00259]  The function Can_Init shall set all CAN controllers in the state
            STOPPED.*/
        }
            }
        else{
            CanDevolpmentErrorType=CAN_E_TRANSITION;
            }
       }

    else
    {
         CanDevolpmentErrorType=CAN_E_TRANSITION;
        /* [SWS_Can_00174] If development error detection for the Can module is enabled:
         The function Can_Init shall raise the error CAN_E_TRANSITION if the driver
       is not in state CAN_UNINIT.*/
    }
 }


void Can_DeInit(void)
{
    if(CanUnitState == CAN_READY ) /*[SWS_Can_91011]  development error detection for the Can module is enabled:
                                     The function Can_DeInit shall raise the error CAN_E_TRANSITION if the
                                       driver is not in state CAN_READY.(SRS_BSW_00369) */
    {
        /*[SWS_Can_91012] âŒˆIf development error detection for the Can module is enabled: The function Can_DeInit shall
        raise the error CAN_E_TRANSITION if any of the CAN controllers is in state STARTED.*/
      /*  Caveat: Caller of the Can_DeInit function has to be sure no CAN controller is in the state STARTED*/

        if  ((Can_ControllerMode [0U]!= CAN_CS_STARTED) && ( Can_ControllerMode[1U]!= CAN_CS_STARTED))
        {
        CanUnitState = CAN_UNINIT ;  /*   [SWS_Can_ 91009] The function Can_DeInit shall change the module state to
                               CAN_UNINIT before de-initialising all controllers inside the HW unit.*/

        uint8_t index17;
        uint8_t index18 ;
        for (index17 = 0U; index17<NUM_OF_CAN_CONTROLLERS; index17++)
        {
            CANInit(CanContainer.CanConfigSet.CanController[index17].CanControllerBaseAddress);
            SysCtlPeripheralDisable(CanContainer.CanConfigSet.CanController[index17].CanControllerBaseAddress);
        }
        for(index18 = 0U; index18<NUM_OF_CAN_CONTROLLERS; index18++)
        {
            Can_ControllerMode [index18]= CAN_CS_UNINIT  ;
            /*[SWS_Can_91010] The function Can_DeInit shall set all CAN controllers in the state UNINIT*/
        }
    }
        else{
            CanDevolpmentErrorType=CAN_E_TRANSITION;
            }
    }
    else
    {
         CanDevolpmentErrorType=CAN_E_TRANSITION;
    }
}
