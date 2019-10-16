const char* idTemperaturaD6 = "175";
long ultimoEnvioTemperaturaD6 = 0;

void sendTemperaturaD6() {
    if (!client.connected()) {
        reconnect();
    }

    long now = millis();  
    if (now - ultimoEnvioTemperaturaD6 > INTERVAL_SEND_TIME) {
        ultimoEnvioTemperaturaD6 = now; 
        sensorsD6.setResolution(12);
        sensorsD6.requestTemperatures();
        float temperaturaD6 = sensorsD6.getTempCByIndex(0)*100000;       
        Serial.println(String(millis()) + " ID [" + String(idTemperaturaD6) + "] Enviando Temperatura ao E-gas :: " + String(temperaturaD6)); 
        client.publish((idTemperaturaD6), String(temperaturaD6).c_str(), true);         
        Serial.println("Enviado com Sucesso (Waiting)...");   
    } 
}
