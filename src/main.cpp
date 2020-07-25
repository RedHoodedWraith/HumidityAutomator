#include <Arduino.h>
#include "DHT.h"
#include <BlynkSimpleEsp8266.h>

#define SENSOR D4
#define TEMP_BLYNK V0
#define HUMID_BLYNK V1
#define THRESHOLD_BLYNK V2

// DHT Sensor Object
DHT sensor(SENSOR, DHT11);

// Humidity
float hum = -0;

// Temperature
float temp = -0;

float hum_thresh = -0;

// Authentication Token
char auth[] = "Q1L7OU4Kix7Q-3Hq6u3ms_jJEIAE4cZQ";

// WiFi Connection
char* ssid = "RdA Net";
char* pass = "Fsh^9MjkMUYLCvHB1REJ";
/*char* ssid = "The Black Phoenix";
char* pass = "*Iam2C0ol4this";*/

/**
 * Updates the Temperature & Humidity Values
 */
void update(){
    hum = sensor.readHumidity();
    temp = sensor.readTemperature();
    delay(250);
}

/**
 * Sends the Data to the Blynk Server
 */
void syncData(){
    Blynk.virtualWrite(TEMP_BLYNK, temp);
    Blynk.virtualWrite(HUMID_BLYNK, hum);
}

/**
 * Reports the data to the Serial Monitor
 */
void reportData(){
    Serial.print("Humidity: ");
    Serial.println(hum);
    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.println();
}

/**
 * Attempts to connect to WiFi
 */
void connectToWiFi(){
    Blynk.connectWiFi(ssid, pass);
    if(Blynk.connected()){
        Blynk.config(auth);
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println("Welcome to Humidity Automator");
    sensor.begin();

}

void loop() {
    update();
    reportData();
    syncData();
}