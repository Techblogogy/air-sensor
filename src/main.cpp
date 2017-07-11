#include <Arduino.h>
#include <SoftwareSerial.h>

#include <SensorModule.h>
#include <MicModule.h>

#include "wifi/SerialESP8266wifi.h"

#include "Globals.h"

// TODO: Plan For Today:

// TODO: Calibrated Audio 

// TODO: Setup ESP8266 to receive data from Arduino
// TODO: Setup ESP8266 to transmit data to Agents server

// TODO: Send sensor data over wifi



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

        ppmCO2 = (256 * responseHigh) + responseLow;

        Serial.println(ppmCO2);
    }

    delay(10000);
}

/*
 *
 * Methods for handling audio capture
 *
 */

int audioAnalog = 0;
double audioValue = 0;

void initAudio() {

}

double get_abs_db(int input) {
   return 20 * log((double)input / (double)MIC_ADC_SOUND_REF) + MIC_DB_SOUND_REF;
}

void captureAudio() {
    Serial.println(audioAnalog);

    for (int i=0; i<MIC_READINGS) {
        audioAnalog += analogRead(MIC_PIN);
        delay(1);
    }
    audioAnalog /= MIC_READINGS;

    Serial.println(audioAnalog);


    // audioValue = get_abs_db(audioAnalog);
    // Serial.println(audioValue);
}

/**
  *
  * WiFi connection
  *
  */

SoftwareSerial wifiSerial(WIFI_TX_PIN, WIFI_RX_PIN);
SerialESP8266wifi wifi(wifiSerial, wifiSerial, WIFI_RST_PIN);

bool wifiCon = false;
bool wifiLocal = false;

void initWifi() {

    // wifiSerial.begin(115200);

    // bool wifiStart = wifi.begin();

    // if (wifiStart) {
    //     wifiCon = wifi.connectToAP(WIFI_SSID, WIFI_PASS);

    //     if (wifi.isConnectedToAP()) {
    //         Serial.println("Connected to Wi-Fi");
    //     } else {
    //         Serial.println("Wi-Fi Connection Failed");

    //         wifiLocal = wifi.startLocalAPAndServer(WIFI_SETUP_AP_SSID, WIFI_SETUP_AP_PASS, "6", "8080");

    //         if (wifi.isLocalAPAndServerRunning()) {
    //             Serial.println("Started Local AP and Server");
    //         } else {
    //             Serial.println("Failed to start local AP and server");
    //         }
    //     }
    // } else {
    //     Serial.println("Failed to start Wifi Module");
    // }

}

void sendWifi() {

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

    initWifi();

    // // Initialize LED for Sharp Dust Sensor
    initAudio();
    initDust();
    initCO2();

    // initSensors();
}

void loop() {

    // collectData();
    // sendData();

    captureAudio();
    // captureDust();
    // captureCO2();

    delay(WIFI_SEND_RATIO);
}
