
#ifndef GLOBALS
#define GLOBALS

#define DEBUG true

/**
 * Serial Devices Baud Rates
 */

#define SERIAL_BAUD_RATE 9600
#define WIFI_BAUD_RATE 115200

/**
 *  DFRobots Microphone Constants
 */

#define MIC_PIN 1 // Analog Input Pin

#define MIC_ADC_SOUND_REF 3
#define MIC_DB_SOUND_REF 55

#define MIC_READINGS (1024 * 2) //100
#define MIC_DB_MAX (1024 / 2)


/**
 *  Sharp Dust Sensors Constants
 */

#define DUST_MEASURE_PIN 6  // Analog Input Pin
#define DUST_LED_PIN 12 // Digital Input Pin

#define DUST_SAMPLE_TIME 280
#define DUST_DELTA_TIME 40
#define DUST_SLEEP_TIME 9680

/**
 *  CO2 Sensors Constants
 */

#define CO2_TX_PIN 4 // Digital Pin
#define CO2_RX_PIN 5 // Digital Pin

/**
 * Wi-Fi Constants
 */

#define WIFI_TX_PIN 3 // Digital Pin
#define WIFI_RX_PIN 2 // Digital Pin
#define WIFI_RST_PIN 6 // Digital Pin

#define WIFI_SSID "TCDC_Guest"
#define WIFI_PASS ""
// #define WIFI_PASS "fablab"

#define WIFI_SETUP_AP_SSID "Meteo_Sensor_1" // AP Name For Setup Purposes
#define WIFI_SETUP_AP_PASS "fabricatoROKS" // AP Name For

#define WIFI_SEND_RATIO 250 //500

#define WIFI_SERVER_IP "10.1.4.5"
#define WIFI_SERVER_PORT "8000"


#endif
