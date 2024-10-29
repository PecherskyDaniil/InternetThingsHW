#include "Config.h"
#include "WIFI.h"
#include "Server.h"
#include "MQTT.h"

bool constat=false;
void setup(void){
  Serial.begin(115200);
  pinMode(led, OUTPUT);
}

void loop(void){
  //server.handleClient();
  if (topicval.length()==0){// || topicmin.length()==0 || topicmax.length()==0){
    get_topics();
  }else{
    if (constat){
      mqtt_cli.loop();
    }else{
      start_serv();
    }
  }
}
void start_serv(){
  WIFI_init(false);
  Serial.println("lol");
  MQTT_init(topicval);
  mqtt_cli.subscribe(topicval.c_str(),0);
  //mqtt_cli.subscribe(topicmin.c_str());
  //mqtt_cli.subscribe(topicmax.c_str());
  constat=true;
}
void get_topics(){
  if (topicval.length()==0){
    Serial.println("Input topic for commands:");
  }//else if (topicmin.length()==0){
  //  Serial.println("Input topic for min values:");
  //}else if (topicmax.length()==0){
  //  Serial.println("Input topic for max values:");
  //}
  if(Serial.available()>0){
    String top = Serial.readString();
    Serial.println(top);
    if (topicval.length()==0 ){
      topicval=top;
    }//else if (topicmin.length()==0 ){
    //  topicmin=top;
    //}else if (topicmax.length()==0 ){
    //  topicmax=top;
    //}
  }
}