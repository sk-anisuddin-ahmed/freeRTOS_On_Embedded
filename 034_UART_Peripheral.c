#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>

SemaphoreHandle_t xUartMutex;

void vUartTxTask(void *pvParameters)
{
    for(;;)
    {
        if(xSemaphoreTake(xUartMutex, portMAX_DELAY))
        {
            printf("UART TX: Sending data\n");
            xSemaphoreGive(xUartMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vUartRxTask(void *pvParameters)
{
    for(;;)
    {
        if(xSemaphoreTake(xUartMutex, portMAX_DELAY))
        {
            printf("UART RX: Receiving data\n");
            xSemaphoreGive(xUartMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(700));
    }
}

int main()
{
    xUartMutex = xSemaphoreCreateMutex();
    xTaskCreate(vUartTxTask, "UART_TX", 128, NULL, 2, NULL);
    xTaskCreate(vUartRxTask, "UART_RX", 128, NULL, 2, NULL);
    vTaskStartScheduler();
    return 0;
}