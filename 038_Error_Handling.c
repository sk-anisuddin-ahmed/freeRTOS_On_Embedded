#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void vErrorTask(void *pvParameters)
{
    int error = 0;
    for(;;)
    {
        if(error)
        {
            printf("Error detected!\n");
            error = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    xTaskCreate(vErrorTask, "Error", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}