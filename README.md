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



