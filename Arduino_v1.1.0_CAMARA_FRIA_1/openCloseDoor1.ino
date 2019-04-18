
String STATIC1 = "";
long COUNT_TIMER1 = 0;
long DOOR_OPEN_COUNT_TIMER1 = 0;

const char* idTimer1 = "104";

void sendOpenClose1(String value) {
    String result = "";
      
    if(!(STATIC1 == value)) {
      
        if(value == CLOSE) {                          

            if (!client.connected())
            {
                reconnect();
            }
            
            client.publish(idTimer1, String("0").c_str(), true);
            Serial.println("Send PORTA 1 FECHADA NO E-GAS");      
     
            DOOR_OPEN_COUNT_TIMER1 = millis();
        }
        else {
            if (!client.connected())
            {
                reconnect();
            }
            
            client.publish(idTimer1, String("100000").c_str(), true);      
            Serial.println("Send PORTA 1 ABERTA NO E-GAS");
        }    
        COUNT_TIMER1 = millis();           
    }
    else {

        if((millis() - COUNT_TIMER1) > INTERVAL_SEND_TIME) {
      
            if(STATIC1 == OPEN) {
                String timeOpenedLog = String( (millis() - DOOR_OPEN_COUNT_TIMER1) / 1000);
                Serial.println("Send PORTA 1 ABERTA  POR " + timeOpenedLog  + " segundos no E-Gas");
                double timeOpened = (millis() - DOOR_OPEN_COUNT_TIMER1) * 100;

                if (!client.connected())
                {
                    reconnect();
                }
                //if(timeOpened > 0) {
                  client.publish(idTimer1, String(timeOpened).c_str(), true);                       
                //}
            }
            else {
                DOOR_OPEN_COUNT_TIMER1 = millis();
                if (!client.connected())
                {
                    reconnect();
                }
                client.publish(idTimer1, String("0").c_str(), true);                      
                                
                Serial.println("Send PORTA 1 FECHADA NO E-GAS");
            }        
            COUNT_TIMER1 = millis();
        } 
        
    }

    STATIC1 = value;
}
