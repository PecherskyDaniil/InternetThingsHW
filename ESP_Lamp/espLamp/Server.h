#include <ESP8266WebServer.h>
#include "EEPROM.h"
ESP8266WebServer server(80);    



void handleRoot() {                         
  server.send(200, 
              "text/html", 
              "<form action=\"/login\" method=\"POST\"><input type=\"text\" name=\"wifi_name\"/><br/><input type=\"password\" name=\"wifi_password\"/><br/><input style='font-size=50px' type=\"submit\"></form>");
}

void handleLED() {                          
  digitalWrite(led, !digitalRead(led));
  server.sendHeader("Location","/"); // redirection to keep button on the screen
  server.send(303);
}
void handleLogin() {                          
  String message = "Number of args received:";
  message += server.args();            //Get number of parameters
  message += "\n";                            //Add a new line
  
  for (int i = 0; i < server.args(); i++) {
    message += "Arg nº" + (String)i + " –> ";   //Include the current iteration value
    message += server.argName(i) + ": ";     //Get the name of the parameter
    message += server.arg(i) + "\n";              //Get the value of the parameter

  } 
  EEPROM.begin(100);
  ssidCLI=server.arg("wifi_name");
  Serial.println("Writed "+ssidCLI);
  passwordCLI=server.arg("wifi_password");
  writeStringToEEPROM(0,ssidCLI);
  writeStringToEEPROM(ssidCLI.length()+1,passwordCLI);
  EEPROM.commit();
  server.send(200, "text/plain", message);       //Response to the HTTP request
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); 
}

void server_init() {
  server.on("/", HTTP_GET, handleRoot);     
  server.on("/login", handleLogin);
  server.onNotFound(handleNotFound);        

  server.begin();                          
  Serial.println("HTTP server started");    
}