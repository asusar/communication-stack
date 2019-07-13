/*
 * KeyPad.h
 *
 *  keyPad 4x4 driver.
 *  runs on tm4c123gh6pm using CODECOMPOSERSTUDIO
 *  ****************************************************
 *  WIRING:                                            *
 *  keyPad numbering from left to right 8, 7, .., 2, 1 *
 *                                                     *
 *  8-----PE3                                          *
 *  7-----PE2                                          *
 *  6-----PE1                                          *
 *  5-----PE0                                          *
 *  4-----PC7                                          *
 *  3-----PC6                                          *
 *  2-----PC5                                          *
 *  1-----PC4                                          *
 *******************************************************
 *  Created on: 23 NOV 2017                            *
 *  Sarea Al Hariri                                    *
 *  ****************************************************
 */


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KEYPAD_ROW  GPIO_PORTE_DATA_R
#define KEYPAD_COL  GPIO_PORTC_DATA_R



/* this function initializes
 * the ports connected to the keypad
 *
 */
void keypad_init(void) ;
/********************************************************************************/
/* this is non blocking function check if
 * any key is pressed in the keypad.
 * input:  void
 * return: 0 not pressed
 *          1 if pressed
 *
 */
uint32_t KeyPressed(void) ;
/********************************************************************************/
/* testing keypad init and KeyPressed functions
 * this test use the terminal and send "pressed"
 * or "not pressed" depending on the state of
 * keyPad
 *
 * input: void
 * return: void
 *
 */
void test1 (void) ;
/********************************************************************************/
/*
 * GetKey function check if any key
 * is pressed in the keypad and return
 * the corresponding character
 * input: void
 * return: uint32_t
 *
 */
uint8_t GetKey(void) ;
/********************************************************************************/
/*
 * testing kepad init and GetKey function
 * this test use the terminal and send the character
 * pressed on the keyPad
 * input: void
 * return: void
 *
 */
void test2(void) ;
/********************************************************************************/



#endif /* KEYPAD_H_ */
