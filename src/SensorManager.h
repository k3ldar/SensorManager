/*
 * SensorManager.h - Library for managing multiple sensors in Arduino projects
 * Copyright (c) 2025 K3ldar
 * Licensed under GPL-3.0
 * 
 * SensorManager is a lightweight C++ framework for managing multiple sensors
 * in Arduino projects using non-blocking, time-aware scheduling
 */

#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>

class Sensor {
public:
    Sensor(unsigned long updateInterval);
    virtual ~Sensor();
    
    // Check if sensor needs update based on time
    bool needsUpdate();
    
    // Read sensor data (to be implemented by derived classes)
    virtual void read() = 0;
    
    // Get last update time
    unsigned long getLastUpdateTime() const;
    
    // Set update interval
    void setUpdateInterval(unsigned long interval);
    
protected:
    unsigned long _updateInterval;  // Interval between readings in milliseconds
    unsigned long _lastUpdate;      // Last update time in milliseconds
};

class SensorManager {
public:
    SensorManager();
    ~SensorManager();
    
    // Add a sensor to the manager
    bool addSensor(Sensor* sensor);
    
    // Remove a sensor from the manager
    bool removeSensor(Sensor* sensor);
    
    // Update all sensors that need updating
    void update();
    
    // Get number of managed sensors
    int getSensorCount() const;
    
private:
    static const int MAX_SENSORS = 10;
    Sensor* _sensors[MAX_SENSORS];
    int _sensorCount;
};

#endif // SENSOR_MANAGER_H
