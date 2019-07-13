#ifndef RTE_HEADER_H_
#define RTE_HEADER_H_

#include "Rtetypes.h"

Std_ReturnType Rte_Read_LeftLevelReceiver_Left_Level_Heater (UnsignedInteger_8* data);

Std_ReturnType Rte_Read_RightLevelReceiver_Right_Level_Interface (UnsignedInteger_8* data);

Std_ReturnType Rte_Write_StatusLeft_PassengerOnLeftSeat (Boolean* data);

Std_ReturnType Rte_Write_StatusRight_PassengerOnRightSeat (Boolean* data);

Std_ReturnType Rte_Read_SeatSensorLeft_SeatSensorRunnableLeft_SensorLeft_LeftSensorValue(Boolean * data);

Std_ReturnType Rte_Read_SeatSensorRight_SeatSensorRunnableRight_SensorRight_RightSensorValue(Boolean * data);



#endif
