#include <ESP8266WiFi.h>
#include <restclient.h>
#include <bora.h>
#include <ArduinoJson.h>

const char* SSID = "Paulo 401";
const char* PASSWORD = "pcdrpv25";
int potenciometro;
String readExemplo;
String led;

WiFiClient wifi;
BORA bora_device(wifi);
restclient boraServer("server.bora-iot.com", 80);

void setup() {
  Serial.begin(9600);
  connectWifi();

  bora_device.begin("580a95c4f2debd3c1f3cc");
}

void connectWifi() {
  if (WiFi.status() == WL_CONNECTED)
    return;

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Wifi Connected: ");
  Serial.println(SSID);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  connectWifi();

  potenciometro = bora_device.analogRead(A0, "potenciometro");
  Serial.print("Potenciometro ");
  Serial.println(potenciometro);
  
  readExemplo = bora_device.virtualRead("exemplo");
  Serial.print("Exemplo ");
  Serial.println(readExemplo);

  led = bora_device.virtualRead("led");
  Serial.print("Led ");
  Serial.println(led);

  delay(500);
  
  bora_device.loop();
}
