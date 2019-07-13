#include "Rte.h"
#include "Rtetypes.h"
#include "include/Com.h"





Std_ReturnType Rte_Read_LeftLevelReceiver_Left_Level_Heater (UnsignedInteger_8* data)
	{

		return Com_ReceiveSignal( controlheatleft , data ) ;
	}

Std_ReturnType Rte_Read_RightLevelReceiver_Right_Level_Interface (UnsignedInteger_8* data)
	{

		return Com_ReceiveSignal( controlheatright , data ) ;
	}

Std_ReturnType Rte_Write_StatusLeft_PassengerOnLeftSeat (Boolean* data)
	{

		return Com_SendSignal( seatstatusleft , data ) ;
	}

Std_ReturnType Rte_Write_StatusRight_PassengerOnRightSeat (Boolean* data)
	{

		return Com_SendSignal( seatstatusright , data ) ;
	}

Std_ReturnType Rte_Read_SeatSensorLeft_SeatSensorRunnableLeft_SensorLeft_LeftSensorValue(Boolean * data)
{
   *data= PORTF_SSL();
return  E_OK;
}

Std_ReturnType Rte_Read_SeatSensorRight_SeatSensorRunnableRight_SensorRight_RightSensorValue(Boolean * data)
{
    *data= PORTF_SSR();
  return  E_OK;
}

