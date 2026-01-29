#include "FreeRTOS.h"
#include "timers.h"

void vTimerCallback(TimerHandle_t xTimer) 
{
    
}

int main() 
{
    TimerHandle_t xTimer = xTimerCreate("Timer", pdMS_TO_TICKS(1000), pdTRUE, NULL, vTimerCallback);
    xTimerStart(xTimer, 0);
    vTaskStartScheduler();
    return 0;
}