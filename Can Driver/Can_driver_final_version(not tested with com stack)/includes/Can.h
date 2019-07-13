/*
 * Can.h
 *
 *  Created on: May 3, 2018
 */

#ifndef INCLUDES_CAN_H_
#define INCLUDES_CAN_H_
#include "Can_Cfg.h"
#include "ComStack_Types.h"
#pragma CHECK_MISRA("none")
#include "Mcu_Cfg.h"
#include "Can_GeneralTypes.h"
#pragma RESET_MISRA("all")
/* shall not be included here */
/*[SWS_Can_00435] The Can.h file shall include Can_GeneralTypes.h.*/



void Can_Init(Can_ConfigType* Config);
Std_ReturnType Can_SetBaudrate(uint8_t Controller,
                               uint16_t BaudRateConfigID );
void Can_EnableControllerInterrupts(uint8_t Controller);
void Can_DisableControllerInterrupts(uint8_t Controller);
Std_ReturnType Can_SetControllerMode( uint8_t Controller,
                                      Can_StateTransitionType Transition );
Std_ReturnType Can_Write( Can_HwHandleType HTH,
                            Can_PduType* PduInfo );
void  Can_Main_Function_Write(void);
void  Can_Main_Function_Read(void);
void Can_MainFunction_Mode(void);
void Can_MainFunction_BusOff(void);
Std_ReturnType Can_GetControllerMode( uint8_t Controller, Can_ControllerStateType* ControllerModePtr);
void Can_DeInit(void);
Std_ReturnType Can_GetControllerErrorState( uint8_t ControllerId, Can_ErrorStateType* ErrorStatePtr);

#endif /* INCLUDES_CAN_H_ */
