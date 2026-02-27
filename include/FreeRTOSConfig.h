#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION            1
#define configUSE_IDLE_HOOK             1
#define configUSE_TICK_HOOK             0
#define configCPU_CLOCK_HZ              1000000
#define configTICK_RATE_HZ              1000
#define configMAX_PRIORITIES            5
#define configMINIMAL_STACK_SIZE        128
#define configTOTAL_HEAP_SIZE           (10 * 1024)
#define configMAX_TASK_NAME_LEN         16
#define configUSE_MUTEXES               1
#define configUSE_COUNTING_SEMAPHORES   1
#define configCHECK_FOR_STACK_OVERFLOW  2
#define configUSE_MALLOC_FAILED_HOOK    1

#define configTICK_TYPE_WIDTH_IN_BITS   TICK_TYPE_WIDTH_32_BITS

#define configUSE_TIMERS                1      // must be 1 to use xTimerCreate and timers
#define configTIMER_TASK_PRIORITY       2      // priority of the timer task
#define configTIMER_QUEUE_LENGTH        10     // length of the timer command queue
#define configTIMER_TASK_STACK_DEPTH    256    // stack size for timer task
					       //
#define INCLUDE_xTimerPendFunctionCall    1
#define INCLUDE_xTimerGetTimerDaemonTaskHandle 1
#define INCLUDE_xTimerGetExpiryTime       1
#define INCLUDE_xTimerCreate              1
#define INCLUDE_xTimerDelete              1
#define INCLUDE_xTimerReset               1
#define INCLUDE_xTimerStartStop           1
#define INCLUDE_xTimerChangePeriod        1

/* Required for POSIX port */
#define INCLUDE_vTaskDelay 1
#define INCLUDE_vTaskDelayUntil 1

#endif
