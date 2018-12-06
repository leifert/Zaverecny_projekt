#include <Homie.h>
#include <DHT.h>
#include <TroykaMQ.h>


#define MQ135PIN A0
#define DHTPIN 5
#define DHTTYP DHT11
#define INTERVAL 2 //sekundy

unsigned long lastSent = 0;

DHT dht(DHTPIN, DHTTYP);
MQ135 mq135(MQ135PIN);


HomieNode teplotaNode("teplota", "teplota");
HomieNode vlhkostNode("vlhkost", "vlhkost");
HomieNode co2Node("CO2", "CO2");
HomieNode ratioNode("ratio", "ratio");

void setupHandler() {
  teplotaNode.setProperty("unit").send("C");
  vlhkostNode.setProperty("unit").send("%");
  co2Node.setProperty("unit").send("PPM");
  ratioNode.setProperty("unit").send("ratio");
  mq135.calibrate();
  mq135.getRo();
}

void loopHandler() {
    if (millis() - lastSent >= INTERVAL * 1000UL || lastSent == 0) {
      float teplota = dht.readTemperature();
      float vlhkost = dht.readHumidity();

      float ratio = mq135.readRatio();
      float co2 = mq135.readCO2();
      teplotaNode.setProperty("celsia").send(String(teplota));
      vlhkostNode.setProperty("procent").send(String(vlhkost));
      ratioNode.setProperty("ratio").send(String(ratio));
      co2Node.setProperty("PPM").send(String(co2));
        lastSent = millis();
  }
}

void setup() {
  Serial.begin(115200);

  Homie_setFirmware("homie-meric", "1.0.0");
  
  Homie.setSetupFunction(setupHandler);
  Homie.setLoopFunction(loopHandler);
  
  Homie.setup();
}

void loop() {
  Homie.loop();
}