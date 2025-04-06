#include "Config.h"
#include "WIFI.h"
#include "Server.h"
#include "MQTT.h"
//#include <SoftwareSerial.h>
 
//SoftwareSerial mySerial(10, 11); // RX, TX
void setup(void){
  Serial.begin(115200);
  //mySerial.begin(4800);
  WIFI_init(true);
  server_init();
  pinMode(led, OUTPUT);
}

void loop(void){
  server.handleClient();
}