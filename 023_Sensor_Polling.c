#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void vSensorTask(void *pvParameters)
{
    for(;;)
    {
        int sensor_value = 123; // Simulate sensor read
        printf("Sensor value: %d\n", sensor_value);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main()
{
    xTaskCreate(vSensorTask, "Sensor", 128, NULL, 2, NULL);
    vTaskStartScheduler();
    return 0;
}