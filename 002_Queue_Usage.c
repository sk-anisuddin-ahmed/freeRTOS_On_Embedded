#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

QueueHandle_t xQueue;

void vSenderTask(void *pvParameters) 
{
    int valueToSend = 0;
    while (1) 
    {
        xQueueSend(xQueue, &valueToSend, portMAX_DELAY);
    }
}

void vReceiverTask(void *pvParameters)
{
    int receivedValue;
    while (1) 
    {
        xQueueReceive(xQueue, &receivedValue, portMAX_DELAY);
    }
}

int main() 
{
    xQueue = xQueueCreate(10, sizeof(int));
    xTaskCreate(vSenderTask, "Sender", 1000, NULL, 1, NULL);
    xTaskCreate(vReceiverTask, "Receiver", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}