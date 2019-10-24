bool attachWiFi() {
  LWiFi.begin();  
  Serial.println("Conectando WiFi ...");
  int count = 0;
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD))) {
    Serial.print(".");
    delay(1000);
    count++;
    if(count >10) {
      Serial.println("Falha na conexão WiFi ...");
      return false;
    }    
  }
  Serial.println("Conectado a ..." + String(WIFI_AP));
  return true;
}

bool testClientWiFi(char host[], int port) {
  Serial.println("---------------------------------------------");
  Serial.print("Conectando ao Host [WiFi] :: " + String(host) + ":" + String(port) + ".. ");
  int count = 0;
  while (0 == clientWiFi.connect(host, port)) {
    Serial.print(".");
    delay(1000);
    count++;
    if(count >10) {
      Serial.println("Não Conectado ...");
      return false;
    }
  }
  Serial.println("Conectado."); 
  return true;
}

bool connClientWiFi(char host[], int port) {
  Serial.print("Conectando ao Host [WiFi] :: " + String(host) + ":" + String(port) + ".. ");
  int count = 0;
  while (0 == clientWiFi.connect(host, port)) {
    Serial.print(".");
    delay(1000);
    count++;
    if(count >10) {
      Serial.println("Não Conectado ...");
      return false;
    }
  }
  Serial.printLN("Conectado.";
  return true;
}

bool sendRequestUriWiFi(char host[], String uri) {
    Serial.printLN("Processando chamada REST [URI]: " + uri);
    clientWiFi.print("GET ");    
    clientWiFi.print(String(uri));
    clientWiFi.println(" HTTP/1.1");
    clientWiFi.print("Host: ");
    clientWiFi.println(host);
    clientWiFi.println("Connection: close");
    
    if (clientWiFi.println() == 0) {
        Serial.println("Falha na Requisição.");
        clientWiFi.stop();        
        return false;
    }    
    return true;
}

bool skipResponseHeadersWiFi() {
    Serial.print("Validando Response. ");
  
    char status[32] = {0};
    clientWiFi.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
        Serial.println("Response [ERRO]: " + String(status));    
        return false;
    }    
    char endOfHeaders[] = "\r\n\r\n";
    if (!clientWiFi.find(endOfHeaders)) {
        Serial.println("Response [REST] Inválida.");        
        return false;
    }    
    char endOfHeaders2[] = "\n";
    clientWiFi.find(endOfHeaders2);
    Serial.println("[OK].");
    return true;
}

bool checkReponseWiFi() {
  
  Serial.print("Response: ");
  while (clientWiFi.connected() || clientWiFi.available()) {
    if (clientWiFi.available()) {
      String line = clientWiFi.readStringUntil('\n');
      String res = line.substring(0,41);

      String respostaSistema = parseResult(res); 
      if (String(respostaSistema) == "SUCCESS") {
        Serial.println("Sistema Atualizado: " + respostaSistema);
      } else {
        Serial.println("Sistema Não Atualizado: " + respostaSistema);
      }        
      break;
    }
  }    
   return true;
}

void disconnectWiFi() {
  Serial.print("Fechando Ciclo.");
  Serial.println("");
  clientWiFi.stop();
}
