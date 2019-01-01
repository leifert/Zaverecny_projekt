#include <Homie.h> //připojení potřebných knihoven
#include <DHT.h>
#include <TroykaMQ.h>
#define MQ135PIN A0 //nastavení propojovácích pinů
#define DHTPIN 5
#define DHTTYP DHT11 //určení o jaký teplotní senzor se jedná
#define INTERVAL 2 //po kolika sekundách má data posílat na MQTT server
unsigned long lastSent = 0;

DHT dht(DHTPIN, DHTTYP); //inicializace senzorů z knihoven
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
  mq135.calibrate(); //kalibrace mq135 senzoru
  mq135.getRo(); //ziskání odporu mq135 senzoru, pro výpočet CO2 ppm


}

void loopHandler() {
    if (millis() - lastSent >= INTERVAL * 1000UL || lastSent == 0) { //interval pro odesílání dat
      float teplota = dht.readTemperature(); //načtení teploty do proměnné
      float vlhkost = dht.readHumidity(); //načtení vlhkosti do proměnné
      float ratio = mq135.readRatio();
      float co2 = mq135.readCO2(); //načtení koncentrace CO2 do proměnné

if (co2 >= 350 && co2 <= 1000) {
    digitalWrite(12, HIGH);  
    digitalWrite(14, LOW);
    digitalWrite(12, LOW);
  }
  else if (co2 >= 1001 && co2 <= 1500) {
    digitalWrite(12, LOW);  
    digitalWrite(14, HIGH);
    digitalWrite(4, LOW);
  }
  else if (co2 > 1500) {
    digitalWrite(12, LOW);  
    digitalWrite(14, LOW);  
    digitalWrite(4, HIGH);
  }
      teplotaNode.setProperty("celsia").send(String(teplota)); //odeslání prměnných na MQTT server
      vlhkostNode.setProperty("procent").send(String(vlhkost));
      ratioNode.setProperty("ratio").send(String(ratio));
      co2Node.setProperty("PPM").send(String(co2));
        lastSent = millis();
  }
    
  
}

void setup() {
  Serial.begin(115200); //inicializace komunikace po seriové lince rychlostí 115200 baudů
  Homie_setFirmware("homie-meric", "1.0.0");
  pinMode(4, OUTPUT); //červená LED
  pinMode(14, OUTPUT); //žlutá LED
  pinMode(12, OUTPUT); //zelená LED

  Homie.setSetupFunction(setupHandler);
  Homie.setLoopFunction(loopHandler);

  Homie.setup();
}

void loop() {
  Homie.loop();
}