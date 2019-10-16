const char* idTemperatura = "174";
long ultimoEnvioTemperatura = 0;

void sendTemperatura() {
    if (!client.connected()) {
        reconnect();
    }

    long now = millis();  
    if (now - ultimoEnvioTemperatura > INTERVAL_SEND_TIME) {
        ultimoEnvioTemperatura = now; 
        sensors.setResolution(12);
        sensors.requestTemperatures();
        float temperatura = sensors.getTempCByIndex(0)*100000;       
        Serial.println(String(millis()) + " ID [" + String(idTemperatura) + "] Enviando Temperatura ao E-gas :: " + String(temperatura)); 
        client.publish((idTemperatura), String(temperatura).c_str(), true);         
        Serial.println("Enviado com Sucesso (Waiting)...");   
    } 
}
