#include "WiFi.h"
#include <HTTPClient.h>

const char* ssid = "greenhouse";
const char* password =  "greenhouse";

const char* serverName = "http://209.159.204.189:6381/ingest";

#define LED_BUILTIN 2

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  digitalWrite(LED_BUILTIN, LOW);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  digitalWrite(LED_BUILTIN, HIGH);
}


void loop() {
  delay(2000);
  HTTPClient http;

  http.begin(serverName);
  
  http.addHeader("Content-Type", "application/json");
  http.addHeader("accept", "application/json");
  
  String val = "TS.ADD bin:3:test * 8.1";
  String httpRequestData = "{\"msg\":\"" + val + "\"}";

  Serial.println(httpRequestData);
  
  int httpResponseCode = http.POST(httpRequestData);
  
  Serial.println(httpResponseCode);

  delay(30000);
}
