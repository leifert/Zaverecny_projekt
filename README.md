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

 temperatureNode.setProperty("unit").send("c");                    // v2.0.0
 
 temperatureNode.setProperty("degrees").send(String(temperature)); // v2.0.0
 
HomieNode temperatureNode("temperature", "temperature");             // v1.5

Homie.setNodeProperty(temperatureNode, "degrees", String(temperature), true)   // v1.5



platformio

pio run

upload 

pio run -t upload

pio run -t uploadfs

pio device monitor -b 115200

esptool (na vymazani paměti na esp)

pip install esptool 

esptool.py erase_flash
           
           
mosquitto_sub -t '#' -v

mosquitto_sub -v -t #

mosquitto_pub -t homie/sdf1sd65f1(jmeno)/switch/on/set -m "true"

VsCode: https://code.visualstudio.com/

Mosquitto mqtt: https://mosquitto.org/download/

Knihovny: https://platformio.org/lib

Knihovna pro DHT senzor: ID 19: https://platformio.org/lib/show/19/DHT%20sensor%20library

Knihovna pro MQ-135: ID 2537:  https://platformio.org/lib/show/2537/TroykaMQ

Home Assistant: https://www.home-assistant.io

Návod na instalaci ve windows:

Nainstalovat python: https://www.python.org/downloads/

Do terminálu napsat: 

pip3 install homeassistant

hass --open-ui

http://localhost:8123

Konfigurační soubor(configuration.yaml) se nachází ve :C:\Users\[jmeno]\AppData\Roaming\.homeassistant

K otevírání doporučuji Notepad++. U jiných byl problém s uložením.

AppData je neviditelná složka, takže buď si zobrazte i nevidelné složky nebo do vyhledavání napište %appdata%

Ukázka pro dht sensors:

mqtt:

  #broker: Vaše IP stroje
  
  protocol: 3.1
  
  port: 1883
  
  discovery: true
  
  discovery_prefix: homeassistant
  
  sensor: 
    
  - platform: mqtt
  
    state_topic: 'homeassistant/sensor/temperature_celsius/'
    
    name: "Temperature Celsius"
    
    unit_of_measurement: '°C'   

  - platform: mqtt
    state_topic: 'homeassistant/sensor/humidity/'
    
    name: "Humidity"
    
    unit_of_measurement: '%'  

Datasheets: 
![alt text](https://github.com/leifert/Zaverecny_projekt/blob/master/esp8266.png)

![alt text](https://github.com/leifert/Zaverecny_projekt/blob/master/dht11.png)

![alt text](https://github.com/leifert/Zaverecny_projekt/blob/master/MQ2-Gas-sensor-Pinout.jpg)




