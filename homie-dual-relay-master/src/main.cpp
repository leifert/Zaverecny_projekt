#include <Homie.h>
#include "DHT.h"

#define DHTPIN 5
#define DHTTYPE DHT11
#define INTERVAL 60

unsigned long lastSent = 0;

DHT dht(DHTPIN, DHTTYPE);

HomieNode temperatureNode("temperature", "temperature");
HomieNode humidityNode("humidity", "humidity");

void setupHandler() {
  temperatureNode.setProperty("unit").setRetained(true).send("F");
  humidityNode.setProperty("unit").setRetained(true).send("percent");

}

void loopHandler() {
   if (millis() - lastSent >= INTERVAL * 1000UL || lastSent == 0) {
     float humidity = dht.readHumidity();
     float temperature = dht.readTemperature(true);
     temperatureNode.setProperty("F").send(String(temperature));
     humidityNode.setProperty("percent").send(String(humidity));
     lastSent = millis();
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Homie_setFirmware("homie-dht", "1.0.0");
  
  Homie.setSetupFunction(setupHandler);
  Homie.setLoopFunction(loopHandler);
  
  temperatureNode.advertise("unit");
  temperatureNode.advertise("temperature");
  humidityNode.advertise("unit");
  humidityNode.advertise("percent");

  Homie.setup();
}

void loop() {
  Homie.loop();
}