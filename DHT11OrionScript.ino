#include <ESP8266WiFi.h>
#include <WiFiServerSecureBearSSL.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFiScan.h>
#include <WiFiClient.h>
#include <BearSSLHelpers.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiServerSecure.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiUdp.h>
#include <ESP8266WiFiGeneric.h>
#include <WiFiServerSecureAxTLS.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiAP.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFiType.h>
#include <ESP8266WiFiSTA.h>
#include <WiFiServer.h>

#include <ESP8266HTTPClient.h>

#include "DHT.h"
#define DHTTYPE DHT11

#define dht_dpin 13
DHT dht(dht_dpin, DHTTYPE);

const char* ssid = "Robby";
const char* password = "0l30l4ng";

uint8_t BLUE_LED_PIN = 12;
uint8_t WHITE_LED_PIN = 15;

void setup() {
  Serial.begin(115200);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(WHITE_LED_PIN, OUTPUT);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting...");  
  }
  dht.begin();
  delay(500);
  
}

void loop() {
  if ( WiFi.status() == WL_CONNECTED ) {
    digitalWrite(WHITE_LED_PIN, HIGH);
  } else {
    digitalWrite(WHITE_LED_PIN, LOW); 
  }
  Serial.print("Current humidity = ");
  Serial.print(dht.readHumidity());
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(dht.readTemperature()); 
  Serial.println("C  ");

  if ( dht.readTemperature() < 31 ) {
    digitalWrite(BLUE_LED_PIN, LOW);
  } else {
    digitalWrite(BLUE_LED_PIN, HIGH);
  }
  
  delay(500);
}
