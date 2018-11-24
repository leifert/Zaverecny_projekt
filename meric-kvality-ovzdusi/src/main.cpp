#include <Homie.h>
#include "DHT.h"

#define DHTPIN 5
#define DHTTYP DHT11
#define INTERVAL 5 //sekundy

unsigned long lastSent = 0;

DHT dht(DHTPIN, DHTTYP);

HomieNode teplotaNode("teplota", "teplota");
HomieNode vlhkostNode("vlhkost", "vlhkost");

void setupHandler() {
  teplotaNode.setProperty("unit").send("C");
  vlhkostNode.setProperty("unit").send("%");

}

void loopHandler() {
   if (millis() - lastSent >= INTERVAL * 1000UL || lastSent == 0) {
     float teplota = dht.readTemperature();
     float vlhkost = dht.readHumidity();
     if (isnan(teplota) || isnan(vlhkost)) {
      Homie.getLogger() << F("Chyba čtení ze snímače DHT!");
    } else {
      Homie.getLogger() << F("Teplota: ") << teplota << " °C" << endl;
      Homie.getLogger() << F("Vlhkost: ") << vlhkost << " %" << endl;
      teplotaNode.setProperty("stupne").send(String(teplota));
      vlhkostNode.setProperty("procenta").send(String(vlhkost));
    }
     lastSent = millis();
  }
}

void setup() {
  Serial.begin(115200);

  Homie_setFirmware("homie-meric", "1.0.0");
  
  Homie.setSetupFunction(setupHandler);
  Homie.setLoopFunction(loopHandler);
  
  teplotaNode.advertise("unit");
  teplotaNode.advertise("degrees");
  vlhkostNode.advertise("unit");
  vlhkostNode.advertise("percent");

  Homie.setup();
}

void loop() {
  Homie.loop();
}