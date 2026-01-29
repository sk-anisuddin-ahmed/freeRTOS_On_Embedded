#include "FreeRTOS.h"
#include "task.h"

// Example for SMP port only
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
    // vTaskCoreAffinitySet(xHandle0, 0x01); // Pin to core 0 (API is port-specific)
    // vTaskCoreAffinitySet(xHandle1, 0x02); // Pin to core 1
    vTaskStartScheduler();
    return 0;
}