
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

#define MIC_PIN 2 // Analog Input Pin

#define MIC_ADC_SOUND_REF 5
#define MIC_DB_SOUND_REF 38

#define MIC_READINGS 100

/**
 *  Sharp Dust Sensors Constants
 */

#define DUST_MEASURE_PIN 1  // Analog Input Pin
#define DUST_LED_PIN 12 // Digital Input Pin

#define DUST_SAMPLE_TIME 280
#define DUST_DELTA_TIME 40
#define DUST_SLEEP_TIME 9680

/**
 *  CO2 Sensors Constants
 */

#define CO2_TX_PIN 5 // Digital Input Pin
#define CO2_RX_PIN 6 // Digital Input Pin

/**
 * Wi-Fi Constants
 */

#define WIFI_TX_PIN 2 // Digital Input Pin
#define WIFI_RX_PIN 3 // Digital Input Pin

#define WIFI_SETUP_AP_SSID "Meteo_Sensor_1" // AP Name For Setup Purposes
#define WIFI_SETUP_AP_PASS "fabricatoROKS" // AP Name For

#define WIFI_SEND_RATIO 30000

#define WIFI_SERVER_IP "10.1.4.5"
#define WIFI_SERVER_PORT "8000"


#endif
