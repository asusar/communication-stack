#include "tm4c123gh6pm.h"
#include "LCD_Header.h"
#pragma CHECK_MISRA("none")
/*int getTotalChars()
        {
        int total_chars = 0;

        for(i = 0; i < charsArrSize; i++)
            if(charsArr[i] != 'n')
                total_chars++;
            else
                break;

        return total_chars;
        }

        //return 1 for true, 0 for false
        int isCursorAtRightmost()
        {

        //special case if no numbers at all, still counts as rightmost
        if( getTotalChars() == 0 && cursor_position == 0)
                return 1;

        //special case for last char
        if( cursor_position == charsArrSize - 1)
                return 1;

        //normal case
        if( getTotalChars() == cursor_position)
                return 1;

        return 0;
        }*/

//This Function is used to send commands to the LCD
void LCD_command(unsigned char command)
{   GPIO_PORTA_DATA_R = 0;     /* RS(0x20) = 0 for cmd, R/W = 0 */
GPIO_PORTC_DATA_R = command;
GPIO_PORTE_DATA_R = command;

GPIO_PORTA_DATA_R = 0x80;    /* pulse E */
Delay_ms(1);             /* Enable pulse Width */
GPIO_PORTA_DATA_R = 0;

if (command < 4)
    Delay_ms(2);         /* command 1 and 2 needs up to 1.64ms */

else
    Delay_Us(40);     /* all others 40 us */
}

void LCD_data( char  data)
{


    GPIO_PORTA_DATA_R = 0x20;    /* RS(0x20) = 1 for data, R/W = 0 */
    GPIO_PORTE_DATA_R = data;
    GPIO_PORTC_DATA_R = data;

        GPIO_PORTA_DATA_R |= 0x80;  // pulse E
    Delay_ms(1);
    GPIO_PORTA_DATA_R = 0;

    Delay_Us(40);
}
/*

void LCD_print_cursor(){

    unsigned int i;
    unsigned char hex;
    for(i=0; i < 32; i++){
        if (cursor_position == i){
            if (i < charsArrSize)
                hex = 0x80 + i;
            else
                hex = 0xC0 + (i-charsArrSize);
            LCD_command(hex);
        }
    }

}


void LCD_move_cursor_right(){

    //skip increment if no chars || if cursor at rightmost number on screen
    if( (getTotalChars() == 0)  || ( isCursorAtRightmost() && getTotalChars() > 0))
        return;

    if(cursor_position == charsArrSize-1 )
        return;

    LED_BLINK(BLUE);
    cursor_position++;
        Display_Data();
}

void LCD_move_cursor_left(){

//check if cursor is at screen max left
    if(cursor_position == 0)
                    return;

    LED_BLINK(BLUE);
    cursor_position--;
        Display_Data();
}*/

void LCD_INIT(){
    SYSCTL_RCGCGPIO_R |=0x1;
    SYSCTL_RCGCGPIO_R |=0x14;
    //Enable Port A&B Clock
          while((SYSCTL_PRGPIO_R & 0x14) == 0){};           //Wait for clock stabilization
             GPIO_PORTC_DIR_R |= 0xFF;
             GPIO_PORTE_DIR_R |= 0xFF;
             GPIO_PORTA_DIR_R |= 0xE0;
             GPIO_PORTC_DEN_R |= 0xFF;
             GPIO_PORTE_DEN_R |= 0xFF;
             GPIO_PORTA_DEN_R |= 0xE0;             ////

             GPIO_PORTC_AMSEL_R &= ~0xFF;
             GPIO_PORTE_AMSEL_R &= ~0xFF;
             GPIO_PORTA_AMSEL_R &= ~0xFF;
             GPIO_PORTC_AFSEL_R &= 0x00;
             GPIO_PORTE_AFSEL_R &= 0x00;
             GPIO_PORTA_AFSEL_R &= 0x00;

            // Wake Up LCD Sequence
        Delay_ms(20);            /* initialization sequence */// Wait >15 ms after power is applied
        LCD_command(0x30);      // command 0x30 = Wake up
        Delay_ms(5);                  // must wait 5ms, busy flag not available

        //Prepare LCD Operation and Function
        LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
        LCD_command(0x01);      /* clear screen, move cursor to home */
      LCD_command(0x0F);

}

/*void resetLCD(){
    //init chars array to 'n's
    for(i = 0; i < charsArrSize; i++)
        charsArr[i] = 'n';
    cursor_position = 0;

        Display_Data();
}

/*void LCD_print_String_1s(char * a){
    int oldCurs;
    char old[charsArrSize];
    for(i = 0; i < charsArrSize; i++)
        old[i] = charsArr[i];
    oldCurs = cursor_position;

        resetLCD();

    for(i = 0; a[i] != '\0'; i++)
        LCD_data( a[i] );

        LED_BLINK(RED);
        Delay_ms(3000000);

        for(i = 0; i < charsArrSize; i++)
            charsArr[i] = old[i];
        cursor_position= oldCurs;

        Display_Data();
}*/

//returns 1 for error detect
/*void Display_Data(){

    LCD_command(0x01);       // clear display

    for(i = 0; charsArr[i] != 'n' && charsArr[i] != '\0' && i < charsArrSize; i++)
        LCD_data(charsArr[i]);

    LCD_print_cursor();
}*/
