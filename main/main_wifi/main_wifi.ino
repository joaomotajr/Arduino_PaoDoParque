#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const char* ssid = "SMART_DEVICE";
const char* password = "3012enesens@2018";

char connType[] = "WIFI"; 
char host[] = "177.144.134.145";
char uri[] = "/api/historic/SaveByPositionIOT/";
char uriDate[] = "/api/util/time/";
int port = 8090;

WiFiClient clientWiFi;
int SensorPorta1 = D4;

void setup() {
    Serial.begin(115200);
    pinMode (SensorPorta1, INPUT_PULLUP);

    wifi_init();
} 

void loop() {  
  sendTemperatura();   
  sendOpenClose1(String(digitalRead(SensorPorta1)));  
}

