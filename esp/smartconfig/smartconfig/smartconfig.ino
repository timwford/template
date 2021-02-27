#include "WiFi.h"

#define LED_BUILTIN 2

class WifiManager {
  public:
    bool connect() {
      if (WiFi.waitForConnectResult() == WL_CONNECTED) {
        delay(500);
        return true;
      }

      return false;
    }

    void startSmartConfig() {
      WiFi.beginSmartConfig();
      Serial.println("Waiting for SmartConfig.");
      while (!WiFi.smartConfigDone()) {
        delay(250);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(250);
        digitalWrite(LED_BUILTIN, LOW);
      }

      while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
      }

      char ssid[WiFi.psk().length()];
      strcpy(ssid, WiFi.psk().c_str());
      char pass[WiFi.psk().length()];
      strcpy(pass, WiFi.psk().c_str());
      
      WiFi.disconnect();
      digitalWrite(LED_BUILTIN, LOW);
      WiFi.stopSmartConfig();

      WiFi.begin(ssid, pass);
      while(WiFi.status() != WL_CONNECTED) {
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
      }
    }
};

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  WifiManager wifiManager;

  if (wifiManager.connect()) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    wifiManager.startSmartConfig();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
