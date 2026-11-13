# Fundamentals and Practice of IoT — Laboratory Portfolio

<p align="center">
  <b>Registration Number: 25011102079</b><br>
  <b>Course: Fundamentals and Practice of IoT</b><br>
  <a href="https://github.com/Rathi1233/25011102079_FIoT_LAB">GitHub Repository</a>
</p>

---

## About This Repository

This repository contains the laboratory experiments and integrated IoT project completed as part of the **Fundamentals and Practice of IoT** course.

The experiments demonstrate the progression from fundamental 8051 microcontroller programming to STM32-based embedded systems, peripheral interfacing, wireless communication, sensor integration and IoT application development.

The repository is organized into two major laboratory platforms and one integrated project:

- **8051:** CAT2–CAT7
- **STM32:** CAT8–CAT14
- **Integrated IoT Project:** CAT15, maintained under the STM32 directory

The experiments cover embedded C programming, GPIO, timers, interrupts, UART, I2C, Wi-Fi communication, HTTP, MQTT, environmental sensing and Node-RED dashboard development.

---

## Repository Structure

```text
25011102079_FIoT_LAB/
│
├── 8051/
│   ├── CAT2/
│   ├── CAT3/
│   ├── CAT4/
│   ├── CAT5/
│   ├── CAT6/
│   └── CAT7/
│
├── STM32/
│   ├── CAT8/
│   ├── CAT9/
│   ├── CAT10/
│   ├── CAT11/
│   ├── CAT12/
│   ├── CAT13/
│   │   └── TASK13/
│   ├── CAT14/
│   │   └── TASK14/
│   └── CAT15/
│
├── .gitignore
└── README.md
```

---

# PART 1 — 8051 MICROCONTROLLER LABORATORY

**Platform:** 8051 Microcontroller  
**Controller:** AT89S52  
**Development Environment:** Keil µVision  
**Compiler:** Keil C51

This section covers fundamental microcontroller programming, digital interfacing, timers, interrupts, serial communication and display control.

## CAT2 — LED Interfacing

**TASK2B — Bare-Metal LED Blink and Custom Delay**

- LED interfacing with the 8051 microcontroller.
- Digital output control.
- Software delay implementation.
- Basic embedded C programming.

[Explore CAT2](8051/CAT2/)

## CAT3 — Pushbutton and LED Interfacing

**TASK3A — Four-LED Four-Mode Pushbutton Controller**

- Pushbutton input interfacing.
- Four-LED control.
- Multiple operating modes.
- Digital input/output programming.

[Explore CAT3](8051/CAT3/)

## CAT4 — Keypad and Display Interfacing

**TASK4A — Matrix Keypad, Seven-Segment and LED HMI**

- Matrix keypad interfacing.
- Seven-segment display control.
- LED output control.
- Human-machine interface implementation.

[Explore CAT4](8051/CAT4/)

## CAT5 — Timers and Signal Generation

| Task | Experiment |
|---|---|
| TASK5A | Timer 0 Interrupt and 1-Second LED Timebase |
| TASK5B / TASK5B.1 | Software PWM LED Fading |
| TASK5B.2 | Variable-Frequency Square-Wave Generation |
| TASK5B.3 | Different Signal Types — Pulse Train, Burst and Variable Duty Cycle |
| TASK5C | Stepper Motor Speed and Direction (Optional) |

**Concepts covered:**

- Timer configuration.
- Timer interrupts.
- Periodic timebase generation.
- Software PWM.
- Frequency and duty-cycle control.
- Stepper motor speed and direction control.

[Explore CAT5](8051/CAT5/)

## CAT6 — UART Serial Communication

| Task | Experiment |
|---|---|
| TASK6A | UART Initialization and Character Transmission |
| TASK6B | UART Echo and Interrupt-Driven Reception |

**Concepts covered:**

- UART initialization.
- Serial character transmission.
- UART reception.
- Interrupt-driven communication.
- Serial data handling.

[Explore CAT6](8051/CAT6/)

## CAT7 — LCD and Keypad Interfacing

| Task | Experiment |
|---|---|
| TASK7A | LCD Initialization and Character/String Display |
| TASK7B | LCD Cursor Positioning and Dynamic Update |
| TASK7C | 4×4 Keypad-Controlled Character Movement |

**Concepts covered:**

- LCD initialization.
- Character and string display.
- Cursor positioning.
- Dynamic LCD updates.
- Keypad input processing.
- Display control.

[Explore CAT7](8051/CAT7/)

### 8051 Learning Outcomes

The 8051 experiments provide practical experience in:

- Embedded C programming.
- Digital input and output.
- Pushbutton and keypad interfacing.
- LED and seven-segment display control.
- Timers and interrupts.
- PWM and waveform generation.
- Stepper motor control.
- UART communication.
- LCD interfacing.

---

# PART 2 — STM32 MICROCONTROLLER LABORATORY

**Development Platforms:**
- STM32F103C8T6 Blue Pill
- STM32 NUCLEO-F410RB

**Development Tools:** STM32CubeMX and Keil MDK-ARM  
**Programming Framework:** STM32 HAL

This section focuses on STM32 peripheral configuration, GPIO, UART communication, ESP8266 interfacing, HTTP communication and environmental sensor integration.

## CAT8 — GPIO Interfacing: LED and Pushbutton

**Board:** STM32F103C8T6 Blue Pill

| Task | Implementation |
|---|---|
| TASK8A | LED follows the current pushbutton state |
| TASK8B | Debounced pushbutton press toggles the LED once |
| TASK8C | Short-press and long-press detection with non-blocking LED blinking |

**Concepts covered:**

- GPIO input and output configuration.
- Internal pull-up resistor.
- Pushbutton state detection.
- Button debouncing.
- Short-press and long-press detection.
- Non-blocking timing.

[Explore CAT8](STM32/CAT8/)

## CAT9 — UART Serial Communication

**Board:** STM32F103C8T6 Blue Pill  
**Communication:** USART2

| Task | Implementation |
|---|---|
| TASK9A | UART character transmission, reception and echo |
| TASK9B | Serial command-based LED control |

TASK9B supports commands such as:

```text
LED ON
LED OFF
LED TOGGLE
HELP
```

**Concepts covered:**

- USART2 configuration.
- UART transmission and reception.
- Serial terminal communication.
- Command parsing.
- GPIO control through UART commands.

[Explore CAT9](STM32/CAT9/)

## CAT10 — Wi-Fi Modem Interface Using ESP8266

**Hardware:** STM32 and Wemos D1 Mini (ESP8266)

| Task | Implementation |
|---|---|
| TASK10A | Establish UART communication between STM32 and Wemos ESP8266 |
| TASK10B | Explore and test ESP8266 AT commands |
| TASK10C | Configure ESP8266 and connect to a wireless network |

**Concepts covered:**

- UART communication between microcontrollers and Wi-Fi modules.
- ESP8266 AT command interface.
- Wi-Fi configuration.
- Wireless network connection.
- Module response handling.

[Explore CAT10](STM32/CAT10/)

## CAT11 — HTTP Server Using STM32 and Wemos ESP8266

**Hardware:** STM32F410RB and Wemos ESP8266

### TASK11A — Configure ESP8266 as TCP Server

- Test ESP8266 AT communication.
- Configure multiple connections using `AT+CIPMUX=1`.
- Start a TCP server on port 80 using `AT+CIPSERVER=1,80`.
- Receive incoming HTTP requests through ESP8266 `+IPD` notifications.

### TASK11B — HTTP Response and Node-RED Integration

- Parse received HTTP requests.
- Construct HTTP responses with status line, headers and HTML body.
- Use the two-step `AT+CIPSEND` procedure.
- Access the HTTP server through a web browser.
- Configure Node-RED as another HTTP client.
- Display received HTTP responses using a Debug node.

**Concepts covered:**

- TCP server configuration.
- HTTP request reception.
- HTTP response construction.
- UART-based communication.
- ESP8266 networking.
- Node-RED HTTP client integration.

[Explore CAT11](STM32/CAT11/)

## CAT12 — GPIO and Onboard LED/Pushbutton Interfacing

**Board:** STM32 NUCLEO-F410RB

| Task | Implementation |
|---|---|
| TASK12A | Onboard LED blinking |
| TASK12B | Pushbutton-controlled LED toggling with debouncing |
| TASK12C | Short-press and long-press detection with LED state control and blinking |

**Concepts covered:**

- GPIO configuration.
- Onboard LED control.
- Pushbutton input.
- Edge detection.
- Debouncing.
- Non-blocking timing and event handling.

[Explore CAT12](STM32/CAT12/)

## CAT13 — BME280 Sensor Interfacing and HTTP Response Preparation

**Board:** STM32 NUCLEO-F410RB  
**Sensor:** Bosch BME280  
**Communication:** I2C1

This experiment focuses on environmental sensor interfacing using the BME280 sensor.

### Implementation

- BME280 sensor communication through I2C1.
- Bosch BME280 Sensor API initialization.
- Calibration-data loading.
- Temperature, pressure and humidity oversampling configuration.
- Normal measurement mode.
- Periodic compensated sensor data acquisition.
- JSON payload construction.
- HTTP/1.1 response construction.
- `Content-Length` calculation using `strlen()`.
- UART2 output for JSON data and HTTP response preview.

### Hardware Connections

| BME280 | NUCLEO-F410RB |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SCL | PB8 |
| SDA | PB9 |
| SDO | GND for address 0x76 |
| CSB | 3V3 |

**Concepts covered:**

- I2C communication.
- Sensor initialization and calibration.
- Environmental data acquisition.
- Temperature, humidity and pressure measurement.
- JSON formatting.
- HTTP response construction.

**Implementation scope:** The documented implementation prepares and prints JSON and HTTP response data through UART2. This should not be confused with a completed ESP8266 Wi-Fi or Node-RED HTTP integration unless those components are separately implemented in the project.

[Explore CAT13](STM32/CAT13/TASK13/)

## CAT14 — BME280 Sensor Interfacing Using MQTT

**Board:** STM32 NUCLEO-F410RB  
**Sensor:** Bosch BME280

This experiment focuses on environmental sensor monitoring and MQTT-based IoT communication.

### Implementation

- BME280 environmental data acquisition.
- Temperature, humidity and pressure monitoring.
- Sensor data processing.
- MQTT communication workflow.
- Publishing environmental telemetry through the configured MQTT setup.
- Integration with IoT monitoring tools.

**Concepts covered:**

- Environmental sensor interfacing.
- Sensor data acquisition.
- MQTT messaging.
- IoT telemetry.
- Wireless data communication.

[Explore CAT14](STM32/CAT14/TASK14/)

---

# PART 3 — CAT15: INTEGRATED IoT PROJECT

# Smart Agriculture — Heat Monitoring and Irrigation Advisory System

**Project Category:** Integrated IoT Project  
**Controller:** STM32 NUCLEO-F410RB  
**Sensor:** BME280  
**Wi-Fi Module:** Wemos D1 Mini (ESP8266)  
**Communication:** I2C, UART, Wi-Fi and MQTT  
**IoT Platform:** Node-RED  
**Dashboard:** FlowFuse Dashboard

## 1. Project Overview

CAT15 is an integrated IoT project developed to monitor environmental conditions and provide heat-risk and irrigation advisories.

The system combines STM32-based environmental sensing, ESP8266 wireless connectivity, MQTT messaging, external weather information and Node-RED dashboard visualization.

The BME280 sensor measures local temperature, relative humidity and atmospheric pressure. These measurements are processed and compared with city weather data obtained through a weather API.

The system provides two separate advisory mechanisms:

1. **Heat Monitoring:** Calculates Heat Index using temperature and relative humidity to estimate perceived heat conditions.
2. **Irrigation Advisory:** Uses project-defined temperature and humidity thresholds to identify possible atmospheric drying conditions.

The dashboard presents local sensor readings, city weather readings, heat-risk classification, irrigation alerts and comparison analysis.

## 2. System Architecture

```text
          BME280 SENSOR
                |
                | I2C
                |
                v
       STM32 NUCLEO-F410RB
                |
                | UART
                |
                v
         WEMOS ESP8266
                |
                | Wi-Fi / MQTT
                |
                v
           MQTT BROKER
                |
                v
             NODE-RED
                |
        +-------+--------+
        |                |
        v                v
  Sensor Data        Weather API
  Processing         HTTP Request
        |                |
        v                v
  Local Sensor       City Weather
  Readings           Readings
        |                |
        +-------+--------+
                |
                v
       COMPARISON ANALYSIS
                |
        +-------+--------+
        |                |
        v                v
     HEAT INDEX       IRRIGATION
     ANALYSIS          ADVISORY
        |                |
        +-------+--------+
                |
                v
        NODE-RED DASHBOARD
```

## 3. Hardware Components

| Component | Purpose |
|---|---|
| STM32 NUCLEO-F410RB | Main microcontroller |
| BME280 | Temperature, humidity and pressure sensing |
| Wemos D1 Mini (ESP8266) | Wireless communication |
| MQTT Broker | Telemetry message exchange |
| Node-RED | Data processing and integration |
| Weather API | External city weather information |
| FlowFuse Dashboard | Data visualization and alerts |

## 4. Environmental Parameters

The BME280 provides three environmental measurements:

| Parameter | Unit | Purpose |
|---|---|---|
| Temperature | °C | Environmental temperature monitoring |
| Relative Humidity | % | Moisture content in air |
| Atmospheric Pressure | hPa | Pressure monitoring |

These measurements are used for local environmental monitoring and comparison with external weather information.

## 5. Heat Index Calculation and Risk Classification

Heat Index combines air temperature and relative humidity to estimate how hot conditions feel.

The project uses the following National Weather Service heat-index categories.

| Heat Index (°C) | Heat Index (°F) | Classification |
|---|---|---|
| Below 26.7°C | Below 80°F | Normal |
| 26.7–32.2°C | 80–90°F | Caution |
| 32.2–39.4°C | 90–103°F | Extreme Caution |
| 39.4–51.7°C | 103–125°F | Danger |
| 51.7°C and above | 125°F and above | Extreme Danger |

### Heat Index Classification Logic

The project uses Fahrenheit thresholds for classification:

```javascript
if (hiF < 80) {
    combinedRisk = "Normal";
} else if (hiF < 90) {
    combinedRisk = "Caution";
} else if (hiF < 103) {
    combinedRisk = "Extreme Caution";
} else if (hiF < 125) {
    combinedRisk = "Danger";
} else {
    combinedRisk = "Extreme Danger";
}
```

### Interpretation

| Classification | Meaning |
|---|---|
| Normal | No elevated heat-index category |
| Caution | Fatigue may occur with prolonged exposure |
| Extreme Caution | Heat-related illness becomes more possible |
| Danger | Serious heat-related illness is possible |
| Extreme Danger | Very high heat-related risk |

**Important:** Heat Index is primarily intended for human heat-exposure assessment under shaded, light-wind conditions. It is not a direct crop-stress classification or irrigation requirement measurement.

## 6. Irrigation Advisory Logic

The irrigation advisory uses separate project-defined temperature and humidity thresholds.

These thresholds are experimental rules developed for the project. They are not official rice irrigation standards.

### Irrigation Threshold Table

| Condition | Temperature | Humidity | Alert |
|---|---|---|---|
| High | ≥35°C | ≤50% | HIGH |
| Moderate | ≥33°C | ≤60% | MODERATE |
| Monitor | ≥35°C OR ≤40% | Either condition | MONITOR |
| Normal | Other combinations | Other combinations | NORMAL |

### Irrigation Classification Logic

The order of evaluation is important. The HIGH condition is checked first, followed by MODERATE, MONITOR and NORMAL.

```javascript
if (temperature >= 35 && humidity <= 50) {
    alertLevel = "HIGH";
} else if (temperature >= 33 && humidity <= 60) {
    alertLevel = "MODERATE";
} else if (temperature >= 35 || humidity <= 40) {
    alertLevel = "MONITOR";
} else {
    alertLevel = "NORMAL";
}
```

### Advisory Interpretation

| Alert | Meaning | Suggested Action |
|---|---|---|
| HIGH | Hot and dry atmospheric conditions | Check field water level and soil condition promptly |
| MODERATE | Conditions may increase atmospheric drying | Review the irrigation schedule |
| MONITOR | One environmental condition needs attention | Check field conditions |
| NORMAL | No elevated atmospheric drying signal from these thresholds | Continue routine monitoring |

The irrigation advisory is an environmental warning indicator. Actual irrigation decisions require additional information such as soil moisture, crop growth stage, rainfall and field water level.

## 7. Atmospheric Pressure Monitoring

The BME280 also measures atmospheric pressure.

Pressure is displayed as an additional environmental measurement and can be compared with weather API pressure data.

Important distinctions:

- Pressure is not part of the NOAA Heat Index formula.
- Pressure alone cannot determine whether a crop needs irrigation.
- Pressure comparison is used as an additional environmental monitoring feature.

## 8. Weather API Integration

The project uses external city weather information to compare local sensor measurements with weather API readings.

The weather API workflow provides:

- City temperature.
- City relative humidity.
- Additional available weather information.

Node-RED processes the API response and makes the readings available for comparison with STM32 sensor data.

## 9. Comparison Analysis

The comparison workflow evaluates differences between local BME280 measurements and city weather data.

The comparison includes:

| Parameter | Comparison |
|---|---|
| Temperature | Local sensor temperature versus weather API temperature |
| Humidity | Local sensor humidity versus weather API humidity |
| Pressure | Local sensor pressure versus available weather pressure |
| Heat Index | Local and weather-based Heat Index values |

The dashboard displays the calculated differences to help identify variations between local sensor readings and external weather information.

Data availability is also considered so that unavailable sensor or weather readings are not incorrectly treated as valid measurements.

## 10. Node-RED Processing Workflow

The Node-RED flow performs the following operations:

1. Receive STM32 sensor data through the configured MQTT communication workflow.
2. Parse incoming sensor messages.
3. Standardize and store sensor readings.
4. Retrieve city weather data through an HTTP request.
5. Process weather API response values.
6. Calculate Heat Index.
7. Compare local sensor readings with weather API readings.
8. Determine combined heat-risk classification.
9. Calculate irrigation alert level.
10. Generate advisory messages.
11. Send processed values to dashboard widgets.

## 11. Dashboard Features

The FlowFuse Dashboard provides a visual monitoring interface titled:

**Heat Monitoring & Irrigation Advisory**

### City Weather Data

Displays:

- Weather temperature.
- Weather humidity.
- Weather pressure where available.
- Weather-based Heat Index.

### STM32 — Current Local Data

Displays:

- Local temperature.
- Local humidity.
- Sensor pressure.
- Local Heat Index.

### Heat Risk & Safety

Displays:

- Combined heat-risk classification.
- Heat Index advisory.
- Safety recommendations.

### Comparison Analysis

Displays:

- Temperature difference.
- Humidity difference.
- Pressure difference.
- Heat Index difference.

### Irrigation Advisory

Displays:

- Irrigation alert level.
- Irrigation advisory message.
- Temperature and humidity-based conditions.
- Plant-related recommendations based on environmental conditions.

## 12. Example Evaluation

Consider the following example sensor readings:

| Parameter | Value |
|---|---:|
| Temperature | 35°C |
| Humidity | 68% |
| Pressure | 1005 hPa |
| Heat Index | 49°C |

The resulting classifications are:

| Output | Result |
|---|---|
| Heat Index Risk | Danger |
| Irrigation Alert | MONITOR |
| Reason | High temperature, but humidity is not low |

This demonstrates that a high Heat Index does not automatically result in a HIGH irrigation alert.

**Heat-risk classification and irrigation classification are independent decision mechanisms.**

## 13. Technologies Used

| Technology | Application |
|---|---|
| STM32 NUCLEO-F410RB | Embedded processing |
| BME280 | Environmental sensing |
| ESP8266 | Wi-Fi connectivity |
| UART | STM32–ESP8266 communication |
| I2C | BME280 communication |
| MQTT | Sensor telemetry |
| HTTP | Weather API communication |
| Node-RED | Data processing and integration |
| FlowFuse Dashboard | Monitoring and visualization |
| JavaScript | Processing and advisory logic |

## 14. Project Scope and Limitations

- Heat Index classification is intended for human heat-exposure assessment, not direct crop-stress measurement.
- Irrigation thresholds are project-defined and should not be treated as official agricultural recommendations.
- Atmospheric pressure is monitored but is not independently used to decide irrigation requirements.
- Actual field irrigation decisions require soil moisture, rainfall, crop growth stage and field water-level information.
- Sensor and weather API comparisons depend on valid and available input data.

[Explore CAT15 — Integrated IoT Project](STM32/CAT15/)

---

# Development Tools and Technologies

| Tool / Technology | Purpose |
|---|---|
| Keil µVision / C51 | 8051 embedded C development |
| Keil MDK-ARM | STM32 embedded development |
| STM32CubeMX | Peripheral and clock configuration |
| STM32 HAL | STM32 peripheral programming |
| UART / USART | Serial communication |
| I2C | Sensor communication |
| ESP8266 AT Commands | Wi-Fi module configuration |
| HTTP | Client-server communication |
| MQTT | IoT telemetry messaging |
| Node-RED | IoT data processing |
| FlowFuse Dashboard | Dashboard visualization |
| Weather API | External environmental data |

---

# Quick Repository Navigation

| Section | Description | Repository Link |
|---|---|---|
| CAT2 | Bare-Metal LED Blink | [Open](8051/CAT2/) |
| CAT3 | Four-LED Pushbutton Controller | [Open](8051/CAT3/) |
| CAT4 | Keypad and Display HMI | [Open](8051/CAT4/) |
| CAT5 | Timers, PWM and Signal Generation | [Open](8051/CAT5/) |
| CAT6 | UART Communication | [Open](8051/CAT6/) |
| CAT7 | LCD and Keypad Interfacing | [Open](8051/CAT7/) |
| CAT8 | STM32 GPIO and Pushbutton | [Open](STM32/CAT8/) |
| CAT9 | STM32 UART Communication | [Open](STM32/CAT9/) |
| CAT10 | ESP8266 Wi-Fi Modem Interface | [Open](STM32/CAT10/) |
| CAT11 | HTTP Server Using STM32 and ESP8266 | [Open](STM32/CAT11/) |
| CAT12 | STM32 LED and Pushbutton Interfacing | [Open](STM32/CAT12/) |
| CAT13 | BME280 Sensor and HTTP Response Preparation | [Open](STM32/CAT13/TASK13/) |
| CAT14 | BME280 Sensor and MQTT | [Open](STM32/CAT14/TASK14/) |
| CAT15 | Smart Agriculture — Heat Monitoring and Irrigation Advisory | [Open](STM32/CAT15/) |

---

## Project Documentation and Verification

- Each experiment is organized in its respective CAT or TASK folder.
- Source files and project configuration files are retained with their corresponding experiments.
- Circuit diagrams are included wherever available.
- STM32 projects contain the relevant Core, Drivers and MDK-ARM project files.
- Generated compiler output and build artifacts are excluded through `.gitignore` where applicable.
- The documentation describes the supplied project implementations and does not claim fresh compilation or hardware verification unless explicitly stated.

---

## Author

**Registration Number:** 25011102079  
**Course:** Fundamentals and Practice of IoT  
**GitHub Profile:** [Rathi1233](https://github.com/Rathi1233)  
**Repository:** [25011102079_FIoT_LAB](https://github.com/Rathi1233/25011102079_FIoT_LAB)

---

<p align="center">
  <b>From Microcontroller Fundamentals to Integrated IoT Systems</b><br>
  8051 • STM32 • Embedded C • Sensors • Wi-Fi • HTTP • MQTT • Node-RED
</p>
