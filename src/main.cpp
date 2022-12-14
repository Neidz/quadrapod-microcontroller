#include <Arduino.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "secrets.h"

const int rx = 3;
const int tx = 1;
const int led = 2;

AsyncWebServer server(80);

void flash()
{
  digitalWrite(led, HIGH);
  delay(20);
  digitalWrite(led, LOW);
  delay(20);
  digitalWrite(led, HIGH);
  delay(20);
  digitalWrite(led, LOW);
}

void setup()
{
  Serial.begin(9600, SERIAL_8N1, rx, tx);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  pinMode(led, OUTPUT);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
      AsyncWebParameter* p = request->getParam(0);
      String value = p->value();
      std::replace(value.begin(), value.end(), '_', '#');

      flash();

      Serial.println(value + "\r\n");

      request->send(200, "text/plain", "message received"); });

  server.begin();
}

void loop()
{
}