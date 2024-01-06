/*
This code was designed by Michail Gouvalaris & Michail Kagiaogloy on January 06th 2024.
It is intended for academic use at the Dept. of Informatics and Telecommunication
of University of Ioannina.
*/
/*
This code was designed and compiled at Arduino IDE 2.2.1
It was designed for use with ESP8266
*/
/*
This Arduino code reads temperature and humidity data from a DHT22 sensor, calculates the average temperature over time, and integrates with Thinger.io for IoT monitoring. 
The data is displayed on an LCD screen and transmitted to Thinger.io for remote monitoring.
*/

#define THINGER_SERIAL_DEBUG

#include <ThingerESP8266.h>
#include "arduino_secrets.h"
#include "DHT.h"
#include <LiquidCrystal_I2C.h>

//dht Config
#define DHTPIN D3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

const int numReadings = 60; // Number of readings to average over (1 reading per second)
float temperatureReadings[numReadings];
int readingIndex = 0;

void setup()
{
  // open serial for monitoring
  Serial.begin(115200);
  Serial.begin(9600);
  // set builtin led as output
  pinMode(LED_BUILTIN, OUTPUT);
  dht.begin();
  // add WiFi credentials
  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_BUILTIN);

  // resource output example (i.e. reading a sensor value)
  thing["dht22"] >> [](pson &out) {
    out["humidity"] = dht.readHumidity();
    out["celsius"] = dht.readTemperature();
    out["avg"] = getAverageTemperature();
  };

  // more details at http://docs.thinger.io/arduino/
}

void loop()
{
  thing.handle();
  delay(1000); // Delay for 1 second

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Store the temperature reading in the array
  temperatureReadings[readingIndex] = t;
  readingIndex = (readingIndex + 1) % numReadings;

  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(F("Humidity: "));
  lcd.print(h);
  lcd.setCursor(0, 1);
  lcd.print(F("Temp.: "));
  lcd.print(t);
}

float getAverageTemperature()
{
  float total = 0;
  for (int i = 0; i < numReadings; i++)
  {
    total += temperatureReadings[i];
  }
  return total / numReadings;
}
