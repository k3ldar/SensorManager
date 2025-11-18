#pragma once


#include "SensorManager.h"
#include <dht11.h>


constexpr uint8_t Dht11SensorPin = D9;

constexpr unsigned long TempHumidityCheckMs = 2500;


/**
 * @brief Sensor handler for DHT11 monitoring.
 *
 * Reads temperature and humidity sensor values, 
 * and reports readings to both link and computer serial connections.
 */
class Dht11SensorHandler : public BaseSensorHandler
{
private:
	dht11 _dht11Sensor;
	const uint8_t _sensorPin;

protected:
	void initialize() override
	{
		pinMode(_sensorPin, INPUT);
	};

	unsigned long update() override
	{
		int result = _dht11Sensor.read(_sensorPin);

		if (result != DHTLIB_OK)
		{
            Serial.print("DHT11 Error: ");
            Serial.println(result);

			return TempHumidityCheckMs;
		}

		float humidity = _dht11Sensor.humidity;
		float tempCelsius = _dht11Sensor.temperature;

		Serial.print("Humidity: ");
        Serial.println(humidity);

        Serial.print("Temperature: ");
        Serial.println(tempCelsius);

		return TempHumidityCheckMs;
	};
public:
	Dht11SensorHandler(uint8_t sensorPin)
		: _dht11Sensor(), _sensorPin(sensorPin)
	{
	};
};