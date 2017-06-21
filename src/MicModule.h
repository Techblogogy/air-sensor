
#ifndef MICROPHONE_MODULE
#define MICROPHONE_MODULE

#include "Arduino.h"
#include "SensorModule.h"

class MicModule : public SensorModule {

public:

    MicModule(int tickTime);

    void Tick();
    void Send();

};

#endif
