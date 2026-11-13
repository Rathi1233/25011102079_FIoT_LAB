# Node-RED – CAT15 Heat Monitoring and Irrigation Advisory

The CAT15 dashboard displays city weather data and STM32 local BME280 readings, heat-index information, comparison analysis, combined heat risk and irrigation advisory outputs.

## MQTT input

Configure the MQTT input to subscribe to:

- Broker: `broker.emqx.io`
- Port: `1883`
- Topic: `farm/field01/telemetry`

The STM32 payload fields are `temperature_c`, `humidity_pct` and `pressure_hpa`.

## Weather API

The flow also uses an HTTP Request node to retrieve city weather data. Configure the API endpoint and any required key in your local Node-RED environment. Do not publish API secrets in the repository.

## Heat-index and irrigation logic

The project logic and threshold tables are documented in the root `README.md`, Sections 6–10. Heat Index classification and irrigation advisory are separate calculations.

## Included JSON file

`dashboard_ui_config_partial.json` is the JSON export provided with the project. It contains Dashboard UI configuration nodes (page, group, theme and UI text) only; it does not contain the complete MQTT, weather API, function-node or dashboard wiring flow. It is therefore not a complete importable flow.

To make this project fully portable, export the complete working flow from the Node-RED editor and place it in this folder.
