/*
 * Interrupt.h
 *
 *  Created on: Mar 2, 2018
 *      Author: Dell
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_


#define ISR(name)       void USR_##name(void);\
                        void name(void){\
                          /*OSIsrEnter();*/\
                          USR_##name();\
                          /*OSIsrExit();*/\
                        }\
                        void USR_##name(void)

#define ISR1(name)      void USR_##name(void);\
                        void name(void){\
                           /*OSIsr1Enter();*/\
                           USR_##name();\
                           /*OSIsr1Exit();*/\
                           }\
                        void USR_##name(void)


#endif /* INTERRUPT_H_ */
