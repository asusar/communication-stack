/*
 ============================================================================
 Name        : AVECORE_CANIF.c
 Author      : AVELABS LLC
 Version     : 1
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "CanIf.h"
#include "Can.h"
#include "CanIf_Cbk.h"
#include <string.h>
#include "debug.h"
#include "PduR.h"
#include "txConfirmation_unitTest.h"
#include "AVECORE_CANIF.h"


extern const CanIf_ConfigType CanIf_configTypeInstance;


/*Mina Nabeeh Config
 * for Set Mode Black box unit test
 * */
/*
 * Copy Of Container Types in The CanIF.c
 */

typedef struct
{

Can_ControllerStateType  Controller_Mode;
    CanIf_ChannelGetModeType  PduMode;
} CanIf_ChannelPrivateType;

typedef struct
{
    boolean initRun;
    CanIf_ChannelPrivateType channelData[CANIF_CHANNEL_CNT];
} CanIf_GlobalType;


extern CanIf_GlobalType CanIf_Global;



uint8 arr[]={0xF,0}; /*payload*/

PduInfoType pduInfoTypeInstance = {arr,2}; /*pdu info*/

uint8 arr2[]={0xB,0};

PduInfoType pduInfoTypeInstance2 = {arr2,2};

extern uint8 CAN_BUSY_FLAG;

/*Global Variables*/
/*Ahmed Abdelmoniem Config
 * for Bus Off and Can If transmit
 * */

uint8 databuffer [8] = {0,1,2,3,4,5,6,10};
uint8 databuffer_2 [5] = {8,9,10,11,12};

/*Unit testing functions*/

void Uninit(void)
{
	printf("in case the system in uninitialized the output is: \n");
	CanIf_UnInit ();
	CanIf_RxIndication(HWObj_5,14,8,databuffer);
	printf("----------------------------------------------\n");
}

void invalidcanid (void)
{
	printf("in case the CAN Id entered is invalid the output is: \n");
	CanIf_RxIndication(HWObj_5,1100,8,databuffer);
	printf("----------------------------------------------\n");
}

void invalidhrh (void)
{
	printf("in case the HRH Id entered is invalid the output is: \n");
	CanIf_RxIndication(7,1100,8,databuffer);
	printf("----------------------------------------------\n");
}

void invalidsdu(void)
{
	printf("in case the SDU data entered is invalid the output is: \n");
	CanIf_RxIndication(HWObj_4,14,8,NULL);
	printf("----------------------------------------------\n");
}

void invalidDLC(void)
{
	printf("in case the DLC entered is invalid the output is: \n");
	CanIf_RxIndication(HWObj_4,14,5,databuffer_2);
	printf("----------------------------------------------\n");
}

void correctentry(void)
{
	printf(" ====> valid Data <====: \n");
	CanIf_RxIndication(HWObj_1,14,8,databuffer);
	printf("----------------------------------------------\n");
}


void BusOff_valid(){
	printf("BusOff Valid Test: \n");
	CanIf_ControllerBusOff(0);
	printf("----------------------------------------------\n");
}

void BusOff_uninitialized(){
	printf("BusOff Uninitialized Test: \n");
	CanIf_ControllerBusOff(0);
	printf("----------------------------------------------\n");
}

void BusOff_inv_Contoller(){
	printf("BusOff invalid controller Test: \n");
	CanIf_ControllerBusOff(50);
	printf("----------------------------------------------\n");
}


void BusOff_Offline(){
	printf("BusOff PDU offline Test: \n");
	CanIf_SetPduMode(0,CANIF_GET_OFFLINE);
	CanIf_ControllerBusOff(0);
	printf("----------------------------------------------\n");
}

void BusOff_Test(){
	printf("----------------------------------------------\n");
	printf("BusOff Test: \n");
	printf("----------------------------------------------\n");
	BusOff_uninitialized();
	CanIf_Init(&CanIf_configTypeInstance);
	CanIf_SetControllerMode(0,CANIF_CS_STARTED);
	BusOff_inv_Contoller();
	BusOff_Offline();
	BusOff_valid();
	CanIf_UnInit();
	BusOff_uninitialized();
	printf("----------------------------------------------\n\n");
}

void Can_busy(){
printf("CanIf Transmit CAN BUSY TEST \n");
CAN_BUSY_FLAG = 1;
if(CanIf_Transmit(0,&pduInfoTypeInstance) == E_NOT_OK){
		printf("Return = E_NOT_OK \n");
	}
	else{
		printf("Return = E_OK \n");
	}
printf("----------------------------------------------\n");
}


void Can_free(){
	printf("CanIf Transmit CAN FREE TEST \n");
	if(CanIf_Transmit(0,&pduInfoTypeInstance) == E_NOT_OK){
		printf("Return = E_NOT_OK \n");
	}
	else{
		printf("Return = E_OK \n");
	}
	printf("----------------------------------------------\n");
}

void uninitalized(){
	printf("CanIf Transmit UNINITALIZED TEST \n");
	if(CanIf_Transmit(0,&pduInfoTypeInstance) == E_NOT_OK){
			printf("Return = E_NOT_OK \n");
		}
		else{
			printf("Return = E_OK \n");
		}
	printf("----------------------------------------------\n");
}

void NULL_pdu_inv_ptr(){
	printf("CanIf Transmit NULL PDU INV TEST \n");
	if(CanIf_Transmit(0,NULL) == E_NOT_OK){
			printf("Return = E_NOT_OK \n");
		}
		else{
			printf("Return = E_OK \n");
		}
	printf("----------------------------------------------\n");
}

void Invalid_can_pdu_tx_id(){
	printf("CanIf Transmit INVALID tx ID TEST \n");
	if(CanIf_Transmit(50,&pduInfoTypeInstance) == E_NOT_OK){
			printf("Return = E_NOT_OK \n");
		}
		else{
			printf("Return = E_OK \n");
		}
	printf("----------------------------------------------\n");
}

void CanIf_Transmit_Test(){
	printf("----------------------------------------------\n");
	printf("CanIf Transmit Test: \n");
	printf("----------------------------------------------\n");
	uninitalized();
	CanIf_Init(&CanIf_configTypeInstance);
	CanIf_SetControllerMode(0,CANIF_CS_STARTED);
	NULL_pdu_inv_ptr();
	Invalid_can_pdu_tx_id();
	Can_free();
	Can_busy();
	CanIf_UnInit();
	uninitalized();
	printf("----------------------------------------------\n\n");
}


void rxindication_test(){

		printf("First ----------------------------------------------\n");
		printf("Rx Indication Test: \n");
		printf("----------------------------------------------\n");
		CanIf_Init(&CanIf_configTypeInstance);
		CanIf_SetControllerMode(0,CANIF_CS_STARTED);

        invalidhrh();
		invalidcanid();
		invalidDLC();
		invalidsdu();
		Uninit();

		CanIf_Init(&CanIf_configTypeInstance);
		CanIf_SetControllerMode(0,CANIF_CS_STARTED);
		correctentry();
		CanIf_UnInit();
		printf("Last ----------------------------------------------\n");

}


void uninitTestStart()
{
		CanIf_Global.channelData[0].Controller_Mode=CANIF_CS_UNINIT;
		printf("controller Mode 0 when uninitialized : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		printf("trying to set controller to started : ");
		CanIf_SetControllerMode(0,CANIF_CS_STARTED);
		printf("controller Mode 0 after started when uninitialized : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		printf("\n ------------------------------------ \n");
}

void initTest()
{
	    printf("init function of CANIF Function Test\n");
		printf("controller Mode 0 before Init : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		CanIf_Init(&CanIf_configTypeInstance);
		printf("controller Mode 0 After Init : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		printf("init success\n");
		printf("\n-------------------------------------\n");
}

void startWhenStopped()
{
		CanIf_Global.channelData[0].Controller_Mode=CANIF_CS_STOPPED;
		printf("controller Mode 0 when stopped : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		CanIf_SetControllerMode(0,CANIF_CS_STARTED);
		printf("controller Mode 0 After started : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		printf("\n ------------------------------------ \n");
}

void startWhenSleep()
{
		CanIf_Global.channelData[0].Controller_Mode=CANIF_CS_SLEEP;
		printf("controller Mode 0 when SLEEP : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		CanIf_SetControllerMode(0,CANIF_CS_STARTED);
		printf("controller Mode 0 After started : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		printf("\n ------------------------------------ \n");
}

void startWhenStart()
{
		CanIf_Global.channelData[0].Controller_Mode=CANIF_CS_STARTED;
		printf("controller Mode 0 when STARTED : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		CanIf_SetControllerMode(0,CANIF_CS_STARTED);
		printf("controller Mode 0 After started AGAIN : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		printf("\n ------------------------------------ \n");

}
void SleepWhenStart()
{
		CanIf_Global.channelData[0].Controller_Mode=CANIF_CS_STARTED;
		printf("controller Mode 0 when START : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		CanIf_SetControllerMode(0,CANIF_CS_SLEEP);
		printf("controller Mode 0 After sleep  : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		printf("\n ------------------------------------ \n");
}

void SleepWhenStopped()
{
		CanIf_Global.channelData[0].Controller_Mode=CANIF_CS_STOPPED;
		printf("controller Mode 0 when stopped : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		CanIf_SetControllerMode(0,CANIF_CS_SLEEP);
		printf("controller Mode 0 After sleep : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		printf("\n ------------------------------------ \n");
}

void uninitTestSleep()
{
		CanIf_Global.channelData[0].Controller_Mode=CANIF_CS_UNINIT;
		printf("controller Mode 0 when uninitialized : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		printf("trying to set controller to sleep : ");
		CanIf_SetControllerMode(0,CANIF_CS_STARTED);
		printf("controller Mode 0 after started when uninitialized : %d \n",CanIf_Global.channelData[0].Controller_Mode);
		printf("\n ------------------------------------ \n");
}

void StartCanNetworkTest()
{
		printf("----------------------------------------------\n");
		printf("Start Controller Test: \n");
		printf("----------------------------------------------\n");
		//uninitTestStart();
		initTest();
		startWhenStopped();
		startWhenSleep();
		startWhenStart();
}

void SleepCanNetworkTest()
{
		printf("----------------------------------------------\n");
		printf("Sleep Test: \n");
		printf("----------------------------------------------\n");
		SleepWhenStart();
		SleepWhenStopped();
		uninitTestSleep();
		CanIf_UnInit();
}
extern uint8 CanIf_Pdu_BufferIndex[];
extern CanIf_TxBufferCfg_t TxBufferCfg[];
void BufferTest(){
	printf("Entering Busy\n");
	CAN_BUSY_FLAG = 1;
	CanIf_Transmit(1,&pduInfoTypeInstance);
	CanIf_Transmit(1,&pduInfoTypeInstance2);
	CAN_BUSY_FLAG = 0;
	printf("Exiting Busy\n");
	CanIf_TxConfirmation(0);

	CanIf_TxConfirmation(0);

}
int main(void) {
	/*BlackBoxTest*/
//	BusOff_Test();
//	CanIf_Transmit_Test();
//	rxindication_test();
//	StartCanNetworkTest();
//	SleepCanNetworkTest();
//	runTxConfirmationUnitTest();
//printf("DsssssssssssssssssONE !!");

	//CanIf_Init(&CanIf_configTypeInstance);
	//CanIf_SetControllerMode(0,CANIF_CS_STOPPED);
	//CanIf_ControllerModeIndication(0,CANIF_CS_STOPPED);
	//CanIf_SetControllerMode(0,CANIF_CS_STARTED);
	//CanIf_ControllerModeIndication(0,CANIF_CS_STARTED);
	//BufferTest();
	rxindication_test();

	return EXIT_SUCCESS;
}

/*upper layer notification functions*/
void CanIfBusOffNotification (uint8 Controller){
	printf("BusOff Notification CallOut Called with Controller(%d)\n",Controller);
}
void CanIfCtrlModeIndication (void){}
void CanIfTrcvModeIndication(void){}


/*Upper layer PDUs signaling functions*/
void CanIfUserTxConfirmation (uint32 x){}
void CanIfUserRxIndication (uint8 channel, uint32 pduId, const uint8 *sduPtr, uint8 dlc, Can_IdType canId){
	printf ("upper layer received this data from channel %d with PduId %d , with DLC %d , with CAN Id %d and the data is \n", channel, pduId , dlc , canId );
	printf ("%d %d %d %d %d %d %d %d. \n \n", sduPtr[0], sduPtr[1], sduPtr[2], sduPtr[3], sduPtr[4], sduPtr[5], sduPtr[6], sduPtr[7]);
}

