
 /***************************************************
 *
 * File Name: Com_Asu_Cfg.c
 *
 * Author: AUTOSAR COM Team
 *
 * Date Created: 11 April 2019
 *
 * Description: This is the configuration of the Com_Asu_Configuration struct
 *
 ****************************************************/

#include "include/Std_Types.h"
#include "include/Com_Asu_Types.h"
#include "include/Com_Cfg.h"


Com_Asu_IPdu_type Com_Asu_IPdu[COM_NUM_OF_IPDU];

Com_Asu_Config_type ComAsuConfiguration = {

		.ComIPdu = Com_Asu_IPdu,
		.ComSignal = NULL,
		.ComGroupSignal = NULL
};


