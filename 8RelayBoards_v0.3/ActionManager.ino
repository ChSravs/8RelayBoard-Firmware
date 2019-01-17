const char* actionMode;
const char* switchId;

void actionManager(String payload){
  JsonObject& root = jsonBuffer.parseObject(payload);
  actionMode = root["action"];
  switchId = root["switchId"];
  Serial.println(actionMode);
  Serial.println(switchId);
  if(String(actionMode) == "Switching"){
    onSwitching(String(switchId));
    getStatus();
  }
  else if(String(actionMode) == "Status")
    getStatus();
  else{
    postError("Invalid Action");
  }
}
