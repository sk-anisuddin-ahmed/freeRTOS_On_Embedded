#include "FreeRTOS.h"
#include "task.h"

void vTaskFunction(void *pvParameters) 
{
    while (1) 
    {
        
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) 
{
    
}

int main() 
{
    xTaskCreate(vTaskFunction, "Task", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}