#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS_1 D7
#define ONE_WIRE_BUS_2 D6

OneWire oneWire1(ONE_WIRE_BUS_1);
OneWire oneWire2(ONE_WIRE_BUS_2);

DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);

const char* ssid = "SMART_DEVICE";
const char* password = "3012enesens@2018";
const char* mqtt_server = "www.e-gas.net.br";
//const char* mqtt_server = "177.139.183.153";



// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient_CamaraFria2;
PubSubClient client(wifiClient_CamaraFria2);

int SensorPorta1 = D1;
int SensorPorta2 = D2;

void setup() {
    Serial.begin(115200);
    pinMode (SensorPorta1, INPUT_PULLUP);
    pinMode (SensorPorta2, INPUT_PULLUP);

  
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
    sendTemperatura1();
  }

  {
    sendTemperatura2();
  }
    
  { 
    sendOpenClose1(String(digitalRead(SensorPorta1))); 
  {
    
  }
    sendOpenClose2(String(digitalRead(SensorPorta2)));
  }
}

