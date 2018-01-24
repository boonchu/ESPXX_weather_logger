#### Weather Logger (DHT11 sensor) ####

![weather logger gif](https://github.com/boonchu/ESPXX_weather_logger/blob/master/espxx_weather_logger.gif)

This project work is part two that resume from previous one. I posted the first project in github. Note to understand how to build out the weather station first before continues. This project describe only how unit sends data to Thingspeak API using registered "allow-to-write-data" authentication key. Two available columns are Temperature and Humidty. These two records is being used by ESP 12E weather station unit. If you are interested in, you can click to this link for instructions to build the ESP 12E weather station unit, https://github.com/boonchu/ESPXX_weather_station

Static gathers from sensor to report Outdoor temperature and humidty around my house. The data is available in thingspeak channel web. You can check this out from my channel, https://thingspeak.com/channels/409552

* Hardware:
	- ESP8266 12E
	- DHT11/DHT22
	- Power source such as batteries (3.3 volts)

* Schematic:

![weather logger_schematic](https://github.com/boonchu/ESPXX_weather_logger/blob/master/weather_logger.png)

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

      Serial.println("Going into deep sleep for 50 seconds");
      ESP.deepSleep(1000000 * UPDATE_INTERVAL_SECONDS, WAKE_RF_DEFAULT); // 50 seconds deep sleep
```

* Preparation:
	- review Schematic 

