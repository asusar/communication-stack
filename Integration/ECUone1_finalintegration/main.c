/*
 * main.c
 */
#pragma diag_push
#pragma CHECK_MISRA("none")

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/uart.h"
#include "OS/include/task.h"
#include "OS/include/event.h"
#include "utils/uartstdio.h"
#include "OS/include/InitConsole.h"
#include <PORTF.h>
#include "include/Com.h"
#include "include/CanTp_Cfg.h"
#include "include/CanTp.h"
#include "include/CanIf.h"
#include "include/Can.h"
#include "Rte/Rte.h"
#include "Dio.h"

extern const Can_ConfigType CanContainer;
extern const CanTp_ConfigType CanTp_Config ;
extern const ComConfig_type ComConfiguration ;
extern const CanIf_ConfigType CanIf_configTypeInstance;

//DeclareTask(T1);
//
//DeclareEvent(RTE_Event_HeatRegulatorEvent);
//DeclareEvent(RTE_Event_HeatingControllerEvent);
//DeclareEvent(BSW_Event_Com_MainFunctionRx);
//DeclareEvent(BSW_Event_Com_MainFunctionTx);
//DeclareEvent(BSW_Event_CanTp_MainFunction);

DeclareTask(T1);

DeclareEvent(RTE_Event_SeatHeaterEvent);
DeclareEvent(RTE_Event_SeatSensorLeftUpdateTimer);
DeclareEvent(RTE_Event_SeatSensorRightUpdateTimer);
DeclareEvent(BSW_Event_Com_MainFunctionRx);
DeclareEvent(BSW_Event_Com_MainFunctionTx);
DeclareEvent(BSW_Event_CanTp_MainFunction);


//DeclareAlarm(alar1);

//#pragma RESET_MISRA("all")


int flag = 0;

    int main(void){
    LCD_INIT();
      LCD_command(0X80);
    PORTF_Init();
    InitGPIO();
    Can_Init(&CanContainer);
    Can_SetControllerMode(CanContainer.CanConfigSet.CanController[0].CanControllerId,CAN_T_START);
    CanTp_Init(&CanTp_Config);
    Com_Init(&ComConfiguration);
    CanIf_Init(&CanIf_configTypeInstance);
    CanIf_SetControllerMode(CanContainer.CanConfigSet.CanController[0].CanControllerId,CAN_CS_STARTED);
    StartOS(OSDEFAULTAPPMODE);
    while(1){}
	return 0;
}


//TASK(T1)
//{
//    EventMaskType NewEvent;
//    while(true)
//    {
//        WaitEvent(BSW_Event_Com_MainFunctionTx );
//        GetEvent(T1, &NewEvent);
//        ClearEvent(NewEvent);
//        if(NewEvent & BSW_Event_Com_MainFunctionTx)
//        {
//            SeatSensorRunnableRight();
//            SeatSensorRunnableLeft();
//            SeatHeaterRunnable();
//            Com_MainFunctionRx();
//            Com_MainFunctionTx();
//        }
//
//        TerminateTask();
//    }
//}

    TASK(T1)
    {
        EventMaskType NewEvent;
        while(true)
        {
            WaitEvent(RTE_Event_SeatHeaterEvent | RTE_Event_SeatSensorLeftUpdateTimer | RTE_Event_SeatSensorRightUpdateTimer | BSW_Event_Com_MainFunctionRx | BSW_Event_Com_MainFunctionTx);
            GetEvent(T1, &NewEvent);
            ClearEvent(NewEvent);
            if(NewEvent & RTE_Event_SeatHeaterEvent)
            {
                SeatHeaterRunnable();
            }
            if(NewEvent & RTE_Event_SeatSensorLeftUpdateTimer)
            {
                SeatSensorRunnableLeft();
            }
            if(NewEvent & RTE_Event_SeatSensorRightUpdateTimer)
            {
                SeatSensorRunnableRight();
            }
            if(NewEvent & BSW_Event_Com_MainFunctionRx)
            {
                Com_MainFunctionRx();
            }
            if(NewEvent & BSW_Event_Com_MainFunctionTx)
            {
                Com_MainFunctionTx();
            }
//            if(NewEvent & BSW_Event_CanTp_MainFunction)
//            {
//                CanTp_MainFunction();
//            }
        }
        TerminateTask();
    }
