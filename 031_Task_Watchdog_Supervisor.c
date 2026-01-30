#include "FreeRTOS.h"
#include "task.h"

volatile int heartbeat = 0;

void vWorkerTask(void *pvParameters)
{
    for(;;)
    {
        heartbeat = 1;
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vSupervisorTask(void *pvParameters)
{
    for(;;)
    {
        if(heartbeat)
        {
            heartbeat = 0;
        }
        else
        {
            
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    xTaskCreate(vWorkerTask, "Worker", 128, NULL, 2, NULL);
    xTaskCreate(vSupervisorTask, "Supervisor", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}