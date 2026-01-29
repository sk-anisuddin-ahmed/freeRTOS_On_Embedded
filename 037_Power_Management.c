#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void vPowerTask(void *pvParameters)
{
    for(;;)
    {
        printf("Entering low power mode\n");
        // Simulate low power entry
        vTaskDelay(pdMS_TO_TICKS(2000));
        printf("Exiting low power mode\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    xTaskCreate(vPowerTask, "Power", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}