#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

volatile int dma_done = 0;

void vDMATask(void *pvParameters)
{
    for(;;)
    {
        if(dma_done)
        {
            printf("DMA transfer complete\n");
            dma_done = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vDMA_ISR(void)
{
    dma_done = 1;
}

int main()
{
    xTaskCreate(vDMATask, "DMA", 128, NULL, 2, NULL);
    vTaskStartScheduler();
    // Simulate DMA interrupt
    vDMA_ISR();
    return 0;
}