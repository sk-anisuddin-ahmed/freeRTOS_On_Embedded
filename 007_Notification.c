#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t xTaskToNotify;

void vTask1(void *pvParameters) 
{
    while (1) 
    {
        xTaskNotifyGive(xTaskToNotify);
    }
}

void vTask2(void *pvParameters) 
{
    while (1) 
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}

int main() 
{
    xTaskCreate(vTask1, "Task1", 1000, NULL, 1, &xTaskToNotify);
    xTaskCreate(vTask2, "Task2", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}