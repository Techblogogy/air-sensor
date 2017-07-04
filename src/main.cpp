#include <Arduino.h>

#include <SensorModule.h>
#include <MicModule.h>

#include <SoftwareSerial.h>

#include "Globals.h"

// TODO: Plan For Today:

// TODO: Upload code into Chineese Arduino (+)

// TODO: Get Data from Dust Sensor +
// TODO: Hook in CO2 Sensor +
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

float voMeasured = 0; // Measured Voltage 
float calcVoltage = 0; // Calculated Voltage
float dustDensity = 0; // Dust density calculation

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


/*
 *
 * Methods for handling CO2 dust sensor
 *
 */

SoftwareSerial co2Serial(CO2_TX_PIN, CO2_RX_PIN);

byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; 
unsigned char response[9];

unsigned int ppmCO2 = 0;

void initCO2() {
    co2Serial.begin(9600);
}

void captureCO2() {
    co2Serial.write(cmd, 9);

    memset(response, 0, 9);
    co2Serial.readBytes(response, 9);

    // Serial.println(response);

    int i;
    byte crc = 0;
    for (i = 1; i < 8; i++) crc+=response[i];
    crc = 255 - crc;
    crc++;

    if ( !(response[0] == 0xFF && response[1] == 0x86 && response[8] == crc) ) {
        Serial.println("CRC error: " + String(crc) + " / "+ String(response[8]));
    } else {
        unsigned int responseHigh = (unsigned int) response[2];
        unsigned int responseLow = (unsigned int) response[3];
        ppmCO2 = (256*responseHigh) + responseLow;

        Serial.println(ppmCO2);
    }

    delay(10000);
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
    // initDust();
    initCO2();

    // initSensors();
}

void loop() {

    // collectData();
    // sendData();

    // captureDust();
    captureCO2();

    // delay(WIFI_SEND_RATIO);
}
