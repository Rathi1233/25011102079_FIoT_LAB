#include "ESP8266_HTTP.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ESP_RX_BUFFER_SIZE 1024U
#define ESP_COMMAND_TIMEOUT 15000U
#define ESP_SERVER_PORT 80U

static char request_buffer[ESP_RX_BUFFER_SIZE];
static uint16_t request_length = 0U;
static uint8_t request_active = 0U;

/* Wait for an expected response token while collecting ESP8266 UART data. */
static HAL_StatusTypeDef wait_for_text(UART_HandleTypeDef *huart,
                                       const char *expected,
                                       uint32_t timeout,
                                       char *capture,
                                       size_t capture_size)
{
    uint32_t start = HAL_GetTick();
    size_t used = 0U;
    uint8_t ch;

    if (capture != NULL && capture_size > 0U)
    {
        capture[0] = '\0';
    }

    while ((HAL_GetTick() - start) < timeout)
    {
        if (HAL_UART_Receive(huart, &ch, 1U, 20U) == HAL_OK)
        {
            if (capture != NULL && capture_size > 1U && used < (capture_size - 1U))
            {
                capture[used++] = (char)ch;
                capture[used] = '\0';
            }

            if (capture != NULL && expected != NULL &&
                strstr(capture, expected) != NULL)
            {
                return HAL_OK;
            }
        }
    }

    return HAL_TIMEOUT;
}

static HAL_StatusTypeDef send_command(UART_HandleTypeDef *huart,
                                      const char *command,
                                      const char *expected,
                                      uint32_t timeout,
                                      char *capture,
                                      size_t capture_size)
{
    if (HAL_UART_Transmit(huart,
                          (uint8_t *)command,
                          (uint16_t)strlen(command),
                          1000U) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return wait_for_text(huart, expected, timeout, capture, capture_size);
}

static void extract_station_ip(const char *response, char *ip_out, size_t ip_out_size)
{
    const char *start;
    const char *end;
    size_t length;

    if (ip_out == NULL || ip_out_size == 0U)
    {
        return;
    }

    ip_out[0] = '\0';

    start = strstr(response, "+CIFSR:STAIP,\"");
    if (start == NULL)
    {
        return;
    }

    start += strlen("+CIFSR:STAIP,\"");
    end = strchr(start, '"');

    if (end == NULL)
    {
        return;
    }

    length = (size_t)(end - start);
    if (length >= ip_out_size)
    {
        length = ip_out_size - 1U;
    }

    memcpy(ip_out, start, length);
    ip_out[length] = '\0';
}

HAL_StatusTypeDef ESP8266_HTTP_Init(UART_HandleTypeDef *huart,
                                    const char *ssid,
                                    const char *password,
                                    char *ip_out,
                                    size_t ip_out_size)
{
    char command[160];
    char response[256];

    if (huart == NULL || ssid == NULL || password == NULL)
    {
        return HAL_ERROR;
    }

    /* Reset and disable command echo. */
    (void)send_command(huart, "AT+RST\r\n", "ready", 8000U, response, sizeof(response));
    HAL_Delay(1500U);

    if (send_command(huart, "ATE0\r\n", "OK", 2000U, response, sizeof(response)) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (send_command(huart, "AT+CWMODE=1\r\n", "OK", 3000U, response, sizeof(response)) != HAL_OK)
    {
        return HAL_ERROR;
    }

    /* Join the Wi-Fi access point. */
    (void)snprintf(command, sizeof(command),
                   "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);

    if (send_command(huart, command, "WIFI GOT IP", ESP_COMMAND_TIMEOUT,
                     response, sizeof(response)) != HAL_OK)
    {
        /* Some firmware versions return OK after WIFI GOT IP; accept either. */
        if (strstr(response, "OK") == NULL)
        {
            return HAL_ERROR;
        }
    }

    if (send_command(huart, "AT+CIPMUX=1\r\n", "OK", 3000U,
                     response, sizeof(response)) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (send_command(huart, "AT+CIPSERVER=1,80\r\n", "OK", 3000U,
                     response, sizeof(response)) != HAL_OK)
    {
        return HAL_ERROR;
    }

    /* Query the address assigned by the Wi-Fi router. */
    if (send_command(huart, "AT+CIFSR\r\n", "OK", 3000U,
                     response, sizeof(response)) == HAL_OK)
    {
        extract_station_ip(response, ip_out, ip_out_size);
    }

    request_length = 0U;
    request_active = 0U;
    memset(request_buffer, 0, sizeof(request_buffer));

    return HAL_OK;
}

static void format_two_decimals(float value, char *out, size_t out_size)
{
    long scaled = (long)(value * 100.0f);
    unsigned long magnitude;

    if (scaled < 0)
    {
        magnitude = (unsigned long)(-scaled);
        (void)snprintf(out, out_size, "-%lu.%02lu",
                       magnitude / 100UL, magnitude % 100UL);
    }
    else
    {
        magnitude = (unsigned long)scaled;
        (void)snprintf(out, out_size, "%lu.%02lu",
                       magnitude / 100UL, magnitude % 100UL);
    }
}

static void send_http_response(UART_HandleTypeDef *huart,
                               uint8_t connection_id,
                               const SensorReadings *readings)
{
    char json[180];
    char http_response[360];
    char command[40];
    char temp_text[24];
    char humidity_text[24];
    char pressure_text[24];
    int json_length;
    int response_length;

    if (readings == NULL || readings->valid == 0U)
    {
        (void)snprintf(json, sizeof(json),
                       "{\"status\":\"sensor_error\"}");
    }
    else
    {
        format_two_decimals(readings->temperature, temp_text, sizeof(temp_text));
        format_two_decimals(readings->humidity, humidity_text, sizeof(humidity_text));
        format_two_decimals(readings->pressure, pressure_text, sizeof(pressure_text));

        json_length = snprintf(json, sizeof(json),
                               "{\"status\":\"success\","
                               "\"temperature\":%s,"
                               "\"humidity\":%s,"
                               "\"pressure\":%s}",
                               temp_text, humidity_text, pressure_text);

        if (json_length < 0 || (size_t)json_length >= sizeof(json))
        {
            return;
        }
    }

    json_length = (int)strlen(json);

    response_length = snprintf(http_response, sizeof(http_response),
                               "HTTP/1.1 200 OK\r\n"
                               "Content-Type: application/json\r\n"
                               "Content-Length: %d\r\n"
                               "Connection: close\r\n"
                               "Access-Control-Allow-Origin: *\r\n"
                               "\r\n"
                               "%s",
                               json_length, json);

    if (response_length <= 0 || (size_t)response_length >= sizeof(http_response))
    {
        return;
    }

    (void)snprintf(command, sizeof(command),
                   "AT+CIPSEND=%u,%d\r\n",
                   (unsigned int)connection_id, response_length);

    if (HAL_UART_Transmit(huart, (uint8_t *)command,
                          (uint16_t)strlen(command), 1000U) == HAL_OK)
    {
        if (wait_for_text(huart, ">", 3000U, request_buffer,
                          sizeof(request_buffer)) == HAL_OK)
        {
            (void)HAL_UART_Transmit(huart, (uint8_t *)http_response,
                                    (uint16_t)response_length, 3000U);
            (void)wait_for_text(huart, "SEND OK", 5000U,
                                request_buffer, sizeof(request_buffer));
        }
    }

    (void)snprintf(command, sizeof(command),
                   "AT+CIPCLOSE=%u\r\n", (unsigned int)connection_id);
    (void)HAL_UART_Transmit(huart, (uint8_t *)command,
                            (uint16_t)strlen(command), 1000U);
}

/*
 * ESP-AT sends incoming TCP data as:
 * +IPD,<link_id>,<length>:<payload>
 * This handler waits for the HTTP header terminator before replying.
 */
void ESP8266_HTTP_Process(UART_HandleTypeDef *huart,
                          const SensorReadings *readings)
{
    uint8_t ch;
    char *ipd;
    char *colon;
    char *header_end;
    int connection_id;

    if (huart == NULL)
    {
        return;
    }

    if (HAL_UART_Receive(huart, &ch, 1U, 1U) != HAL_OK)
    {
        return;
    }

    if (request_length < (ESP_RX_BUFFER_SIZE - 1U))
    {
        request_buffer[request_length++] = (char)ch;
        request_buffer[request_length] = '\0';
    }
    else
    {
        request_length = 0U;
        request_active = 0U;
        memset(request_buffer, 0, sizeof(request_buffer));
        return;
    }

    ipd = strstr(request_buffer, "+IPD,");
    if (ipd != NULL)
    {
        request_active = 1U;
    }

    if (request_active == 0U)
    {
        /* Keep only a short suffix until the start of an incoming packet. */
        if (request_length > 5U)
        {
            memmove(request_buffer, &request_buffer[request_length - 5U], 5U);
            request_length = 5U;
            request_buffer[request_length] = '\0';
        }
        return;
    }

    header_end = strstr(request_buffer, "\r\n\r\n");
    if (header_end == NULL)
    {
        return;
    }

    ipd = strstr(request_buffer, "+IPD,");
    colon = (ipd != NULL) ? strchr(ipd, ':') : NULL;

    if (ipd != NULL && colon != NULL)
    {
        connection_id = atoi(ipd + 5);
        if (connection_id >= 0 && connection_id <= 4)
        {
            send_http_response(huart, (uint8_t)connection_id, readings);
        }
    }

    request_length = 0U;
    request_active = 0U;
    memset(request_buffer, 0, sizeof(request_buffer));
}
