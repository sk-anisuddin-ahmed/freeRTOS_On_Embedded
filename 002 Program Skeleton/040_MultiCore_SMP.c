#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void vCore0Task(void *pvParameters)
{
    for(;;)
    {
        printf("Task running on Core 0\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vCore1Task(void *pvParameters)
{
    for(;;)
    {
        printf("Task running on Core 1\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    TaskHandle_t xCore0Handle, xCore1Handle;
    xTaskCreate(vCore0Task, "Core0Task", 128, NULL, 2, &xCore0Handle);
    xTaskCreate(vCore1Task, "Core1Task", 128, NULL, 2, &xCore1Handle);
    vTaskStartScheduler();
    return 0;
}