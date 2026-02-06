#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void vUARTTask(void *pvParameters)
{
    for(;;)
    {
        printf("UART: Sending data\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vSPITask(void *pvParameters)
{
    for(;;)
    {
        printf("SPI: Sending data\n");
        vTaskDelay(pdMS_TO_TICKS(1200));
    }
}

void vI2CTask(void *pvParameters)
{
    for(;;)
    {
        printf("I2C: Sending data\n");
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

int main()
{
    xTaskCreate(vUARTTask, "UART", 128, NULL, 2, NULL);
    xTaskCreate(vSPITask, "SPI", 128, NULL, 2, NULL);
    xTaskCreate(vI2CTask, "I2C", 128, NULL, 2, NULL);
    vTaskStartScheduler();
    return 0;
}