#include "FreeRTOS.h"
#include "task.h"

static StaticTask_t xTaskBuffer;
static StackType_t xStack[128];

void vStaticTask(void *pvParameters)
{
    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    xTaskCreateStatic(vStaticTask, "Static", 128, NULL, 1, xStack, &xTaskBuffer);
    vTaskStartScheduler();
    return 0;
}