#### Weather Logger (DHT11 sensor) ####


This project work is part two that resume from previous one. I posted the first project in github. Note to understand how to build out the weather station first before continues. This unit sends data to Thingspeak API using registered "allow-to-write-data" authentication key. Two available columns are Temperature and Humidty. These two records is being used by ESP 12E weather station unit. If you are interested in, you can click to this link for instructions to build the ESP 12E weather station unit, https://github.com/boonchu/ESPXX_weather_station

* Hardware:
	- ESP8266 12E
	- DHT11/DHT22
	- Power source such as batteries (3.3 volts)

* Schematic:

```
Consult pin layouts from manufacturers. Table below is *ONLY* sample pin that use for my unit.
I have not responsible for any mistake.
```

DHT11 sensor  | ESP8266 12E
------------- | -------------
pin 1 data | pin D6 - GPIO
pin 2 vcc  | pin 3v3
pin 3 GND  | pin GND

Batter(ies) unit | ESP8266 12E
---------------- | ------------
wire Vcc | pin Vin
wire GND | pin GND

```
Note to add special wire from 12E unit itself from RST pin to D0 pin to support deep sleep feature.
```

* Preparation:
	- review Schematic 

