#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define ONE_WIRE_BUS_D6 D6
OneWire oneWireD6(ONE_WIRE_BUS_D6);
DallasTemperature sensorsD6(&oneWireD6);

const char* ssid = "CARI";
const char* password = "P@lmeiras";
const char* mqtt_server = "www.e-gas.tech";

// Controle de status de porta aberta ou fechada + o tempo de intervalo
const String OPEN = "1";
const String CLOSE = "0"; 
const long INTERVAL_SEND_TIME = 10000;

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient_CamaraFria1;
PubSubClient client(wifiClient_CamaraFria1);

int SensorPorta1 = D1;
int SensorPorta2 = D2;

void setup() {
    Serial.begin(115200);
    Serial.println("Inicializando Dispositivo ....");
    pinMode (SensorPorta1, INPUT_PULLUP);
    pinMode (SensorPorta2, INPUT_PULLUP);

    // Seta o servidor MQTT
    client.setServer(mqtt_server, 1883);   
    wifi_init();  
    
    if (!client.connected()) {
        reconnect();
    }
} 

void loop() {
  sendTemperatura();
  sendTemperaturaD6();
  sendOpenClose1(String(digitalRead(SensorPorta1)));      
  sendOpenClose2(String(digitalRead(SensorPorta2)));      
}
