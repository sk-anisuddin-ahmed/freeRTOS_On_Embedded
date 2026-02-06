#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

typedef struct { 
    int value; 
} MyMsg_t;
QueueHandle_t xMailbox;

void vSenderTask(void *pvParameters)
{
    MyMsg_t msg = {42};
    xQueueOverwrite(xMailbox, &msg);
    vTaskDelete(NULL);
}

void vReceiverTask(void *pvParameters)
{
    MyMsg_t msg;
    if(xQueueReceive(xMailbox, &msg, portMAX_DELAY) == pdTRUE)
    {
        
    }
    vTaskDelete(NULL);
}

int main()
{
    xMailbox = xQueueCreate(1, sizeof(MyMsg_t));
    xTaskCreate(vSenderTask, "Sender", 1000, NULL, 1, NULL);
    xTaskCreate(vReceiverTask, "Receiver", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}