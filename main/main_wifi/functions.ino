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

send(String id, String value) {
    String dataReaded = String(id) + "/" + String(value*100000).c_str();
    if(sendRequestUriWiFi(host, String(uri) + String(dataReaded))) {
        if (skipResponseHeadersWiFi()) {
            checkReponseWiFi();
        } 
    }
}