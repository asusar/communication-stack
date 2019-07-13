#include "Rte.h"
#include "Rtetypes.h"
#include "Rte_SeatHeater.h"


uint8 controlright;
uint8 controlleft;
//int temp=0;
int*l;
int s=0 ;
uint8_t si=0 ;
uint8_t su=0 ;

uint8_t arrray[2];

void SeatHeaterRunnable(	)
	{
    Rte_Read_LeftLevelReceiver_Left_Level_Heater(&controlleft);
    Rte_Read_RightLevelReceiver_Right_Level_Interface(&controlright);

          l= &s;

          if ( (controlleft==0U) && (controlright==0U)  )
          {
                              LCD_command(0x80);
                              Delay_ms(2);
                              LCD_data('R');
                              LCD_data('I');
                              LCD_data('G');
                              LCD_data('H');
                              LCD_data('T');
                              LCD_data(' ');
                              LCD_data('S');
                              LCD_data('E');
                              LCD_data('A');
                              LCD_data('T');
                              LCD_data(' ');
                              LCD_data('O');
                              LCD_data('F');
                              LCD_data('F');
                              LCD_data(' ');
                              LCD_data(' ');

                              LCD_command(0xC0);
                              Delay_ms(2);
                              LCD_data('L');
                              LCD_data('E');
                              LCD_data('F');
                              LCD_data('T');
                              LCD_data(' ');
                              LCD_data(' ');
                              LCD_data('S');
                              LCD_data('E');
                              LCD_data('A');
                              LCD_data('T');
                              LCD_data(' ');
                              LCD_data('O');
                              LCD_data('F');
                              LCD_data('F');
                              LCD_data(' ');
                              LCD_data(' ');
                              LCD_data(' ');

         }


          else if ( (controlleft>0) && (controlright>0) )     /// one for left
          {

               si =controlleft /10;
               su = controlleft % 10;
               if(si>2)
               {
                   si=2;
               }

                                          LCD_command(0x80);
                                          Delay_ms(2);
                                          LCD_data('R');
                                          LCD_data('I');
                                          LCD_data('G');
                                          LCD_data('H');
                                          LCD_data('T');
                                          LCD_data(' ');
                                          LCD_data('S');
                                          LCD_data('E');
                                          LCD_data('A');
                                          LCD_data('T');
                                          LCD_data(' ');
                                          LCD_data(si +'0');
                                          LCD_data(su +'0');
                                          LCD_data(' ');
                                          LCD_data('C');
                                          LCD_data(' ');

                                          LCD_command(0xC0);
                                          Delay_ms(2);
                                          LCD_data('L');
                                          LCD_data('E');
                                          LCD_data('F');
                                          LCD_data('T');
                                          LCD_data(' ');
                                          LCD_data(' ');
                                          LCD_data('S');
                                          LCD_data('E');
                                          LCD_data('A');
                                          LCD_data('T');
                                          LCD_data(' ');
                                          LCD_data(si +'0');
                                          LCD_data(su +'0');
                                          LCD_data(' ');
                                          LCD_data('C');
                                          LCD_data(' ');
          }

          else if ( (controlright==0) && (controlleft>0)   )
          {


              si =controlleft /10;
              su = controlleft % 10;
               if(si>2)
                            {
                                si=2;
                            }


                      LCD_command(0x80);
                      Delay_ms(2);
                      LCD_data('R');
                      LCD_data('I');
                      LCD_data('G');
                      LCD_data('H');
                      LCD_data('T');
                      LCD_data(' ');
                      LCD_data('S');
                      LCD_data('E');
                      LCD_data('A');
                      LCD_data('T');
                      LCD_data(' ');
                      LCD_data('O');
                      LCD_data('F');
                      LCD_data('F');
                      LCD_data(' ');
                      LCD_data(' ');
                      LCD_data(' ');

                      LCD_command(0xC0);
                      Delay_ms(2);
                      LCD_data('L');
                      LCD_data('E');
                      LCD_data('F');
                      LCD_data('T');
                      LCD_data(' ');
                      LCD_data(' ');
                      LCD_data('S');
                      LCD_data('E');
                      LCD_data('A');
                      LCD_data('T');
                      LCD_data(' ');
                      LCD_data(si +'0');
                      LCD_data(su +'0');
                      LCD_data(' ');
                      LCD_data(' ');
                      LCD_data(' ');
                      LCD_data(' ');
}
          else  if ((controlright>0) && (controlleft==0)   )
          {

              si =controlright /10;
              su = controlright % 10;
               if(si>2)
                            {
                                si=2;
                            }

              LCD_command(0x80);
              Delay_ms(2);
              LCD_data('R');
              LCD_data('I');
              LCD_data('G');
              LCD_data('H');
              LCD_data('T');
              LCD_data(' ');
              LCD_data('S');
              LCD_data('E');
              LCD_data('A');
              LCD_data('T');
              LCD_data(' ');
              LCD_data(si +'0');
              LCD_data(su +'0');
              LCD_data(' ');
              LCD_data('C');
              LCD_data(' ');


              LCD_command(0xC0);
              Delay_ms(2);
              LCD_data('L');
              LCD_data('E');
              LCD_data('F');
              LCD_data('T');
              LCD_data(' ');
              LCD_data(' ');
              LCD_data('S');
              LCD_data('E');
              LCD_data('A');
              LCD_data('T');
              LCD_data(' ');
              LCD_data('O');
              LCD_data('F');
              LCD_data('F');
              LCD_data(' ');
              LCD_data(' ');
              LCD_data('C');
              LCD_data(' ');
}




	}

