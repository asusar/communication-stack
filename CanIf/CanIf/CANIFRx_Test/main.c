#include <stdio.h>
#include <stdlib.h>
#include "Can.h"
#include "CanIf.h"
#include "CanIf_Cbk.h"
#include "CanIf_Cfg.h"
#include "CanIf_Lcfg.h"

#define USE_CANTP  1

void CanTp_RxIndication(uint32 RxPduId , const PduInfoType *PduInfoPtr){
    printf("this is : %d" , RxPduId);
}
int main()
{
    CanIf_RxIndication(1 , 0 , 10 , 8);

    return 0;
}
