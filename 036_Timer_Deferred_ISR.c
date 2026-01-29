#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"
#include <stdio.h>

TimerHandle_t xTimer;

void vTimerCallback(TimerHandle_t xTimer)
{
    printf("Deferred ISR: Timer callback executed\n");
}

void vISR(void)
{
    // Simulate ISR triggering timer
    xTimerStart(xTimer, 0);
}

int main()
{
    xTimer = xTimerCreate("DeferredISR", pdMS_TO_TICKS(1000), pdFALSE, NULL, vTimerCallback);
    vTaskStartScheduler();
    // Simulate ISR event
    vISR();
    return 0;
}