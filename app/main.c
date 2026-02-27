#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "timers.h"

/* ------------------ Configuration ------------------ */
#define SENSOR_TASK_PERIOD_MS    1000
#define MONITOR_TASK_PERIOD_MS   1500
#define EVENT_SENSOR_READY       (1 << 0)

/* ------------------ Global Handles ----------------- */
QueueHandle_t sensorQueue;
SemaphoreHandle_t printMutex;
EventGroupHandle_t eventGroup;
TimerHandle_t sensorTimer;

/* ------------------ Idle Hook ---------------------- */
void vApplicationIdleHook(void) {}

/* ------------------ Sensor Task -------------------- */
void sensor_task(void *params) {
    int count = 0;
    while (1) {
        count++;

        // Send data to queue
        xQueueSend(sensorQueue, &count, 0);

        // Set sensor ready event
        xEventGroupSetBits(eventGroup, EVENT_SENSOR_READY);

        // Delay
        vTaskDelay(pdMS_TO_TICKS(SENSOR_TASK_PERIOD_MS));
    }
}

/* ------------------ Monitor Task ------------------- */
void monitor_task(void *params) {
    int received;
    while (1) {
        // Wait for sensor event
        xEventGroupWaitBits(eventGroup, EVENT_SENSOR_READY, pdTRUE, pdFALSE, portMAX_DELAY);

        // Read from queue
        if (xQueueReceive(sensorQueue, &received, 0) == pdPASS) {
            xSemaphoreTake(printMutex, portMAX_DELAY);
            printf("[Monitor] Sensor Value: %d, Free Heap: %lu\n",
                   received, (unsigned long)xPortGetFreeHeapSize());
            xSemaphoreGive(printMutex);
        }

        vTaskDelay(pdMS_TO_TICKS(MONITOR_TASK_PERIOD_MS));
    }
}

/* ------------------ Timer Callback ----------------- */
void sensor_timer_callback(TimerHandle_t xTimer) {
    xSemaphoreTake(printMutex, portMAX_DELAY);
    printf("[Timer] Sensor timer triggered!\n");
    xSemaphoreGive(printMutex);
}

/* In main.c or a separate hooks.c */

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    printf("Stack Overflow in task: %s\n", pcTaskName);
    while(1);
}

void vApplicationMallocFailedHook(void) {
    printf("Malloc Failed!\n");
    while(1);
}

/* ------------------ Main --------------------------- */
int main() {
    // Create queue
    sensorQueue = xQueueCreate(10, sizeof(int));

    // Create mutex
    printMutex = xSemaphoreCreateMutex();

    // Create event group
    eventGroup = xEventGroupCreate();

    // Create timer (5-second periodic)
    sensorTimer = xTimerCreate("SensorTimer", pdMS_TO_TICKS(5000), pdTRUE, NULL, sensor_timer_callback);
    xTimerStart(sensorTimer, 0);

    // Create tasks
    xTaskCreate(sensor_task, "SensorTask", 256, NULL, 2, NULL);
    xTaskCreate(monitor_task, "MonitorTask", 256, NULL, 1, NULL);

    // Start scheduler
    vTaskStartScheduler();

    while (1); // Should never reach here
    return 0;
}
