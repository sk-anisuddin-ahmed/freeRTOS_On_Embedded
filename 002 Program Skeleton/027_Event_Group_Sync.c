#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"

EventGroupHandle_t xEventGroup;
#define WIFI_READY_BIT (1 << 0)
#define MQTT_READY_BIT (1 << 1)
#define GPS_READY_BIT  (1 << 2)

void vWifiTask(void *pvParameters)
{
    xEventGroupSetBits(xEventGroup, WIFI_READY_BIT);
    vTaskDelete(NULL);
}

void vMqttTask(void *pvParameters)
{
    xEventGroupSetBits(xEventGroup, MQTT_READY_BIT);
    vTaskDelete(NULL);
}

void vGpsTask(void *pvParameters)
{
    xEventGroupSetBits(xEventGroup, GPS_READY_BIT);
    vTaskDelete(NULL);
}

void vMainTask(void *pvParameters)
{
    xEventGroupWaitBits(xEventGroup, WIFI_READY_BIT | MQTT_READY_BIT | GPS_READY_BIT, pdTRUE, pdTRUE, portMAX_DELAY);
    vTaskDelete(NULL);
}

int main()
{
    xEventGroup = xEventGroupCreate();
    xTaskCreate(vWifiTask, "WiFi", 128, NULL, 2, NULL);
    xTaskCreate(vMqttTask, "MQTT", 128, NULL, 2, NULL);
    xTaskCreate(vGpsTask, "GPS", 128, NULL, 2, NULL);
    xTaskCreate(vMainTask, "Main", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}