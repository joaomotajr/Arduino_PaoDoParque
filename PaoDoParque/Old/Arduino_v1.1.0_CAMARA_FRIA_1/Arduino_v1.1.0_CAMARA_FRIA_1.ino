#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const char* ssid = "ENESENS 2.4G";
const char* password = "3012enesens";
//const char* ssid = "SMART_DEVICE";
//const char* password = "3012enesens@2018";
//const char* mqtt_server = "e-gas.net.br";
const char* mqtt_server = "www.e-gas.net.br";

// Controle de status de porta aberta ou fechada + o tempo de intervalo
const String OPEN = "1";
const String CLOSE = "0"; 
const long INTERVAL_SEND_TIME = 10000;


// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient_CamaraFria1;
PubSubClient client(wifiClient_CamaraFria1);

int SensorPorta1 = D1;


void setup() {
    Serial.begin(9600);
    pinMode (SensorPorta1, INPUT_PULLUP);
    

  
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
  }
    
 }

