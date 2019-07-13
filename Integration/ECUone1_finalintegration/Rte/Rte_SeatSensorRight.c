#include "Rte.h"
#include "Rtetypes.h"
#include "Rte_SeatSensorRight.h"

boolean rightsensor = FALSE;
void SeatSensorRunnableRight(	)

	{
    Rte_Read_SeatSensorRight_SeatSensorRunnableRight_SensorRight_RightSensorValue(&rightsensor);
        Rte_Write_StatusRight_PassengerOnRightSeat(&rightsensor);
	}

