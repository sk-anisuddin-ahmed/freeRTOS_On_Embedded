#include "FreeRTOS.h"
#include "task.h"

void vApplicationIdleHook(void) 
{
    
}

int main() 
{
    vTaskStartScheduler();
    return 0;
}