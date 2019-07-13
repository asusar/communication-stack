#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* Here is a good place to include header files that are required across
your application. */

#include "OS/include/Config.h"

/* Scheduler configuration using in ASU AUTOSAR OS */


#define configCPU_CLOCK_HZ                      CPU_CLOCK_HZ
#define configTICK_RATE_HZ                      (1000000/OSTICKDURATION)
#define configMAX_PRIORITIES            NUMBER_OF_PRIORITES
#define configUSE_PREEMPTION                    1
/* Interrupt nesting behaviour configuration. */

#define configKERNEL_INTERRUPT_PRIORITY         ( 7 << 5 )    /* Priority 1, only the top three bits are implemented.  This is the highest priority. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY     ( 5 << 5 )  /* Priority 1, only the top three bits are implemented. */
/* in the ARM CM4F only the last three bits is considered to set priority
 * SYSCALL priority 1 that mean that the register BASEPRI is set by 1
 * that mean that any interrupt has priority value higher than or equal to 1 will be disabled (masked)
 * it using to made critical section bu using DisableAllInterrupt() */


/* freeRTOS config they should be defined to avoid error */
/* TODO: Clear all the files and definitions related to freeRTOS
 * with keeping the definition that using in portable files*/

#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#define configUSE_TICKLESS_IDLE                 0

#define configMINIMAL_STACK_SIZE                32
#define configMAX_TASK_NAME_LEN                 16
#define configUSE_16_BIT_TICKS                  0

/* Hook function related definitions. */
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0


#endif /* FREERTOS_CONFIG_H */
