#include "Config.h"
#include "WIFI.h"
#include "Server.h"
#include "MQTT.h"


void setup(void){
  Serial.begin(115200);
  WIFI_init(false);
  pinMode(led, OUTPUT);
  //server_init();
  MQTT_init();
  
  mqtt_cli.publish("pech/esp8266/state", "hello emqx");
  mqtt_cli.subscribe(topicval);
  mqtt_cli.subscribe(topicmin);
  mqtt_cli.subscribe(topicmax);
}

void loop(void){
  
  //server.handleClient();                   
  mqtt_cli.loop();
}
