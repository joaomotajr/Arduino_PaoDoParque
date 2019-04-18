
const String OPEN3 = "1";
const String CLOSE3 = "0"; 
const long INTERVAL_SEND_TIME3 = 10000;

String STATIC3 = "";
long COUNT_TIMER3 = 0;
long DOOR_OPEN_COUNT_TIMER3 = 0;

const char* idTimer3 = "95";

void sendOpenClose3(String value) {
    String result = "";
      
    if(!(STATIC3 == value)) {
      
        if(value == CLOSE3) {                          

            if (!client.connected())
            {
                reconnect();
            }
            
            client.publish(idTimer3, String("0").c_str(), true);
            Serial.println("Send PORTA 3 FECHADA NO E-GAS");      
     
            DOOR_OPEN_COUNT_TIMER3 = millis();
        }
        else {
            if (!client.connected())
            {
                reconnect();
            }
            
            client.publish(idTimer3, String("100000").c_str(), true);      
            Serial.println("Send PORTA 3 ABERTA NO E-GAS");
        }    
        COUNT_TIMER3 = millis();           
    }
    else {

        if((millis() - COUNT_TIMER3) > INTERVAL_SEND_TIME3) {
      
            if(STATIC3 == OPEN3) {
                String timeOpenedLog = String( (millis() - DOOR_OPEN_COUNT_TIMER3) / 1000);
                Serial.println("Send PORTA 3 ABERTA  POR " + timeOpenedLog  + " segundos no E-Gas");
                double timeOpened = (millis() - DOOR_OPEN_COUNT_TIMER3) * 100;

                if (!client.connected())
                {
                    reconnect();
                }
                //if(timeOpened > 0) {
                  client.publish(idTimer3, String(timeOpened).c_str(), true);                       
                //}
            }
            else {
                DOOR_OPEN_COUNT_TIMER3 = millis();
                if (!client.connected())
                {
                    reconnect();
                }
                client.publish(idTimer3, String("0").c_str(), true);                      
                                
                Serial.println("Send PORTA 3 FECHADA NO E-GAS");
            }        
            COUNT_TIMER3 = millis();
        } 
        
    }

    STATIC3 = value;
}
