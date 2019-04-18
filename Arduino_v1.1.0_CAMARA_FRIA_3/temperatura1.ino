const char* idTemperatura1 = "111";
long ultimoEnvioTemperatura1 = 0;
const long INTERVAL_SEND_TIME3 = 10000;
void sendTemperatura1()
{
    if (!client.connected())
    {
        reconnect();
    }

    long now = millis();
  
    if (now - ultimoEnvioTemperatura1 > INTERVAL_SEND_TIME3)
    {
        ultimoEnvioTemperatura1 = now;
 
        sensors1.setResolution(12);
        sensors1.requestTemperatures();
        float temperatura1 = sensors1.getTempCByIndex(0)*100000;
       
        Serial.println("Send ID 111 Temperatura 1 ao E-gas :: " + String(temperatura1)); 
        client.publish((idTemperatura1), String(temperatura1).c_str(), true);
         
        Serial.println("Enviado com Sucesso (Waiting)...");   
    } 
}
