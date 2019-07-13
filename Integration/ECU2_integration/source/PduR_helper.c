/*
 * PduR_helper.c
 *
 *  Created on: Apr 28, 2019
 *      Author: lenovo
 */

#include "include/PduR_cfg.h"
#include "include/PduR_helper.h"
#include "include/PduR.h"

int virtual_com[] =  {vcom};
int real_com[] =      {com_real};

int virtual_CanIf[] =   { vcanf_R };
int real_CanIf[] =      { rcanf_R};

int virtual_CanTp_rx[] =   { vcantp_com_rx};
int real_CanTp_rx[] =      { rcantp_com_rx};

int virtual_CanTp_tx[] =   { vcantp_TXcopy_com};
int real_CanTp_tx[] =      { rcantp_TXcopy_com};

int Com_type[] =        {com_type};



uint8_t get_ID(uint32_t source_id , type_t source )
{
     uint32_t i =0 ;
    if (source == Com )
     {
        for(i =0;  i< sizeof(real_com); i++)
         {
            if (virtual_com[i] == source_id)
            {
                return real_com[i];
            }
         }
     }
    else if (source == CanIF)
     {
        for(i =0 ;  i<sizeof( real_CanIf) ; i++)
           {
              if (virtual_CanIf[i] == source_id)
                          {
                              return real_CanIf[i] ;
                          }
           }
     }
    else if (source == CanTp_COM )
     {
            for(i =0 ;  i<sizeof(real_CanTp_rx) ; i++)
             {
                if (virtual_CanTp_rx[i] == source_id)
                {
                    return real_CanTp_rx[i] ;
                }
             }
     }
    else if (source == CanTp_TXCopy )
     {
            for(i =0 ;  i< sizeof(real_CanTp_tx) ; i++)
             {   uint8_t x = virtual_CanTp_tx[i] ;
                if ( x== source_id)
                {
                    return real_CanTp_tx[i] ;
                }

             }
     }

 }

type_t  get_type(uint32_t source_id, type_t source)
{
    uint32_t i =0 ;
        if (source == Com )
         {
            for(i =0;  i< sizeof(real_com); i++)
             {
                if (virtual_com[i] == source_id)
                {
                    return Com_type[i];
                }
             }
         }
}

