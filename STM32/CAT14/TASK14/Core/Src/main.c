/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : CAT13 - BME280 sensor interfacing using I2C and MQTT.
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"
#include "ESPLib.h"
#include "bme280.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;

#define BME280_I2C_ADDR       (0x76U << 1) /* Change to (0x77U << 1) if SDO is HIGH */
#define MQTT_TOPIC            "stm32/bme280"
#define MQTT_PUBLISH_PERIOD   1000U

/* Replace these placeholders with your own Wi-Fi credentials before flashing. */
#define WIFI_SSID             "YOUR_WIFI_SSID"
#define WIFI_PASSWORD         "YOUR_WIFI_PASSWORD"

static struct bme280_dev bme280;
static struct bme280_settings bme280_settings;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);

static BME280_INTF_RET_TYPE BME280_I2C_Read(uint8_t reg_addr,
                                            uint8_t *reg_data,
                                            uint32_t len,
                                            void *intf_ptr);
static BME280_INTF_RET_TYPE BME280_I2C_Write(uint8_t reg_addr,
                                             const uint8_t *reg_data,
                                             uint32_t len,
                                             void *intf_ptr);
static void BME280_Delay_us(uint32_t period, void *intf_ptr);
static int8_t BME280_InitSensor(void);
static void Publish_BME280_Data(void);

/* USER CODE BEGIN 0 */

static BME280_INTF_RET_TYPE BME280_I2C_Read(uint8_t reg_addr,
                                            uint8_t *reg_data,
                                            uint32_t len,
                                            void *intf_ptr)
{
    I2C_HandleTypeDef *i2c = (I2C_HandleTypeDef *)intf_ptr;

    if (HAL_I2C_Mem_Read(i2c, BME280_I2C_ADDR, reg_addr,
                         I2C_MEMADD_SIZE_8BIT, reg_data,
                         (uint16_t)len, 100U) == HAL_OK)
    {
        return 0;
    }
    return -1;
}

static BME280_INTF_RET_TYPE BME280_I2C_Write(uint8_t reg_addr,
                                             const uint8_t *reg_data,
                                             uint32_t len,
                                             void *intf_ptr)
{
    I2C_HandleTypeDef *i2c = (I2C_HandleTypeDef *)intf_ptr;
    uint8_t tx_buffer[BME280_MAX_LEN + 1U];

    if ((len > BME280_MAX_LEN) || (len == 0U))
    {
        return -1;
    }

    tx_buffer[0] = reg_addr;
    memcpy(&tx_buffer[1], reg_data, len);

    if (HAL_I2C_Master_Transmit(i2c, BME280_I2C_ADDR,
                                tx_buffer, (uint16_t)(len + 1U),
                                100U) == HAL_OK)
    {
        return 0;
    }
    return -1;
}

static void BME280_Delay_us(uint32_t period, void *intf_ptr)
{
    (void)intf_ptr;
    /* HAL_Delay has millisecond resolution; round up for the Bosch API delay. */
    HAL_Delay((period + 999U) / 1000U);
}

static int8_t BME280_InitSensor(void)
{
    int8_t rslt;

    memset(&bme280, 0, sizeof(bme280));
    bme280.intf = BME280_I2C_INTF;
    bme280.intf_ptr = &hi2c1;
    bme280.read = BME280_I2C_Read;
    bme280.write = BME280_I2C_Write;
    bme280.delay_us = BME280_Delay_us;

    rslt = bme280_init(&bme280);
    if (rslt != BME280_OK)
    {
        return rslt;
    }

    bme280_settings.osr_t = BME280_OVERSAMPLING_2X;
    bme280_settings.osr_p = BME280_OVERSAMPLING_16X;
    bme280_settings.osr_h = BME280_OVERSAMPLING_1X;
    bme280_settings.filter = BME280_FILTER_COEFF_16;
    bme280_settings.standby_time = BME280_STANDBY_TIME_125_MS;

    rslt = bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS,
                                      &bme280_settings, &bme280);
    if (rslt != BME280_OK)
    {
        return rslt;
    }

    return bme280_set_sensor_mode(BME280_POWERMODE_NORMAL, &bme280);
}

/*
 * Bosch fixed-point output units for this API:
 * temperature = 0.01 deg C; pressure = Q24.8 Pa (64-bit path); humidity = 1/1024 %RH.
 * Format values as JSON without requiring printf floating-point support.
 */
static void Publish_BME280_Data(void)
{
    struct bme280_data sensor_data;
    char json_payload[80];
    uint32_t humidity_x100;
    uint32_t pressure_hpa_x100;
    int32_t temperature;
    uint32_t temperature_abs;
    int payload_len;

    if (bme280_get_sensor_data(BME280_ALL, &sensor_data, &bme280) != BME280_OK)
    {
        return;
    }

    temperature = sensor_data.temperature;
    temperature_abs = (temperature < 0) ? (uint32_t)(-temperature) : (uint32_t)temperature;
    humidity_x100 = (sensor_data.humidity * 100U + 512U) / 1024U;
    pressure_hpa_x100 = (sensor_data.pressure + 128U) / 256U; /* Q24.8 Pa -> hPa x 100 */

    if (temperature < 0)
    {
        payload_len = snprintf(json_payload, sizeof(json_payload),
            "{\"status\":\"success\",\"temperature\":-%lu.%02lu,"
            "\"humidity\":%lu.%02lu,\"pressure\":%lu.%02lu}",
            (unsigned long)(temperature_abs / 100U),
            (unsigned long)(temperature_abs % 100U),
            (unsigned long)(humidity_x100 / 100U),
            (unsigned long)(humidity_x100 % 100U),
            (unsigned long)(pressure_hpa_x100 / 100U),
            (unsigned long)(pressure_hpa_x100 % 100U));
    }
    else
    {
        payload_len = snprintf(json_payload, sizeof(json_payload),
            "{\"status\":\"success\",\"temperature\":%lu.%02lu,"
            "\"humidity\":%lu.%02lu,\"pressure\":%lu.%02lu}",
            (unsigned long)(temperature_abs / 100U),
            (unsigned long)(temperature_abs % 100U),
            (unsigned long)(humidity_x100 / 100U),
            (unsigned long)(humidity_x100 % 100U),
            (unsigned long)(pressure_hpa_x100 / 100U),
            (unsigned long)(pressure_hpa_x100 % 100U));
    }

    if ((payload_len > 0) && (payload_len < (int)sizeof(json_payload)))
    {
        MQTT_publishTopic(MQTT_TOPIC, json_payload, QoS0);
    }
}

/* USER CODE END 0 */

int main(void)
{
    uint32_t last_publish_time = 0U;
    MQTT_InitTypeDef_t mqttSetting;

    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART2_UART_Init();

    /* Initialize and configure the BME280 over I2C. */
    if (BME280_InitSensor() != BME280_OK)
    {
        Error_Handler();
    }

    /* ESP8266 AT-command setup on USART2, as specified in the CAT13 sheet. */
    if (ESP8266_Init(StationMode, huart2) != funcOk)
    {
        Error_Handler();
    }

    if (ESP8266_wifiConnect(WIFI_SSID, WIFI_PASSWORD) != funcOk)
    {
        Error_Handler();
    }

    /* Connect to the public EMQX MQTT broker (unencrypted MQTT, port 1883). */
    if (ESP8266_portConnect("TCP", "broker.emqx.io", "1883") != funcOk)
    {
        Error_Handler();
    }

    memset(&mqttSetting, 0, sizeof(mqttSetting));
    mqttSetting.keepAlive = 500U;
    mqttSetting.connectFlag = CleanSession;
    mqttSetting.clientID = "STM32_BME280_CAT13";
    MQTT_connectBroker(&mqttSetting);

    while (1)
    {
        if ((HAL_GetTick() - last_publish_time) >= MQTT_PUBLISH_PERIOD)
        {
            last_publish_time = HAL_GetTick();
            Publish_BME280_Data();
        }
    }
}

static void MX_I2C1_Init(void)
{
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000U;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0U;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0U;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
        Error_Handler();
    }
}

static void MX_USART2_UART_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200U;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }
}

static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}

/* Original system clock configuration retained from the supplied project. */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
