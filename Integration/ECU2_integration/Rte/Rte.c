#include "Rte.h"
#include "Rtetypes.h"
#include "include/Com.h"
#include "KeyPad.h"


UnsignedInteger_32 Position ;


Std_ReturnType Rte_Write_Position_Position (UnsignedInteger_32* data)
	{
		Position = * data ;
		return RTE_E_OK ;
	}

Std_ReturnType Rte_Read_RegulatorPosition_Position (UnsignedInteger_32* data)
	{
		* data = Position ;
		return RTE_E_OK ;
	}

Std_ReturnType Rte_Read_LeftSeatStatus_PassengerOnLeftSeat (Boolean* data)
	{

		return Com_ReceiveSignal( passengeronleft , data ) ;
	}

Std_ReturnType Rte_Read_RightSeatStatus_PassengerOnRightSeat (Boolean* data)
	{

		return Com_ReceiveSignal( passengeronright , data ) ;
	}

Std_ReturnType Rte_Write_RightLevel_Right_Level_Interface (UnsignedInteger_8* data)
	{

		return Com_SendSignal( heatright , data ) ;
	}

Std_ReturnType Rte_Write_LeftLevel_Left_Level_Heater (UnsignedInteger_8* data)
	{

		return Com_SendSignal( heatleft , data ) ;
	}

/* this is an autosar violatiob because we donthave DIO stack
   if we have DIO stack this API should connected to the DIO stack
 */
Std_ReturnType Rte_IRead_HeatRegulator_HeatRegulatorRunnable_RegulatorIO_RegulatorValue( UnsignedInteger_8* data)
{
    * data = GetKey ();
    return RTE_E_OK;
}
