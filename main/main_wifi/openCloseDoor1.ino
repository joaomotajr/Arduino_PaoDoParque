
const String OPEN1 = "1";
const String CLOSE1 = "0"; 
const long INTERVAL_SEND_TIME1 = 10000;

String STATIC1 = "";
long COUNT_TIMER1 = 0;
long DOOR_OPEN_COUNT_TIMER1 = 0;

const char* idTimer1 = "78";

void sendOpenClose1(String value) {
    String result = "";
      
    if(!(STATIC1 == value)) {      
        if(value == CLOSE1) {            
            send(idTimer1, String("0").c_str());            
            Serial.println("Send PORTA 1 FECHADA NO E-GAS");     
            DOOR_OPEN_COUNT_TIMER1 = millis();
        } else {
            send(idTimer1, String("100000").c_str());            
            Serial.println("Send PORTA 1 ABERTA NO E-GAS");
        }    
        COUNT_TIMER1 = millis();           
    } else {

        if((millis() - COUNT_TIMER1) > INTERVAL_SEND_TIME1) {      
            if (STATIC1 == OPEN1) {
                String timeOpenedLog = String( (millis() - DOOR_OPEN_COUNT_TIMER1) / 1000);
                Serial.println("Send PORTA 1 ABERTA  POR " + timeOpenedLog  + " segundos no E-Gas");
                double timeOpened = (millis() - DOOR_OPEN_COUNT_TIMER1) * 100;

                send(idTimer1, String(timeOpened).c_str());
            }
            else {
                DOOR_OPEN_COUNT_TIMER1 = millis();
                send(idTimer1, String("0").c_str());                                
                Serial.println("Send PORTA 1 FECHADA NO E-GAS");
            }        
            COUNT_TIMER1 = millis();
        }
    }
    STATIC1 = value;
}
