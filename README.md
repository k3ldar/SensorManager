# SensorManager

SensorManager is a lightweight C++ framework for managing multiple sensors in Arduino projects using non-blocking, time-aware scheduling.

## Features

- **Non-blocking sensor management**: Read from multiple sensors without blocking your main loop
- **Time-aware scheduling**: Each sensor can have its own update interval
- **Easy to use**: Simple API for adding, removing, and updating sensors
- **Flexible architecture**: Extend the base `Sensor` class to create custom sensors
- **Memory efficient**: Designed for resource-constrained Arduino boards

## Installation

### Arduino IDE
1. Download the latest release from the [releases page](https://github.com/k3ldar/SensorManager/releases)
2. In the Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library**
3. Select the downloaded ZIP file
4. The library will be installed and ready to use

### PlatformIO
Add the following to your `platformio.ini`:
```ini
lib_deps =
    k3ldar/SensorManager
```

## Usage

### Basic Example

```cpp
#include <SensorManager.h>

// Create a custom sensor by extending the Sensor class
class AnalogSensor : public Sensor {
public:
    AnalogSensor(int pin, unsigned long updateInterval)
        : Sensor(updateInterval), _pin(pin) {
        pinMode(_pin, INPUT);
    }
    
    void read() override {
        int value = analogRead(_pin);
        Serial.println(value);
    }
    
private:
    int _pin;
};

SensorManager manager;
AnalogSensor sensor1(A0, 1000);  // Read every 1 second

void setup() {
    Serial.begin(9600);
    manager.addSensor(&sensor1);
}

void loop() {
    manager.update();  // Updates all sensors when needed
    delay(10);
}
```

## API Reference

### Sensor Class

Base class for all sensors. Inherit from this class to create custom sensors.

#### Constructor
- `Sensor(unsigned long updateInterval)` - Create a sensor with specified update interval in milliseconds

#### Methods
- `bool needsUpdate()` - Check if sensor needs to be updated
- `virtual void read()` - Read sensor data (must be implemented by derived classes)
- `unsigned long getLastUpdateTime()` - Get the time of last update
- `void setUpdateInterval(unsigned long interval)` - Change the update interval

### SensorManager Class

Manages multiple sensors and their update schedules.

#### Methods
- `bool addSensor(Sensor* sensor)` - Add a sensor to the manager
- `bool removeSensor(Sensor* sensor)` - Remove a sensor from the manager
- `void update()` - Update all sensors that need updating
- `int getSensorCount()` - Get the number of managed sensors

## Examples

The library includes several examples:
- **BasicExample**: Simple example with analog sensors
- **MultiSensorExample**: Advanced example with multiple sensor types and dynamic intervals

## License

This library is licensed under the GPL-3.0 License. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.
