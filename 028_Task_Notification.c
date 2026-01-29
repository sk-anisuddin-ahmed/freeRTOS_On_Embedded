#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t xReceiverTask;

void vSenderTask(void *pvParameters)
{
    for(;;)
    {
        xTaskNotifyGive(xReceiverTask);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vReceiverTask(void *pvParameters)
{
    for(;;)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        // Received notification
    }
}

int main()
{
    xTaskCreate(vSenderTask, "Sender", 128, NULL, 2, NULL);
    xTaskCreate(vReceiverTask, "Receiver", 128, NULL, 1, &xReceiverTask);
    vTaskStartScheduler();
    return 0;
}