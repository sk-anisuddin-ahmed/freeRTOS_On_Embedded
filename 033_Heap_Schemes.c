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
    // Select heap scheme in FreeRTOSConfig.h (heap_1.c, heap_2.c, heap_4.c, etc.)
    xTaskCreate(vTaskFunction, "HeapCheck", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}