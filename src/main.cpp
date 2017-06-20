#include <Arduino.h>

#define SOUND_PIN 0

#define ADC_SOUND_REF 5
#define DB_SOUND_REF 38


/**
  * Variables for calculating avagare microphone value
  *
  */
const int numReadings = 100;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average


/**
 *
 * Helper Method for converting ADC microphone value into DB
 *
 * {input}  Analog read value of micrphone sensor
 *
 */
double get_abs_db(int input) {
   return 20 * log((double)input / (double)ADC_SOUND_REF) + DB_SOUND_REF;
}

/*
 *
 * Method For Capturing Audio Source From Microphone (Main Entry Point for microphone state)
 *
 */
void captureSound() {
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(SOUND_PIN);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;

  // Print some messages
  Serial.print("Analog: ");
  Serial.print(average);
  Serial.print(" (");

  // Print absolute sound db from level value
  Serial.print(get_abs_db(average));
  Serial.print("-");

  // Print absolute sound db from SOUND_PIN read
  Serial.print(get_abs_db(analogRead(SOUND_PIN)));

  Serial.println(" db)");

  delay(1);        // delay in between reads for stability
}

/**
  * Variables for calculating avagare microphone value
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


/**
 *
 * Method for handling CO sensor (Main Entry Point for CO state)
 *
 */
void catpureCO() {

}


/**
 *
 * Connect ESP8266 to Wi-Fi AP
 *
 */
void wifiConnect() {

}

/**
 *
 * Send Data to Server
 *
 */
void dataSend() {

}



void setup() {
  // Initilize hardware serial
  Serial.begin(9600);

  // Initilize avarage sound array
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  // Initialize LED for Sharp Dust Sensor
  pinMode(ledPower,OUTPUT);

}

void loop() {
//  captureSound();
  captureDust();
}
