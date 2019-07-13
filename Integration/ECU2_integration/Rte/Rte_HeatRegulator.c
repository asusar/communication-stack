#include "Rte.h"
#include "Rtetypes.h"
#include "Rte_HeatRegulator.h"



uint8 key ;
uint32  count=0;
uint32 flag1 =0;
uint32 send_value =0;
uint32 send_val =0;
uint32 send_va =0;
uint8  arry [10];

int o=0;
/* WRITE YOUR CODE DOWN HERE */



void HeatRegulatorRunnable()
{ o=0;
        Rte_IRead_HeatRegulator_HeatRegulatorRunnable_RegulatorIO_RegulatorValue(&key);

         if ((key == 0) && (flag1 ==0))
         {
         }
         else if ((key == '1') ||(key == '2')|| (key == '3')||(key == '4')||(key == '5')||(key == '6')||(key == '7')||(key == '8')||(key == '9') ||(key == '0'))
         {   flag1 =1;
             arry[0] = key;

               o++;
             while (key != 0 )
             {
                 Rte_IRead_HeatRegulator_HeatRegulatorRunnable_RegulatorIO_RegulatorValue(&key);
             }

         }

         if   ( (flag1 ==1) && (key==0) )
         {
             while (key == 0 )
                         {
                             Rte_IRead_HeatRegulator_HeatRegulatorRunnable_RegulatorIO_RegulatorValue(&key);
                         }
             count =key;
             while (key != 0 )
                          {
                              Rte_IRead_HeatRegulator_HeatRegulatorRunnable_RegulatorIO_RegulatorValue(&key);
                          }

                        arry[1] = count;
                        flag1 =0;
                      arry[2]= 0;
                      send_value = arry[0] -'0';
                      send_val = arry[1] -'0';
                    send_va=(send_value*10)+send_val;
         }
         Rte_Write_Position_Position( & send_va);
}
