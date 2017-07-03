#include "SensorModule.h"
#include "Arduino.h"

SensorModule::SensorModule() {
}

void SensorModule::Tick() {
    Serial.println("Sensor Ticking");
}

int SensorModule::Send() {
    Serial.println("Sensor Sensing");
    return 0;
}

float SensorModule::GetData() {
    Serial.println("Getting Sensor Data");
}
