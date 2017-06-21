#include "MicModule.h"

MicModule::MicModule(int tickTime) : SensorModule(tickTime) {

}

void MicModule::Tick() {
    Serial.println("Microphone Tick");
}

void MicModule::Send() {
    
}
