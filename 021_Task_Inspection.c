#include "FreeRTOS.h"
#include "task.h"

void vTaskFunction(void *pvParameters)
{
    char buf[128];
    vTaskList(buf); 
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    xTaskCreate(vTaskFunction, "Inspect", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}