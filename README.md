#### Weather Logger (DHT11 sensor) ####

Video link: https://youtu.be/nUpPW-ve5mI

![weather logger gif](https://github.com/boonchu/ESPXX_weather_logger/blob/master/espxx_weather_logger.gif)

This project work is part two that resume from previous one. I posted the first project in github. Its important to understand how to build out the weather station before continues. This project describe only how unit sends data to Thingspeak API using registered "allow-to-write-data" authentication key. The project unit is like the additional feature to fullfill station unit. Two available columns are Temperature and Humidty. These two records is being used by ESP 12E weather station unit. If you are interested in, you can click to this link for instructions to build the ESP 12E weather station unit, https://github.com/boonchu/ESPXX_weather_station

Statistic data gathers from DHT11 remote sensor to report Outdoor temperature and humidty around my house. The data is available in thingspeak channel web. You can check this out from my channel, https://thingspeak.com/channels/409552

* Features:
	- Connects unit to ThingSpeak IoT to deposit data
	- Deep sleep unit when no longer use the unit until next interval

* Hardware:
	- ESP8266 12E
	- DHT11/DHT22 (https://www.itead.cc/wiki/DHT11_Humidity_Temperature_Sensor_Brick)
	- Power source such as batteries (3.3 volts)

Parameters | Accuracy 
-------- | ---------
Humidity at 25C | +/-4 %RH
Humidity (0-50C) | +/-5 %RH
Humidity range at 25C | 20-95 %RH
Temp | +/-1 to +/-2 C
Temp range | 0-50 C

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

