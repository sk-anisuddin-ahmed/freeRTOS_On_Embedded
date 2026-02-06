#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t xUartMutex;

void vUartTask1(void *pvParameters)
{
    for(;;)
    {
        if(xSemaphoreTake(xUartMutex, portMAX_DELAY))
        {
            
            xSemaphoreGive(xUartMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vUartTask2(void *pvParameters)
{
    for(;;)
    {
        if(xSemaphoreTake(xUartMutex, portMAX_DELAY))
        {
            
            xSemaphoreGive(xUartMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}

int main()
{
    xUartMutex = xSemaphoreCreateMutex();
    xTaskCreate(vUartTask1, "UART1", 128, NULL, 2, NULL);
    xTaskCreate(vUartTask2, "UART2", 128, NULL, 2, NULL);
    vTaskStartScheduler();
    return 0;
}