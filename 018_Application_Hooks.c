#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void vApplicationIdleHook(void)
{
    printf("Idle Hook called\n");
}

void vApplicationTickHook(void)
{
    static int tickCount = 0;
    tickCount++;
}

void vApplicationMallocFailedHook(void)
{
    printf("Malloc Failed!\n");
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    printf("Stack Overflow in task: %s\n", pcTaskName);
}

void vTaskFunction(void *pvParameters)
{
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    xTaskCreate(vTaskFunction, "Task", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}