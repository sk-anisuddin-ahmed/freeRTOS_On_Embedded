#include "FreeRTOS.h"
#include "task.h"


void vPeriodicTask(void *pvParameters)
{
    for(;;)
    {
        
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vDeadlineTask(void *pvParameters)
{
    for(;;)
    {
        
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

int main()
{
    TaskHandle_t xPeriodic, xDeadline;
    xTaskCreate(vPeriodicTask, "Periodic", 128, NULL, 2, &xPeriodic);
    xTaskCreate(vDeadlineTask, "Deadline", 128, NULL, 3, &xDeadline);
    
    vTaskStartScheduler();
    return 0;
}