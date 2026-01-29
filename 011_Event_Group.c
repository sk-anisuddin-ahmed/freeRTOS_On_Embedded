#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"

EventGroupHandle_t xEventGroup;

void vTask1(void *pvParameters)
{
    xEventGroupSetBits(xEventGroup, 0x01);
    vTaskDelete(NULL);
}

void vTask2(void *pvParameters)
{
    xEventGroupWaitBits(xEventGroup, 0x01, pdTRUE, pdFALSE, portMAX_DELAY);
    vTaskDelete(NULL);
}

int main()
{
    xEventGroup = xEventGroupCreate();
    xTaskCreate(vTask1, "Task1", 1000, NULL, 1, NULL);
    xTaskCreate(vTask2, "Task2", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}