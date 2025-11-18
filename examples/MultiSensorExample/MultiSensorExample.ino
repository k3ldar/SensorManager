/*
 * MultiSensorExample.ino - Advanced example with multiple sensor types
 * 
 * This example demonstrates how to use the SensorManager library
 * with different types of sensors and dynamic interval changes.
 */

#include <SensorManager.h>

// Temperature sensor simulator (using analog input)
class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(int pin, unsigned long updateInterval)
        : Sensor(updateInterval), _pin(pin), _temperature(0.0) {
        pinMode(_pin, INPUT);
    }
    
    void read() override {
        int rawValue = analogRead(_pin);
        // Simulate temperature conversion (example formula)
        _temperature = (rawValue * 5.0 / 1023.0) * 100.0;
        
        Serial.print("Temperature: ");
        Serial.print(_temperature);
        Serial.println(" °C");
    }
    
    float getTemperature() const {
        return _temperature;
    }
    
private:
    int _pin;
    float _temperature;
};

// Light sensor simulator (using analog input)
class LightSensor : public Sensor {
public:
    LightSensor(int pin, unsigned long updateInterval)
        : Sensor(updateInterval), _pin(pin), _lightLevel(0) {
        pinMode(_pin, INPUT);
    }
    
    void read() override {
        _lightLevel = analogRead(_pin);
        Serial.print("Light level: ");
        Serial.println(_lightLevel);
    }
    
    int getLightLevel() const {
        return _lightLevel;
    }
    
private:
    int _pin;
    int _lightLevel;
};

// Digital sensor simulator (using digital input)
class MotionSensor : public Sensor {
public:
    MotionSensor(int pin, unsigned long updateInterval)
        : Sensor(updateInterval), _pin(pin), _motionDetected(false) {
        pinMode(_pin, INPUT);
    }
    
    void read() override {
        _motionDetected = digitalRead(_pin) == HIGH;
        Serial.print("Motion detected: ");
        Serial.println(_motionDetected ? "YES" : "NO");
    }
    
    bool isMotionDetected() const {
        return _motionDetected;
    }
    
private:
    int _pin;
    bool _motionDetected;
};

// Create sensor manager
SensorManager manager;

// Create sensors with different update intervals
TemperatureSensor tempSensor(A0, 5000);   // Read every 5 seconds
LightSensor lightSensor(A1, 3000);        // Read every 3 seconds
MotionSensor motionSensor(2, 500);        // Read every 0.5 seconds

unsigned long lastStatsTime = 0;
const unsigned long STATS_INTERVAL = 10000; // Print stats every 10 seconds

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for serial port to connect
    }
    
    Serial.println("SensorManager Multi-Sensor Example");
    Serial.println("===================================");
    Serial.println();
    
    // Add sensors to manager
    manager.addSensor(&tempSensor);
    manager.addSensor(&lightSensor);
    manager.addSensor(&motionSensor);
    
    Serial.print("Active sensors: ");
    Serial.println(manager.getSensorCount());
    Serial.println();
    Serial.println("Starting sensor readings...");
    Serial.println();
}

void loop() {
    // Update all sensors (they will only read if their interval has elapsed)
    manager.update();
    
    // Print statistics periodically
    unsigned long currentTime = millis();
    if (currentTime - lastStatsTime >= STATS_INTERVAL) {
        lastStatsTime = currentTime;
        printStatistics();
    }
    
    // Small delay for stability
    delay(10);
}

void printStatistics() {
    Serial.println();
    Serial.println("=== Statistics ===");
    Serial.print("Temperature: ");
    Serial.print(tempSensor.getTemperature());
    Serial.println(" °C");
    Serial.print("Light level: ");
    Serial.println(lightSensor.getLightLevel());
    Serial.print("Motion: ");
    Serial.println(motionSensor.isMotionDetected() ? "Detected" : "None");
    Serial.print("Active sensors: ");
    Serial.println(manager.getSensorCount());
    Serial.println("==================");
    Serial.println();
}
