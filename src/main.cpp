#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress localIP(192,168,4,2);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);
void index();
void error();

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.softAPConfig(localIP, gateway, subnet);
  WiFi.begin("monair","aaaaaaaaaaa");
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
  }

  server.on("/", HTTP_GET, index);
}

void loop(){
  // Serial.printf("Stations conn = %d\n", WiFi.softAPgetStationNum());
  digitalWrite(LED_BUILTIN, HIGH);

  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
void index(){
  server.send(200, "text/html", "<form action=\"/connect\" method=\"POST\"><input type=\"text\" name=\"ssid\" placeholder=\"Network SSID\"><input type=\"password\" name=\"password\" placeholder=\"Password\"><input type=\"submit\" value=\"Connect to AP\"></form>");
}
void error(){
  server.send(404, "text/plain", "Error 404");
}
