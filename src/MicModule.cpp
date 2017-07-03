#include "MicModule.h"

MicModule::MicModule(int pin, int adc, int db) : SensorModule() {

    soundPin = pin;
    adc_sound_ref = adc;
    db_sound_ref = db;


    // // Initilize avarage sound array
    // for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    //   readings[thisReading] = 0;
    // }
}

/*
 *
 * Method For Capturing Audio Source From Microphone (Main Entry Point for microphone state)
 *
 */
void MicModule::Tick() {
    // Serial.begin(9600);
    // Serial.println("Microphone Tick");

    soundSum = 0;

    while (++samples <= numSamples) {

        soundSum += analogRead(soundPin);


        // // subtract the last reading:
        // total = total - readings[readIndex];
        // // read from the sensor:
        // readings[readIndex] = analogRead(soundPin);
        // // add the reading to the total:
        // total = total + readings[readIndex];
        // // advance to the next position in the array:
        // readIndex = readIndex + 1;
        //
        // // if we're at the end of the array...
        // if (readIndex >= numReadings) {
        //     // ...wrap around to the beginning:
        //     readIndex = 0;
        //     break;
        // }
        //
        // // calculate the average:
        // average = total / numReadings;
        //
        // // Print some messages
        // Serial.print("Analog: ");
        // Serial.print(average);
        // Serial.print(" (");
        //
        // // Print absolute sound db from level value
        // Serial.print(get_abs_db(average));
        // Serial.print("-");
        //
        // Serial.print(analogRead(soundPin));
        // Serial.print("-");
        //
        //
        // // Print absolute sound db from SOUND_PIN read
        // Serial.print(get_abs_db(analogRead(soundPin)));
        //
        // Serial.println(" db)");
        //
        delay(1);        // delay in between reads for stability
    }

    soundAvg = soundSum / numSamples;

    // Serial.println(soundSum);
    // Serial.print(numSamples +"\n");
    Serial.println(soundAvg);


}

int MicModule::Send() {
    return 10; //soundAvg;
}

/**
 *
 * Helper Method for converting ADC microphone value into DB
 *
 * {input}  Analog read value of micrphone sensor
 *
 */
double MicModule::get_abs_db(int input) {
   return 20 * log((double)input / (double)adc_sound_ref) + db_sound_ref;
}
