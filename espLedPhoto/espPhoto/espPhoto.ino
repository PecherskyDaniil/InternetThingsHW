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
  Serial.println(val);
  if (minval > val){
    minval = val;
  }
  if (maxval < val){
    maxval = val;
  }
  char cstr[16];
  itoa(val, cstr, 10);
  mqtt_cli.publish("pech/esp8266/val", cstr);
  char minstr[16];
  itoa(minval, minstr, 10);
  mqtt_cli.publish("pech/esp8266/min", minstr);
  char maxstr[16];
  itoa(maxval, maxstr, 10);
  mqtt_cli.publish("pech/esp8266/max", maxstr);
  delay(1000);

}
