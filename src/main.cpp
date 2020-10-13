#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <FS.h>

IPAddress localIP(192,168,4,2);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);
void indexPage();
void error();
void configureWiFi();

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  //configureWiFi();
  if (MDNS.begin("esp8266")) {
    Serial.println("mDNS started");
  }
  //server.on("/", indexPage);
  //server.begin();

  if (SPIFFS.begin()) {
    Serial.println("FS mounted");
  }else{
    Serial.println("Error mounting FS");
    return;
  }

  File file = SPIFFS.open("data.txt", "w");
  if (!file) {
    Serial.println("File opened successfully");
  }
  int byt = file.print("testing Spiffs");
  if (byt > 0) {
    Serial.println("Wrote file");
  }else{
    Serial.println("Failed");
  }
}

void loop(){
  // Serial.printf("Stations conn = %d\n", WiFi.softAPgetStationNum());
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Howdy");
  //server.handleClient();
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
void configureWiFi(){
  WiFi.softAPConfig(localIP, gateway, subnet);
  WiFi.softAP("monair", "password");
  // while (WiFi.status() != WL_CONNECTED){
  //   delay(1000);
  // }
}
void indexPage(){
  server.send(200, "text/plain", "Ola tudo bem");
}
// void indexPage(){
//   server.send(200, "text/html", "<form action=\"/connect\" method=\"POST\"><input type=\"text\" name=\"ssid\" placeholder=\"Network SSID\"><input type=\"password\" name=\"password\" placeholder=\"Password\"><input type=\"submit\" value=\"Connect to AP\"></form>");
// }
void error(){
  server.send(404, "text/plain", "Error 404");
}
