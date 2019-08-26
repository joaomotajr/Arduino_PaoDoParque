#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const char* ssid = "SMART_DEVICE";
const char* password = "3012enesens@2018";
const char* mqtt_server = "www.e-gas.net.br";
//const char* mqtt_server = "e-gas.net.br";



// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient_Geladeira1;
PubSubClient client(wifiClient_Geladeira1);

int SensorPorta1 = D1;
int SensorPorta2 = D2;
int SensorPorta3 = D6;
int SensorPorta4 = D7;

void setup() {
    Serial.begin(115200);
    pinMode (SensorPorta1, INPUT_PULLUP);
    pinMode (SensorPorta2, INPUT_PULLUP);
    pinMode (SensorPorta3, INPUT_PULLUP);
    pinMode (SensorPorta4, INPUT_PULLUP);
  
    // Seta o servidor MQTT
    client.setServer(mqtt_server, 1883);   
    
    wifi_init();
  
    if (!client.connected())
    {
        reconnect();
    }
} 

void loop() {
  {
    sendTemperatura();
  }
    
  { 
    sendOpenClose1(String(digitalRead(SensorPorta1))); 
  {
    
  }
    sendOpenClose2(String(digitalRead(SensorPorta2)));
  }
  
  { 
    sendOpenClose3(String(digitalRead(SensorPorta3))); 
  {
    
  }
    sendOpenClose4(String(digitalRead(SensorPorta4)));
  }
}

