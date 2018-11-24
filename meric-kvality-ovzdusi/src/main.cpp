#include <Homie.h>
#include "DHT.h"
#include <MQ135.h>

#define MQ135PIN A0
#define DHTPIN 5
#define DHTTYP DHT11
#define INTERVAL 5 //sekundy

unsigned long lastSent = 0;

DHT dht(DHTPIN, DHTTYP);
MQ135 plynovySensor = MQ135(MQ135PIN);

HomieNode teplotaNode("teplota", "teplota");
HomieNode vlhkostNode("vlhkost", "vlhkost");
HomieNode co2Node("CO2", "CO2");
HomieNode rzeroNode("rzero", "rzero");

void setupHandler() {
  teplotaNode.setProperty("unit").send("C");
  vlhkostNode.setProperty("unit").send("%");
  co2Node.setProperty("unit").send("PPM");
  rzeroNode.setProperty("unit").send("rzero");
}

void loopHandler() {
    if (millis() - lastSent >= INTERVAL * 1000UL || lastSent == 0) {
      float teplota = dht.readTemperature();
      float vlhkost = dht.readHumidity();
      float rzero = plynovySensor.getRZero();
      float ppm = plynovySensor.getPPM();
      teplotaNode.setProperty("stupne").send(String(teplota));
      vlhkostNode.setProperty("procenta").send(String(vlhkost));
      rzeroNode.setProperty("rzero").send(String(rzero));
      co2Node.setProperty("PPM").send(String(ppm));
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