#include <Arduino.h>

#include <SensorModule.h>
#include <MicModule.h>

#include "Globals.h"

// TODO: Plan For Today:

// TODO: Upload code into Chineese Arduino (+)

// TODO: Get Data from Dust Sensor +
// TODO: Hook in CO2 Sensor 
// TODO: Calibrated Audio

// TODO: Create Universal Data Buffer

// TODO: Send sensor data over wifi


/**
  *
  * Variables for calculating Sharp Dust Sensor Values
  *
  */

// int measurePin = 1;
// int ledPower = 12;

// int samplingTime = 280;
// int deltaTime = 40;
// int sleepTime = 9680;



/*
 *
 * Methods for handling Sharp Dust Sensors (Main Entry Point for Dust state)
 *
 * Tutorial (Schematics) Stored Here
 * http://arduinodev.woofex.net/2012/12/01/standalone-sharp-dust-sensor/
 *
 */

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void initDust() {
    pinMode(DUST_LED_PIN, OUTPUT);
}

void captureDust() {
    digitalWrite(DUST_LED_PIN, LOW); // power on the LED
    delayMicroseconds(DUST_SAMPLE_TIME);

    voMeasured = analogRead(DUST_MEASURE_PIN); // read the dust value

    delayMicroseconds(DUST_DELTA_TIME);
    digitalWrite(DUST_LED_PIN, HIGH); // turn the LED off
    delayMicroseconds(DUST_SLEEP_TIME);

    // 0 - 3.3V mapped to 0 - 1023 integer values
    // recover voltage
    calcVoltage = voMeasured * (3.3 / 1024);

    // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
    // Chris Nafis (c) 2012
    dustDensity = 0.17 * calcVoltage - 0.1;

    Serial.print("Raw Signal Value (0-1023): ");
    Serial.print(voMeasured);

    Serial.print(" - Voltage: ");
    Serial.print(calcVoltage);

    Serial.print(" - Dust Density: ");
    Serial.println(dustDensity);

    delay(1000);
}


const int moduleCount = 3;
SensorModule *sensors[moduleCount] = {
    new MicModule(MIC_PIN, MIC_ADC_SOUND_REF, MIC_DB_SOUND_REF),
    new SensorModule()
};

void initSensors() {
}

void collectData() {

    for (int i=0; i<moduleCount; i++) {
        sensors[i]->Tick();
    }

}

void sendData() {
    for (int i=0; i<moduleCount; i++) {
        // Serial.println(sensors[i]->Send());
    }
}


void setup() {
    // Initilize hardware serial
    Serial.begin(9600);

    // // Initialize LED for Sharp Dust Sensor
    initDust();

    // initSensors();
}

void loop() {

    // collectData();
    // sendData();

    captureDust();

    // delay(WIFI_SEND_RATIO);
}
