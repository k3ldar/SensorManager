/*
 * BasicExample.ino - Basic example of using SensorManager
 * 
 * This example demonstrates how to use the SensorManager library
 * to manage multiple sensors with different update intervals.
 */

#include <SensorManager.h>

// Example sensor class that reads from an analog pin
class AnalogSensor : public Sensor {
public:
    AnalogSensor(int pin, unsigned long updateInterval)
        : Sensor(updateInterval), _pin(pin), _value(0) {
        pinMode(_pin, INPUT);
    }
    
    void read() override {
        _value = analogRead(_pin);
        Serial.print("Analog sensor on pin ");
        Serial.print(_pin);
        Serial.print(": ");
        Serial.println(_value);
    }
    
    int getValue() const {
        return _value;
    }
    
private:
    int _pin;
    int _value;
};

// Create sensor manager
SensorManager manager;

// Create sensors
AnalogSensor sensor1(A0, 1000);  // Read every 1 second
AnalogSensor sensor2(A1, 2000);  // Read every 2 seconds

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for serial port to connect (needed for native USB boards)
    }
    
    Serial.println("SensorManager Basic Example");
    Serial.println("===========================");
    
    // Add sensors to manager
    manager.addSensor(&sensor1);
    manager.addSensor(&sensor2);
    
    Serial.print("Number of sensors: ");
    Serial.println(manager.getSensorCount());
    Serial.println();
}

void loop() {
    // Update all sensors (they will only read if their interval has elapsed)
    manager.update();
    
    // You can do other non-blocking work here
    delay(10);
}
