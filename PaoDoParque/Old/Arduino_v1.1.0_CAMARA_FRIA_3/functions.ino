void wifi_init() {

    delay(10);
    Serial.println();
    
    Serial.print("Connecting to ");
    Serial.println(ssid);
  
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
    // Loop até reconectar
    while (!client.connected()) {
        Serial.print("Aguardando Conexão MQTT ...");
        
        if (client.connect("Camara Fria 3")) {
            Serial.println("conectado");          
        }
        else {
            Serial.print("Falha, rc=");
            Serial.print(client.state());
            Serial.println(" Tentando Novamente em 5 segundos...");
          
            delay(5000);
        }
    }  
}
