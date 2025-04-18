#include <PubSubClient.h>

PubSubClient mqtt_cli(wifiClient);

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    //for (int i = 0; i < length; i++) {
      //Serial.print((char) payload[i]);
    //}
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
