#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

SemaphoreHandle_t xRecursiveMutex;

void vTaskFunction(void *pvParameters)
{
    if(xSemaphoreTakeRecursive(xRecursiveMutex, portMAX_DELAY))
    {
        xSemaphoreGiveRecursive(xRecursiveMutex);
    }
    vTaskDelete(NULL);
}

int main()
{
    xRecursiveMutex = xSemaphoreCreateRecursiveMutex();
    xTaskCreate(vTaskFunction, "Task", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}