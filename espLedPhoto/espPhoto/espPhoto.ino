#include "Config.h"
#include "WIFI.h"
#include "Server.h"
#include "MQTT.h"
#define PHOTO A0

void setup(void){
  Serial.begin(115200);
  WIFI_init(false);
  //server_init();
  MQTT_init();
  pinMode(led, OUTPUT);
  mqtt_cli.subscribe("esp8266/command");
}
int minval = 10000;
int maxval = 0;
void loop() {
  int val = analogRead(PHOTO);
  String comled = "u";
  Serial.println(val);
  if (minval > val){
    minval = val;
  }
  if (maxval < val){
    maxval = val;
  }
  if (val>((minval+maxval)/2)){
    comled="d";
  }

  mqtt_cli.publish("pech/esp8266/com", comled.c_str());
  delay(500);

}
