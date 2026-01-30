#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

QueueHandle_t xQueue;

void vProducerTask(void *pvParameters)
{
    int value = 0;
    for(;;)
    {
        xQueueSend(xQueue, &value, portMAX_DELAY);
        value++;
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vConsumerTask(void *pvParameters)
{
    int value;
    for(;;)
    {
        if(xQueueReceive(xQueue, &value, portMAX_DELAY) == pdTRUE)
        {
            
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

int main()
{
    xQueue = xQueueCreate(5, sizeof(int));
    xTaskCreate(vProducerTask, "Producer", 128, NULL, 2, NULL);
    xTaskCreate(vConsumerTask, "Consumer", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}