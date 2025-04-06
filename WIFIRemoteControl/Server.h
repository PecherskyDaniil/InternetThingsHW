#include <ESP8266WebServer.h>
#include "EEPROM.h"
ESP8266WebServer server(80);    



void handleRoot() {                         
  server.send(200, 
              "text/html", 
              "<html><head><script>function sendCommand(value) {var xhr = new XMLHttpRequest();xhr.open('POST', '/command', true);xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');xhr.send('value=' + value);}</script></head><body><div><button onmousedown=\"sendCommand('u')\" onmouseup=\"sendCommand('s')\">/\\</button></div><div><button onmousedown=\"sendCommand('l')\" onmouseup=\"sendCommand('s')\"><</button><button onmousedown=\"sendCommand('r')\" onmouseup=\"sendCommand('s')\">></button></div><div><button onmousedown=\"sendCommand('d')\" onmouseup=\"sendCommand('s')\">\\/</button></div></body></html>");
}
void handleCommand() {
  if (server.hasArg("value")) {
    String value = server.arg("value");
    Serial.println(value);
    server.sendHeader("Location", "/");
    server.send(303);
  } else {
    server.send(400, "text/plain", "400: Bad Request - no value provided");
  }
}


void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); 
}

void server_init() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/command", HTTP_POST, handleCommand);
  server.onNotFound(handleNotFound);

  server.begin();
  //Serial.println("HTTP server started");   
}
