#include "FreeRTOS.h"
#include "task.h"

void vTaskFunction(void *pvParameters) 
{
    while (1) 
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main() 
{
    xTaskCreate(vTaskFunction, "Task", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}