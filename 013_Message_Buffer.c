#include "FreeRTOS.h"
#include "message_buffer.h"
#include "task.h"

MessageBufferHandle_t xMessageBuffer;

void vSenderTask(void *pvParameters)
{
    const char *msg = "World";
    xMessageBufferSend(xMessageBuffer, msg, 5, portMAX_DELAY);
    vTaskDelete(NULL);
}

void vReceiverTask(void *pvParameters)
{
    char buf[10] = {0};
    xMessageBufferReceive(xMessageBuffer, buf, 5, portMAX_DELAY);
    vTaskDelete(NULL);
}

int main()
{
    xMessageBuffer = xMessageBufferCreate(20);
    xTaskCreate(vSenderTask, "Sender", 1000, NULL, 1, NULL);
    xTaskCreate(vReceiverTask, "Receiver", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}