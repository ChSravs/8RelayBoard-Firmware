void onConnected(){
  String msg;
  const size_t capacity = JSON_OBJECT_SIZE(2);
  DynamicJsonBuffer jsonBuffer(capacity);
  JsonObject& onwifi = jsonBuffer.createObject();
  
  onwifi["Mode"] = "On Connected";
  onwifi["SSID"] = WIFI_SSID;
  onwifi["IP"] = String(myIp);
  onwifi["MAC"] = mac;
  onwifi.printTo(msg);
  
  mqttClient.publish("event", 2, true, msg.c_str());
  Serial.println("Connected msg published");
}

void onDisconnected(){
  String msg;
  const size_t capacity = JSON_OBJECT_SIZE(2);
  DynamicJsonBuffer jsonBuffer(capacity);
  JsonObject& offwifi = jsonBuffer.createObject();
  
  offwifi["Mode"] = "On Disconnected";
  offwifi["IP"] = "0.0.0.0";
  offwifi.printTo(msg);
  
  mqttClient.publish("event", 2, true, msg.c_str());
  Serial.println("Disconnected msg published");
}

void postError(String Message){
  String msg;
  const size_t capacity = JSON_OBJECT_SIZE(2);
  DynamicJsonBuffer jsonBuffer(capacity);
  JsonObject& error = jsonBuffer.createObject();
  
  error["Mode"] = "Error";
  error["Description"] = Message;
  error.printTo(msg);
  
  mqttClient.publish("event", 2, true, msg.c_str());
  Serial.println("Error msg published");
}

void getStatus(){
  String msg;
  const size_t capacity = JSON_OBJECT_SIZE(8);
  DynamicJsonBuffer jsonBuffer(capacity);
  JsonObject& action = jsonBuffer.createObject();
  
  action["Switch1"] = pinStatus("Switch1");
  action["Switch2"] = pinStatus("Switch2");
  action["Switch3"] = pinStatus("Switch3");
  action["Switch4"] = pinStatus("Switch4");
  action["Switch5"] = pinStatus("Switch5");
  action["Switch6"] = pinStatus("Switch6");
  action["Switch7"] = pinStatus("Switch7");
  action["Switch8"] = pinStatus("Switch8");
  action.printTo(msg);
  
  mqttClient.publish("event", 2, true, msg.c_str());
  Serial.println("event msg published"); 
}
