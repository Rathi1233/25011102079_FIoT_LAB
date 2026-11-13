#ifndef ESP8266_HTTP_H
#define ESP8266_HTTP_H

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stddef.h>

typedef struct
{
    float temperature;
    float humidity;
    float pressure;
    uint8_t valid;
} SensorReadings;

/*
 * Connects ESP8266 to the configured Wi-Fi network and starts an HTTP server
 * on TCP port 80. ip_out receives the station IP reported by AT+CIFSR.
 */
HAL_StatusTypeDef ESP8266_HTTP_Init(UART_HandleTypeDef *huart,
                                    const char *ssid,
                                    const char *password,
                                    char *ip_out,
                                    size_t ip_out_size);

/* Call repeatedly from the main loop to process browser / Node-RED requests. */
void ESP8266_HTTP_Process(UART_HandleTypeDef *huart,
                          const SensorReadings *readings);

#endif
