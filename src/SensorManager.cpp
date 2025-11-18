/*
 * SensorManager.cpp - Library for managing multiple sensors in Arduino projects
 * Copyright (c) 2025 K3ldar
 * Licensed under GPL-3.0
 */

#include "SensorManager.h"

// Sensor class implementation
Sensor::Sensor(unsigned long updateInterval)
    : _updateInterval(updateInterval), _lastUpdate(0) {
}

Sensor::~Sensor() {
}

bool Sensor::needsUpdate() {
    unsigned long currentTime = millis();
    if (currentTime - _lastUpdate >= _updateInterval) {
        _lastUpdate = currentTime;
        return true;
    }
    return false;
}

unsigned long Sensor::getLastUpdateTime() const {
    return _lastUpdate;
}

void Sensor::setUpdateInterval(unsigned long interval) {
    _updateInterval = interval;
}

// SensorManager class implementation
SensorManager::SensorManager() : _sensorCount(0) {
    for (int i = 0; i < MAX_SENSORS; i++) {
        _sensors[i] = nullptr;
    }
}

SensorManager::~SensorManager() {
    // Note: We don't delete sensors as we don't own them
}

bool SensorManager::addSensor(Sensor* sensor) {
    if (_sensorCount >= MAX_SENSORS || sensor == nullptr) {
        return false;
    }
    
    _sensors[_sensorCount++] = sensor;
    return true;
}

bool SensorManager::removeSensor(Sensor* sensor) {
    if (sensor == nullptr) {
        return false;
    }
    
    for (int i = 0; i < _sensorCount; i++) {
        if (_sensors[i] == sensor) {
            // Shift remaining sensors
            for (int j = i; j < _sensorCount - 1; j++) {
                _sensors[j] = _sensors[j + 1];
            }
            _sensors[_sensorCount - 1] = nullptr;
            _sensorCount--;
            return true;
        }
    }
    return false;
}

void SensorManager::update() {
    for (int i = 0; i < _sensorCount; i++) {
        if (_sensors[i] != nullptr && _sensors[i]->needsUpdate()) {
            _sensors[i]->read();
        }
    }
}

int SensorManager::getSensorCount() const {
    return _sensorCount;
}
