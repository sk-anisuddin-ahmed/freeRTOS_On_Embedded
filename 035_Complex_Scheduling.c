#include "FreeRTOS.h"
#include "task.h"

// Example for EDF/RMS/LLF if port supports
void vPeriodicTask(void *pvParameters)
{
    for(;;)
    {
        // Do periodic work
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vDeadlineTask(void *pvParameters)
{
    for(;;)
    {
        // Do work with deadline
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

int main()
{
    TaskHandle_t xPeriodic, xDeadline;
    xTaskCreate(vPeriodicTask, "Periodic", 128, NULL, 2, &xPeriodic);
    xTaskCreate(vDeadlineTask, "Deadline", 128, NULL, 3, &xDeadline);
    // vTaskSetDeadline(xDeadline, deadline); // API is port-specific
    vTaskStartScheduler();
    return 0;
}