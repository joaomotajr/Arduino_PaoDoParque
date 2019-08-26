
const String OPEN4 = "1";
const String CLOSE4 = "0"; 
const long INTERVAL_SEND_TIME4 = 10000;

String STATIC4 = "";
long COUNT_TIMER4 = 0;
long DOOR_OPEN_COUNT_TIMER4 = 0;

const char* idTimer4 = "96";

void sendOpenClose4(String value) {
    String result = "";
      
    if(!(STATIC4 == value)) {
      
        if(value == CLOSE4) {                          

            if (!client.connected())
            {
                reconnect();
            }
            
            client.publish(idTimer4, String("0").c_str(), true);
            Serial.println("Send PORTA 4 FECHADA NO E-GAS");      
     
            DOOR_OPEN_COUNT_TIMER4 = millis();
        }
        else {
            if (!client.connected())
            {
                reconnect();
            }
            
            client.publish(idTimer4, String("100000").c_str(), true);      
            Serial.println("Send PORTA 4 ABERTA NO E-GAS");
        }    
        COUNT_TIMER4 = millis();           
    }
    else {

        if((millis() - COUNT_TIMER4) > INTERVAL_SEND_TIME4) {
      
            if(STATIC4 == OPEN4) {
                String timeOpenedLog = String( (millis() - DOOR_OPEN_COUNT_TIMER4) / 1000);
                Serial.println("Send PORTA 4 ABERTA  POR " + timeOpenedLog  + " segundos no E-Gas");
                double timeOpened = (millis() - DOOR_OPEN_COUNT_TIMER4) * 100;

                if (!client.connected())
                {
                    reconnect();
                }
                //if(timeOpened > 0) {
                  client.publish(idTimer4, String(timeOpened).c_str(), true);                       
                //}
            }
            else {
                DOOR_OPEN_COUNT_TIMER4 = millis();
                if (!client.connected())
                {
                    reconnect();
                }
                client.publish(idTimer4, String("0").c_str(), true);                      
                                
                Serial.println("Send PORTA 4 FECHADA NO E-GAS");
            }        
            COUNT_TIMER4 = millis();
        } 
        
    }

    STATIC4 = value;
}
