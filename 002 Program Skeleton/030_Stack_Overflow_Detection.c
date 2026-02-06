#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    printf("Stack overflow detected in task: %s\n", pcTaskName);
}

void vOverflowTask(void *pvParameters)
{
    char bigArray[1024]; 
    for(;;)
    {
        bigArray[0] = 1;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    xTaskCreate(vOverflowTask, "Overflow", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}