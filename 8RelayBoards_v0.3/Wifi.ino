void connectToWifi() {
  WiFi.disconnect();
  delay(100);
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to Wi-Fi...SSID is ");
  Serial.println(ssid);
  WiFi.begin(ssid.c_str(), password.c_str());
  if ( testWifi() == 20 ) { 
      return;
  }
  Serial.println("Opening AP");
  setupAP(); 
}

int testWifi(void) {
  int c = 0; 
  while ( c < 30 ) {
    if (WiFi.status() == WL_CONNECTED) { return(20); } 
    delay(500);
    Serial.print(".");    
    c++;
  }
  Serial.println("WiFi Connect timed out!");
  return(10);
} 

void setupAP(void) {
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0){
    Serial.println("no networks found");
//    st ="<b>No networks found:</b>";
  } else {
    Serial.print(n);
    Serial.println(" Networks found");
//    st = "<ul>";
    for (int i = 0; i < n; ++i)
     {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" (OPEN)":"*");
      
      // Print to web SSID and RSSI for each network found
//      st += "<li>";
//      st +=i + 1;
//      st += ": ";
//      st += WiFi.SSID(i);
//      st += " (";
//      st += WiFi.RSSI(i);
//      st += ")";
//      st += (WiFi.encryptionType(i) == ENC_TYPE_NONE)?" (OPEN)":"*";
//      st += "</li>";
      delay(10);
     }
//    st += "</ul>";
  }
  Serial.println(""); 
  WiFi.disconnect();
  delay(100);
  WiFi.mode(WIFI_AP);

  
  WiFi.softAP(host.c_str());
  WiFi.begin(host.c_str()); // not sure if need but works
  Serial.print("Access point started with name ");
  Serial.println(host);
}

void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  Serial.println("Connected to Wi-Fi.");
  myIp = WiFi.localIP();
  mac = WiFi.macAddress();
  Serial.print("IP address: ");
  Serial.println(myIp);
  Serial.print("MAC address: ");
  Serial.println(mac);
  connectToMqtt();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  Serial.println("Disconnected from Wi-Fi.");
  onDisconnected();
  mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
  wifiReconnectTimer.once(2, connectToWifi);
}

void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}
