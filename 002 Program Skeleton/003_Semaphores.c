#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t xSemaphore;

void vTask1(void *pvParameters) 
{
    while (1) 
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) 
        {
            xSemaphoreGive(xSemaphore);
        }
    }
}

void vTask2(void *pvParameters) 
{
    while (1) 
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) 
        {
            xSemaphoreGive(xSemaphore);
        }
    }
}

int main() 
{
    xSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemaphore);
    xTaskCreate(vTask1, "Task1", 1000, NULL, 1, NULL);
    xTaskCreate(vTask2, "Task2", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}