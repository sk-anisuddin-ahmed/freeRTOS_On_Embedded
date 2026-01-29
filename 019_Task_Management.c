#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t xTaskHandle;

void vTaskFunction(void *pvParameters)
{
    vTaskDelay(pdMS_TO_TICKS(100));
    vTaskSuspend(NULL); // Suspend self
    vTaskResume(xTaskHandle); // Resume another
    vTaskDelete(NULL); // Delete self
}

int main()
{
    xTaskCreate(vTaskFunction, "Task", 128, NULL, 1, &xTaskHandle);
    vTaskStartScheduler();
    return 0;
}