// Basic example using SensorManager with two sensors.
// Adjust serial port as needed (e.g., Serial1/Serial2) and baud rate.

#include <Arduino.h>
#include <SensorManager.h>
#include "WaterSensorHandler.h"
#include "DHT11SensorHandler.h"



WaterSensorHandler waterSensorHandler(WaterSensorPin, WaterSensorActivePin);
Dht11SensorHandler dht11SensorHandler(Dht11SensorPin);

BaseSensorHandler* sensorHandlers[] = { &waterSensorHandler, &dht11SensorHandler };
SensorManager sensorManager(sensorHandlers, sizeof(sensorHandlers) / sizeof(sensorHandlers[0]));


void setup() {
  Serial.begin(9600);
  delay(50);

  sensorManager.setup();
}

void loop() {
  sensorManager.update(millis());
}
