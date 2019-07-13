#ifndef RTE_HEADER_H_
#define RTE_HEADER_H_

#include "Rtetypes.h"

Std_ReturnType Rte_Write_Position_Position (UnsignedInteger_32* data);

Std_ReturnType Rte_Read_RegulatorPosition_Position (UnsignedInteger_32* data);

Std_ReturnType Rte_Read_LeftSeatStatus_PassengerOnLeftSeat (Boolean* data);

Std_ReturnType Rte_Read_RightSeatStatus_PassengerOnRightSeat (Boolean* data);

Std_ReturnType Rte_Write_RightLevel_Right_Level_Interface (UnsignedInteger_8* data);

Std_ReturnType Rte_Write_LeftLevel_Left_Level_Heater (UnsignedInteger_8* data);



#endif