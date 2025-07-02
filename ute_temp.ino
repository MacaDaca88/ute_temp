#include <WiFi.h>
#include <NTPClient.h>
#include <U8g2lib.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

const char* ssid = "NotYours";
const char* password = "PayMe4It";

const char* ssid2 = "Tip-jar";
const char* password2 = "PASSWORD1234LOL";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 43200, 10000);
unsigned long lastNtpEpoch = 0;

#define DHTPIN 4
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
float temp;
float humid;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);  // or specify pins if needed

#include "led.h"
#include "CLOCK.h"

void setup() {

  // Connect to wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // Wait for a few seconds to connect
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 5000) {
    delay(100);
  }

  if (WiFi.status() == WL_CONNECTED) {
  } else {
    WiFi.disconnect();
    WiFi.begin(ssid2, password2);

    // Wait again for backup connection
    startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 5000) {
      delay(100);
    }
  }
  // intiate SCREEN/DHT11
  u8g2.begin();
  dht.begin();
  timeClient.begin();
  timeClient.update();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(10, 30);
  u8g2.print("Booting");
  u8g2.sendBuffer();
  u8g2.print(".");
  u8g2.sendBuffer();
  u8g2.print(".");
  u8g2.sendBuffer();
  u8g2.print(".");
  u8g2.sendBuffer();
  ledStart();
}

void loop() {
  drawWifiSymbol(u8g2);
  clock();
  u8g2.setDrawColor(0);         // Set background color to black
  u8g2.drawBox(0, 0, 127, 63);  // Clear screen

  u8g2.setDrawColor(1);  // Set text color to white
  u8g2.setFont(u8g2_font_ncenB08_tr);

  sensors_event_t event;

  // Read temperature
  dht.temperature().getEvent(&event);
  temp = event.temperature;

  // Draw temperature
  u8g2.setCursor(5, 55);
  u8g2.print("T = ");
  u8g2.print(temp);

  // Read humidity
  dht.humidity().getEvent(&event);
  humid = event.relative_humidity;

  // Draw humidity
  u8g2.setCursor(70, 55);
  u8g2.print("H = ");
  u8g2.print(humid);


  u8g2.sendBuffer();

  //delay(1000);  // Wait 1 second before updating
}
