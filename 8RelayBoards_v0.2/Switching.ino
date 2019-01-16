int pins[] = {5,4,2,14,12,13,15,3};
int maxpins = 8;
int pin;

int getPin(String Id){
  if (Id == "Switch1")
      pin = pins[0];
  else if (Id == "Switch2")
      pin = pins[1];
  else if (Id == "Switch3")
      pin = pins[2];
  else if (Id == "Switch4")
      pin = pins[3];
  else if (Id == "Switch5")
      pin = pins[4];
  else if (Id == "Switch6")
      pin = pins[5];
  else if (Id == "Switch7")
      pin = pins[6];
  else if (Id == "Switch8")
      pin = pins[7];
  else{
    postError("Invalid Switching");
  }
}

bool pinStatus(String ID){
  getPin(ID);
  pinMode(pin,INPUT);
  if(digitalRead(pin) == HIGH) 
    return true;
  else
    return false;
}

void onSwitching(String switchId){
  bool pinState = pinStatus(switchId);
  pinMode(pin,OUTPUT);
  if(pinState)
    digitalWrite(pin,LOW);
  else
    digitalWrite(pin,HIGH);
}

void switch_setup() {
  Serial.println("relay setup");
  for(int i=0; i< maxpins; i++){
   pinMode(pins[i],INPUT);
  }
}
