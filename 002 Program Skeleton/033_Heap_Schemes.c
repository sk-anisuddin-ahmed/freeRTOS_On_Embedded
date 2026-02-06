#include "FreeRTOS.h"
#include "task.h"
#include "portable.h"

void vTaskFunction(void *pvParameters)
{
    size_t heap = xPortGetFreeHeapSize();
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    
    xTaskCreate(vTaskFunction, "HeapCheck", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}