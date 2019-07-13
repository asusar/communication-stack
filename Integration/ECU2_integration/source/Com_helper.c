#include "include/Std_Types.h"
#include "include/Com_Types.h"
#include "include/Com_helper.h"
#include "include/Com_Cfg.h"

boolean validateSignalID (Com_SignalIdType SignalId)
{
	if(SignalId<COM_NUM_OF_SIGNAL)
		return TRUE;
	return FALSE;
}


uint64 power(uint8 x,uint8 y)
{
	uint64 result = x;

	if (y == 0)
		return 1;

	for (; y>1 ; y--)
	{
		result = result * x;
	}
	return result;
}


//boolean compare_float(uint64 f1, uint64 f2)
//{
// float precision = 0.0001;
// if (((f1 - precision) < f2) &&
//     ((f1 + precision) > f2))
//  {
//   return TRUE;
//  }
// else if ((f1-precision)>f2 && (f1+precision)>f2){
//     return TRUE;
// }
// else
//  {
//   return FALSE;
//  }
//}
