#include "Rte.h"
#include "Rtetypes.h"
#include "Rte_SeatSensorLeft.h"


boolean leftsensor = FALSE;
void SeatSensorRunnableLeft( )
	{
        Rte_Read_SeatSensorLeft_SeatSensorRunnableLeft_SensorLeft_LeftSensorValue(&leftsensor );
        Rte_Write_StatusLeft_PassengerOnLeftSeat(&leftsensor);

	}

