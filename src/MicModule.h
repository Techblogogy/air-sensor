
#ifndef MICROPHONE_MODULE
#define MICROPHONE_MODULE

#include "Arduino.h"
#include "SensorModule.h"

class MicModule : public SensorModule {

public:

    const int numSamples = 50;


    MicModule(int sPin, int adc, int db);

    void Tick();
    int Send();

private:

    double get_abs_db(int input);

    /**
      * Variables for calculating avagare microphone value
      *
      */

    int soundPin;
    int adc_sound_ref;
    int db_sound_ref;


    long soundSum = 0;
    int samples = 0;
    int soundAvg;


    // int readings[100];      // the readings from the analog input
    // int readIndex = 0;              // the index of the current reading
    // int total = 0;                  // the running total
    // int average = 0;                // the average

};

#endif
