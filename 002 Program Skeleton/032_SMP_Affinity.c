#include "FreeRTOS.h"
#include "task.h"


void vTaskCore0(void *pvParameters)
{
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vTaskCore1(void *pvParameters)
{
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    TaskHandle_t xHandle0, xHandle1;
    xTaskCreate(vTaskCore0, "Core0", 128, NULL, 1, &xHandle0);
    xTaskCreate(vTaskCore1, "Core1", 128, NULL, 1, &xHandle1);
    
    
    vTaskStartScheduler();
    return 0;
}