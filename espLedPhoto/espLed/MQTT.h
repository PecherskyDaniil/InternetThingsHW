#include <PubSubClient.h>

PubSubClient mqtt_cli(wifiClient);
int maxv=0;
int minv=0;
void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    int val=0;
    for (int i = 0; i < length; i++) {
      val=val*10+((int)payload[i] - (int)'0');
    }
    Serial.println(val);
    if (strcmp(topic,topicmin)==0){
      minv=val;
    }else if (strcmp(topic,topicmax)==0){
      maxv=val;
    }else if (strcmp(topic,topicval)==0){
      if (val>(minv + maxv) / 2){
        digitalWrite(led,LOW);
      }else{
        digitalWrite(led,HIGH);
      }
    }
    Serial.println();
    Serial.println("-----------------------");
}

void MQTT_init(){

  mqtt_cli.setServer(mqtt_broker, mqtt_port);
  mqtt_cli.setCallback(callback);
  while (!mqtt_cli.connected()) {
      String client_id = "esp8266-" + String(WiFi.macAddress());
      Serial.print("The client " + client_id);
      Serial.println(" connects to the public mqtt broker\n");
      if (mqtt_cli.connect(client_id.c_str())){
          Serial.println("MQTT Connected");
      } else {
          Serial.print("failed with state ");
          Serial.println(mqtt_cli.state());
          delay(2000);
      }
  }  
}
