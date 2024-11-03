#include "Config.h"
#include "WIFI.h"
#include "Server.h"
#include "MQTT.h"


bool constat=false;
void setup(void){
  Serial.begin(115200);
  EEPROM.begin(100);
  pinMode(led, OUTPUT);
  WIFI_init(true);
  server_init();
  ssidCLI=readStringFromEEPROM(0);
  passwordCLI=readStringFromEEPROM(ssidCLI.length()+1);
  Serial.println("eeprom_id: "+ssidCLI);
  Serial.println("eeprom_pass: "+passwordCLI);
  changeMode("APmode");
}

void loop(void){
  Indicator(indstate);
  if (ssidCLI.length()!=0 && passwordCLI.length()!=0 && !constat){
    if (WIFI_init(false)){
      changeMode("CLImode");
      MQTT_init("/pech/esplamp/stream");
      mqtt_cli.subscribe("/pech/esplamp/1",0);
      constat=true;
    }else{
      changeMode("APmode");
      ssidCLI = "";
      passwordCLI = "";
      WIFI_init(true);
      server_init();
    }
  }else{
    server.handleClient();
  }
  if (WiFi.status() != WL_CONNECTED && constat){
      changeMode("APmode");
      ledstate=0;
      ssidCLI = "";
      passwordCLI = "";
      WIFI_init(true);
      server_init();
      constat=false;
  }
  if (constat){
    //mqtt_cli.publish("/pech/esplamp/hello","hello");
    //Serial.println("hello");
    mqtt_cli.loop();
  }
  //if (topicval.length()==0){// || topicmin.length()==0 || topicmax.length()==0){
  //  get_topics();
  //}else{
  //  if (constat){
  //    mqtt_cli.loop();
  //  }else{
  //    start_serv();
  //  }
  //}
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