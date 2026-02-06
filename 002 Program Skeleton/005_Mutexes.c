#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t xMutex;

void vTask1(void *pvParameters) 
{
    while (1) 
    {
        if (xSemaphoreTake(xMutex, portMAX_DELAY)) 
        {
            xSemaphoreGive(xMutex);
        }
    }
}

void vTask2(void *pvParameters) 
{
    while (1) 
    {
        if (xSemaphoreTake(xMutex, portMAX_DELAY)) 
        {
            xSemaphoreGive(xMutex);
        }
    }
}

int main() 
{
    xMutex = xSemaphoreCreateMutex();
    xTaskCreate(vTask1, "Task1", 1000, NULL, 1, NULL);
    xTaskCreate(vTask2, "Task2", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}