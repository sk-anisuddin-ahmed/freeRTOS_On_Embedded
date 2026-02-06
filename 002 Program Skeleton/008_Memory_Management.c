#include "FreeRTOS.h"
#include "task.h"
#include "portable.h"

void vTaskFunction(void *pvParameters) 
{
    while (1) 
    {
        void *ptr = pvPortMalloc(100);
        vPortFree(ptr);
    }
}

int main() 
{
    xTaskCreate(vTaskFunction, "Task", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}