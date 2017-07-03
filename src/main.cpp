#include <Arduino.h>

#include <SensorModule.h>
#include <MicModule.h>

#include "Globals.h"


/**
  *
  * Variables for calculating Sharp Dust Sensor Values
  *
  */

int measurePin = 1;
int ledPower = 12;

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;


/*
 *
 * Method for handling Sharp Dust Sensors (Main Entry Point for Dust state)
 *
 * Tutorial (Schematics) Stored Here
 * http://arduinodev.woofex.net/2012/12/01/standalone-sharp-dust-sensor/
 *
 */
void captureDust() {
    digitalWrite(ledPower,LOW); // power on the LED
    delayMicroseconds(samplingTime);

    voMeasured = analogRead(measurePin); // read the dust value

    delayMicroseconds(deltaTime);
    digitalWrite(ledPower,HIGH); // turn the LED off
    delayMicroseconds(sleepTime);

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
    // pinMode(ledPower,OUTPUT);

    initSensors();
}

void loop() {

    collectData();
    sendData();

    delay(WIFI_SEND_RATIO);

}
