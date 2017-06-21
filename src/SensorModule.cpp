#include "SensorModule.h"
#include "Arduino.h"

SensorModule::SensorModule(int tTime) {
    tickTime = tTime;
}

void SensorModule::Tick() {
    Serial.println("Sensor Ticking");
}

void SensorModule::Send() {
    Serial.println("Sensor Sensing");
}

float SensorModule::GetData() {
    Serial.println("Getting Sensor Data");
}
