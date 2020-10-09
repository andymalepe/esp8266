#include <Arduino.h>
#include <ESP8266WiFi.h>

IPAddress localIP(192,168,4,2);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.softAPConfig(localIP, gateway, subnet);
  WiFi.begin("monair","aaaaaaaaaaa");
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
  }
}

void loop(){
  // Serial.printf("Stations conn = %d\n", WiFi.softAPgetStationNum());
  digitalWrite(LED_BUILTIN, HIGH);

  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
