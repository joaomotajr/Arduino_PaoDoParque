String STATIC2 = "";
long COUNT_TIMER2 = 0;
long DOOR_OPEN_COUNT_TIMER2 = 0;
const char* idTimer2 = "176";

void sendOpenClose2(String value) {
    String result = "";      
    if(!(STATIC2 == value)) {      
        if(value == CLOSE) {
            if (!client.connected()) {
                reconnect();
            }            
            client.publish(idTimer2, String("0").c_str(), true);
            Serial.println(String(millis()) + " ID [" + String(idTimer2) + "] Send PORTA 2 FECHADA NO E-GAS");     
            DOOR_OPEN_COUNT_TIMER2 = millis();
        }
        else {
            if (!client.connected()) {
                reconnect();
            }            
            client.publish(idTimer2, String("100000").c_str(), true);      
            Serial.println(String(millis()) + " ID [" + String(idTimer2) + "] Send PORTA 2 ABERTA NO E-GAS");
        }    
        COUNT_TIMER2 = millis();           
    } else {
        if((millis() - COUNT_TIMER2) > INTERVAL_SEND_TIME) {      
            if(STATIC2 == OPEN) {
                String timeOpenedLog = String( (millis() - DOOR_OPEN_COUNT_TIMER2) / 1000);
                Serial.println(String(millis()) + " ID [" + String(idTimer2) + "] Send PORTA 2 ABERTA  POR " + timeOpenedLog  + " segundos no E-Gas");
                double timeOpened = (millis() - DOOR_OPEN_COUNT_TIMER2) * 100;

                if (!client.connected()) {
                    reconnect();
                }
                //if(timeOpened > 0) {
                  client.publish(idTimer2, String(timeOpened).c_str(), true);                       
                //}
            }
            else {
                DOOR_OPEN_COUNT_TIMER2 = millis();
                if (!client.connected()) {
                    reconnect();
                }
                client.publish(idTimer2, String("0").c_str(), true);                                
                Serial.println(String(millis()) + " ID [" + String(idTimer2) + "] Send PORTA 2 FECHADA NO E-GAS");
            }        
            COUNT_TIMER2 = millis();
        }        
    }
    STATIC2 = value;
}
