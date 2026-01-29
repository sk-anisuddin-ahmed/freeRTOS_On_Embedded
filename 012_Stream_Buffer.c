#include "FreeRTOS.h"
#include "stream_buffer.h"
#include "task.h"

StreamBufferHandle_t xStreamBuffer;

void vSenderTask(void *pvParameters)
{
    const char *msg = "Hello";
    xStreamBufferSend(xStreamBuffer, msg, 5, portMAX_DELAY);
    vTaskDelete(NULL);
}

void vReceiverTask(void *pvParameters)
{
    char buf[10] = {0};
    xStreamBufferReceive(xStreamBuffer, buf, 5, portMAX_DELAY);
    vTaskDelete(NULL);
}

int main()
{
    xStreamBuffer = xStreamBufferCreate(20, 1);
    xTaskCreate(vSenderTask, "Sender", 1000, NULL, 1, NULL);
    xTaskCreate(vReceiverTask, "Receiver", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}