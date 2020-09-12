#include <bora.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

const char* SSID = "SSID";
const char* PASSWORD = "PASSWORD";
float potenciometro;
String readExemplo;

WiFiClient wifi;
BORA bora_device(wifi);

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
  readExemplo = bora_device.virtualRead("exemplo");
}
