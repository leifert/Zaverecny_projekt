# Zaverecny_projekt

Měřič kvality ovzduší(vydýchanost)
Vydýchanost vzduchu se dá velmi dobře určit například pomocí měření koncentrace oxidu uhličitého, který lidé vydechují.
Existuje několik druhů senzorů typu MQ: MQ-2, MQ-3, MQ-4, MQ-5, MQ-6, MQ-7, MQ-135...

Detektory mq2 https://navody.arduino-shop.cz/navody-k-produktum/senzor-horlavych-plynu-mq-2.html  It is suitable for detecting H2, LPG, CH4, CO, Alcohol, Smoke or Propane.
4vodiče
+5V
AOUT
DOUT
GND
Cena 100Kč

Pro CO2 je nutné použít MQ135 https://navody.arduino-shop.cz/navody-k-produktum/senzor-plynu-mq-135.html

http://forum.mypower.cz/viewtopic.php?f=19&t=2253&sid=7c6d5585a668146bce83b2f60e9b03bb&start=180

Jak to bude fungovat...

Cílem bude sběr dat z čidel - co2, vlhkost, teplota do mqtt serveru (pokud možno s použitím protokolu mqtt ssl)
Použité prvky:esp8266 esp-e12,DHT22,MQ-135,
Použité technologie: homie framework
vsCode, platformio

Zprovoznění platfomia ve Vscodu
Poznámky:
sudo usermod -a -G dialout student (Povolení USB portu, pro přenos dat)

Pozor existuje několik verzí Homie!! My používáme v2.0.0 pak je ale ještě verze 1.5 a to má odlišný syntax! Pokud se vám objeví taková hláška: error: 'class HomieInternals::HomieClass' has no member named 'setNodeProperty' Tak máte verzi 2.0.0 ale používate syntax verze 1.5 !!
Tady malá ukázka: 
 temperatureNode.setProperty("unit").setRetained(true).send("C"); // v2.0.0
 Homie.setNodeProperty(temperatureNode, "unit", "c", true);       // v1.5



platformio

pio run

upload 

pio run -t upload

pio run -t uploadfs

pio device monitor

esptool (na vymazani paměti na esp)

pip install esptool 

esptool.py erase_flash
           
           
mosquitto_sub -t '#' -v

mosquitto_pub -t homie/sdf1sd65f1(jmeno)/switch/on/set -m "true"

Knihovny: https://platformio.org/lib

Knihovna pro DHT senzor: ID 19: https://platformio.org/lib/show/19/DHT%20sensor%20library

Knihovna pro MQ-135: ID 2537:  https://platformio.org/lib/show/2537/TroykaMQ


Datasheets: 
![alt text](https://github.com/leifert/Zaverecny_projekt/blob/master/esp8266.png)

![alt text](https://github.com/leifert/Zaverecny_projekt/blob/master/dht11.png)

![alt text](https://github.com/leifert/Zaverecny_projekt/blob/master/MQ2-Gas-sensor-Pinout.jpg)




