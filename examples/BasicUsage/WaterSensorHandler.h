#pragma once


#include "SensorManager.h"


constexpr uint8_t WaterSensorPin = A0;
constexpr uint8_t WaterSensorActivePin = D8;
constexpr unsigned long WaterSensorCheckIntervalMs = 5000;
constexpr unsigned long WaterSensorStabilizeMs = 10;

/**
 * @brief Sensor handler for water level monitoring with averaging.
 *
 * Reads analog water sensor values, maintains a rolling average using a queue,
 * and reports readings to both link and computer serial connections.
 */
class WaterSensorHandler : public BaseSensorHandler
{
private:
	const uint8_t _sensorPin;
	const uint8_t _activePin;
	bool _waitingForStabilization;

protected:
	void initialize() override
	{
	};

	unsigned long update() override
	{
		if (!_waitingForStabilization)
		{
			digitalWrite(WaterSensorActivePin, HIGH);
			_waitingForStabilization = true;
			return WaterSensorStabilizeMs;
		}

		_waitingForStabilization = false;
		int sensorValue = analogRead(_sensorPin);

		digitalWrite(WaterSensorActivePin, LOW);

        Serial.print("Water sensor value: ");
        Serial.println(sensorValue);

		return WaterSensorCheckIntervalMs;
	};
public:
	WaterSensorHandler(uint8_t sensorPin, uint8_t activePin)
		: _sensorPin(sensorPin), _activePin(activePin),	_waitingForStabilization(false)
	{
		pinMode(sensorPin, INPUT);
		digitalWrite(_activePin, LOW);
	};
};