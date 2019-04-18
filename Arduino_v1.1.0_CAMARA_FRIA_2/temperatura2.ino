const char* idTemperatura2 = "108";
long ultimoEnvioTemperatura2 = 0;
const long INTERVAL_SEND_TIME4 = 10000;
void sendTemperatura2()
{
    if (!client.connected())
    {
        reconnect();
    }

    long now = millis();
  
    if (now - ultimoEnvioTemperatura2 > INTERVAL_SEND_TIME4)
    {
        ultimoEnvioTemperatura2 = now;
 
        sensors2.setResolution(12);
        sensors2.requestTemperatures();
        float temperatura2 = sensors2.getTempCByIndex(0)*100000;
       
        Serial.println("Enviando Temperatura 2 ao E-gas :: " + String(temperatura2)); 
        client.publish((idTemperatura2), String(temperatura2).c_str(), true);
         
        Serial.println("Enviado com Sucesso (Waiting)...");   
    } 
}
