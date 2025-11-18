# SensorManager
SensorManager is a lightweight C++ framework for managing multiple sensors in Arduino projects using non-blocking, time-aware scheduling. It enables each sensor to define its own update interval and initialization logic, promoting modularity and clean separation of concerns.

### Architecture
- BaseSensorHandler: Abstract base class for individual sensor modules. Each sensor implements initialize() and update() methods.
- SensorManager: Central coordinator that calls update() only when a sensor's next scheduled time has arrived, based on millis().

  
### Features
- Non-blocking, cooperative multitasking for sensor polling
- Per-sensor update intervals for efficient resource use
- Simple integration with any Arduino-compatible sensor
- Predictable execution order (based on array position)

### Ideal For
- Projects with multiple sensors requiring different polling rates
- Systems where blocking delays (delay()) are unacceptable
- Modular sensor libraries and reusable components
