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
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiAP.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFiType.h>
#include <ESP8266WiFiSTA.h>
#include <WiFiServer.h>
#include <ESP8266HTTPClient.h>

#define BLUE_LED_PIN 12
#define RED_LED_PIN 13
#define GREEN_LED_PIN 14

const char* ssid = "Robby";
const char* password = "0l30l4ng";

uint8_t serverStatusState = 0;
ESP8266WebServer server(80);

void _serverInitFailedBlinking();
void _handleRequest();
void __notFoundHandler();
void _initController();

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    pinMode(BLUE_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);

    /* Starting initial led start up */
    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(700);
    digitalWrite(GREEN_LED_PIN, LOW);
    delay(700);

    digitalWrite(BLUE_LED_PIN, HIGH);
    delay(700);
    digitalWrite(BLUE_LED_PIN, LOW);
    delay(700);

    digitalWrite(RED_LED_PIN, HIGH);
    delay(700);
    digitalWrite(RED_LED_PIN, LOW);

    delay(1000);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting...");
    }
    Serial.println("Connected with local IP address as: ");
    Serial.println(WiFi.localIP());

    if ( MDNS.begin("esp8266") ) {
        _initController();
        server.begin();
        Serial.println("Server Started...");
    } else {
        _serverInitFailedBlinking();
        Serial.println("mDNS responder failed to start. Please re-start the esp8266");
    }
}

void loop() {
    if ( WiFi.status() == WL_CONNECTED ) {
        digitalWrite(GREEN_LED_PIN, HIGH);
    } else {
        digitalWrite(GREEN_LED_PIN, LOW); 
    }
    server.handleClient();
}

void _serverInitFailedBlinking() {
    /* 
        RED LIGHT BLINKING FOR 3 TIMES MEANS THE SERVER START UP HAS BEEN FAILED.
        THE BEST THING YOU CAN DO IS RESTART THE ESP8266
    */
   digitalWrite(RED_LED_PIN, HIGH);
   delay(400);
   digitalWrite(RED_LED_PIN, LOW);
   delay(400);
   digitalWrite(RED_LED_PIN, HIGH);
   delay(400);
   digitalWrite(RED_LED_PIN, LOW);
   delay(400);
   digitalWrite(RED_LED_PIN, HIGH);
   delay(400);
   digitalWrite(RED_LED_PIN, LOW);
}

void _handleRequest() {
    digitalWrite(BLUE_LED_PIN, HIGH);
    server.send(200, "application/json", "{\"status\": true, \"message\": \"This sensor is on development progress. Please wait for the initial launch.\"}");
    digitalWrite(BLUE_LED_PIN, LOW);
}

void _notFoundHandler() {
    digitalWrite(RED_LED_PIN, HIGH);
    server.send(404, "application/json", "{\"status\": true, \"message\": \"This sensor is on development progress. Please wait for the initial launch.\"}");
    digitalWrite(RED_LED_PIN, LOW);
}

void _initController() {
    server.on("/", HTTP_GET, []() {
        digitalWrite(BLUE_LED_PIN, HIGH);
        server.send(200, "application/json", "{\"status\": true, \"message\": \"Hello from ORION CONTROLLER\"}");
        digitalWrite(BLUE_LED_PIN, LOW);
    });
    server.on("/get-dht-sensor-value", HTTP_POST, _handleRequest);
    server.onNotFound(_notFoundHandler);
}