#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"

TimerHandle_t xTimer;

void vTimerCallback(TimerHandle_t xTimer)
{
    
}

int main()
{
    xTimer = xTimerCreate("Periodic", pdMS_TO_TICKS(1000), pdTRUE, NULL, vTimerCallback);
    xTimerStart(xTimer, 0);
    vTaskStartScheduler();
    return 0;
}