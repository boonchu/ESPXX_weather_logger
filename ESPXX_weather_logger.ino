/**The MIT License (MIT)

Copyright (c) 2015 by Daniel Eichhorn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

See more at http://blog.squix.ch
*/

#include <ESP8266WiFi.h>
#include <DHT.h>
#include "settings.h"
 
// Initialize the temperature/ humidity sensor
DHT dht(DHTPIN, DHTTYPE);

// Vcc (Voltage at the common collector) monitoring
ADC_MODE(ADC_VCC);
#define BATT_CRT 2.2 // critical battery voltage -> go sleep
float vcc = 0.0;

//// Wifi signal strength in dBm
int32_t rssi = 0;

void setup() {
	Serial.begin(115200);
	delay(10);
	
	vcc = ESP.getVcc()/1024.00f;
	Serial.print("Vcc: ");
	Serial.print(vcc);
	Serial.println(" Volts");
	
	if (vcc <= BATT_CRT) {
	  Serial.print("Vcc drop to critical level, enforce to sleep 5 minutes!");
	  deepSleep();
	}
	
	// We start by connecting to a WiFi network
	
	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);
	
	WiFi.begin(ssid, password);
	
	while (WiFi.status() != WL_CONNECTED) {
	  delay(500);
	  Serial.print(".");
	}
	
	if (!rssi){
	  /// WiFi RSSI
	  rssi = WiFi.RSSI();
	  Serial.print("Wifi signal strength index (Rssi): ");
	  Serial.print(rssi);
	  Serial.println(" dBm");
	} 
	
	Serial.println("");
	Serial.println("WiFi connected");  
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

void loop() {      
	Serial.print("connecting to ");
	Serial.println(host);
	
	// Use WiFiClient class to create TCP connections
	WiFiClient client;
	const int httpPort = 80;
	if (!client.connect(host, httpPort)) {
	  Serial.println("connection failed");
	  return;
	}
	
	// read values from the sensor
	float humidity = dht.readHumidity();
	float temperature = dht.readTemperature(!IS_METRIC);
	if (isnan(temperature) || isnan(humidity)) {
	  Serial.println("Failed to read from DHT");
	  delay(1);
	} else {
	  // We now create a URI for the request
	  String url = "/update?api_key=";
	  url += THINGSPEAK_API_KEY;
	  url += "&field1=";
	  url += String(temperature);
	  url += "&field2=";
	  url += String(humidity);
	  url += "&field3=";
	  url += String(rssi);
	  url += "&field4=";
	  url += String(vcc);      
	  url += "&field5=";
	  url += String(dewPointFast(temperature,humidity));
	  url += "&field6=";
	  url += String(FtoC(heatIndex(CtoF(temperature),humidity)));
	
	  Serial.print("Requesting URL: ");
	  Serial.println(url);
	
	  // This will send the request to the server
	  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
	             "Host: " + host + "\r\n" + 
	             "Connection: close\r\n\r\n");
	  delay(10);
	  while(!client.available()){
	    delay(100);
	    Serial.print(".");
	  }
	  // Read all the lines of the reply from server and print them to Serial
	  while(client.available()){
	    String line = client.readStringUntil('\r');
	    Serial.print(line);
	  }
	
	  Serial.println();
	  Serial.println("closing connection");
	  deepSleep();
	}
}

void deepSleep() {
	// Go back to sleep. If your sensor is battery powered you might
	// want to use deep sleep here
	// delay(1000 * UPDATE_INTERVAL_SECONDS);
	Serial.println("Going into deep sleep for 300 seconds");
	ESP.deepSleep(1000000 * UPDATE_INTERVAL_SECONDS, WAKE_RF_DEFAULT); // 300 seconds deep sleep
}

// https://github.com/RobTillaart/Arduino/blob/master/libraries/Temperature/temperature.h
//
// delta max = 0.6544 wrt dewPoint()
// 5x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
float dewPointFast(float celsius, float humidity)
{
	float a = 17.271;
	float b = 237.7;
	float temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
	float Td = (b * temp) / (a - temp);
	return Td;
}

float CtoF(float c) {
	return c * 1.8 + 32;
}

float FtoC(float f) {
	return (f - 32) * 0.55555;
}

float heatIndex(float celsius, float humidity)
{
    const float c1 = -42.379;
    const float c2 =  2.04901523;
    const float c3 = 10.14333127;
    const float c4 = -0.22475541;
    const float c5 = -0.00683783;
    const float c6 = -0.05481717;
    const float c7 =  0.00122874;
    const float c8 =  0.00085282;
    const float c9 = -0.00000199;

    float A = (( c5 * celsius) + c2) * celsius + c1;
    float B = (((c7 * celsius) + c4) * celsius + c3) *humidity;
    float C = (((c9 * celsius) + c8) * celsius + c6) *humidity *humidity;

    return A + B + C;
}
