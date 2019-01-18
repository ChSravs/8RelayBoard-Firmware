#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager


char dtype[40]="8 Channel Relay";
char dmodel[40] = "Armtronix";
char dver[40] = "v1.0";
char rid[40];
char fname[40];
char uname[40];
char pwd[40];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFiManagerParameter custom_dtype("dtype", "Device Type", dtype, 40 , "readonly");
  WiFiManagerParameter custom_dmodel("dmodel", "Device Model", dmodel, 40 , "readonly");
  WiFiManagerParameter custom_dver("dver", "Device Version", dver, 40 , "readonly");
  
  WiFiManagerParameter custom_rid("rid", "Resource ID", rid , 40);
  WiFiManagerParameter custom_fname("fname", "Friendly Name", fname , 40);
  WiFiManagerParameter custom_uname("uname", "User Name", uname , 40);
  WiFiManagerParameter custom_pwd("pwd", "Password", pwd , 40);
  
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //reset settings - for testing
  wifiManager.resetSettings();
  WiFiManagerParameter custom_text1("<p>Device details</p>");
  wifiManager.addParameter(&custom_text1);
  wifiManager.addParameter(&custom_rid);
  wifiManager.addParameter(&custom_fname);
  wifiManager.addParameter(&custom_dtype);
  wifiManager.addParameter(&custom_dmodel);
  wifiManager.addParameter(&custom_dver);
  WiFiManagerParameter custom_text2("<p>User details</p>");
  wifiManager.addParameter(&custom_text2);
  wifiManager.addParameter(&custom_uname);
  wifiManager.addParameter(&custom_pwd);
  
  //sets timeout until configuration portal gets turned off
  //useful to make it all retry or go to sleep
  //in seconds
  wifiManager.setTimeout(180);
  
  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if(!wifiManager.autoConnect("AutoConnectAP")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  } 

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  strcpy(dtype, custom_dtype.getValue());
  Serial.println(dtype);
  strcpy(rid, custom_rid.getValue());
  Serial.println(rid);
  strcpy(fname, custom_fname.getValue());
  Serial.println(fname);
  strcpy(uname, custom_uname.getValue());
  Serial.println(uname);
  strcpy(pwd, custom_pwd.getValue());
  Serial.println(pwd);
  Serial.println(dmodel);
  Serial.println(dver);
 
}

void loop() {
  // put your main code here, to run repeatedly:

}
