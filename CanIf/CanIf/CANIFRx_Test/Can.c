#include "Can.h"
#include <stdio.h>

void Can_Init( const Can_ConfigType *Config ){}
void Can_DeInit(void){}
void Can_InitController( uint8 controller, const Can_ControllerConfigType *config){}
Can_ReturnType Can_SetControllerMode( uint8 Controller, Can_StateTransitionType transition ){
	printf("Can_SetControllerMode called  state transition : %d \n",transition);

		return CAN_OK;
}
void Can_DisableControllerInterrupts( uint8 controller ){}
void Can_EnableControllerInterrupts( uint8 controller ){}

uint8 CAN_BUSY_FLAG = 0;

Can_ReturnType Can_Write( Can_Arc_HTHType hth, Can_PduType *pduInfo ){
	/*UINT TEST*/

	printf("Hth = %d\n",hth);
	printf("Can ID = %d\n",pduInfo->id);
	printf("Length = %d\n",pduInfo->length);
	uint8 index = 0;
	for(;index<pduInfo->length;index++){
		printf("Sdu[%d] = %d\n",index,(pduInfo->sdu)[index]);
	}

	printf("Handle = %d\n",pduInfo->swPduHandle);

	//CAN_BUSY_FLAG=1;

	if(CAN_BUSY_FLAG == 1){
		return CAN_BUSY;
	}
	else{
		return CAN_OK;
	}

	/*UINT TEST*/
	}

void Can_Cbk_CheckWakeup( uint8 controller ){}
void Can_MainFunction_Write( void ){}
void Can_MainFunction_Read( void ){}
void Can_MainFunction_BusOff( void ){}
void Can_MainFunction_Error( void ){}
void Can_MainFunction_Wakeup( void ){}

void Can_Arc_GetStatistics( uint8 controller, Can_Arc_StatisticsType * stat){}

Can_TestType *Can_Arc_GetTestInfo( void   ){return 0;}

