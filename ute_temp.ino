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
  timeClient.update();
  u8g2.setDrawColor(0);  // Set background color to black
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
  int hours = timeClient.getHours();
  if (hours >= 24) {
    hours -= 24;
  }

  int minutes = timeClient.getMinutes();
  int seconds = timeClient.getSeconds();

  String period = "AM";
  if (hours >= 12) {
    period = "PM";
    if (hours > 12) hours -= 12;
  } else if (hours == 0) {
    hours = 12;
  }

  char timeBuffer[9];
  sprintf(timeBuffer, "%02d:%02d:%02d", hours, minutes, seconds);

  String dayOfWeek;
  int day = timeClient.getDay();
  switch (day) {
    case 0: dayOfWeek = "Sunday"; break;
    case 1: dayOfWeek = "Monday"; break;
    case 2: dayOfWeek = "Tuesday"; break;
    case 3: dayOfWeek = "Wednesday"; break;
    case 4: dayOfWeek = "Thursday"; break;
    case 5: dayOfWeek = "Friday"; break;
    case 6: dayOfWeek = "Saturday"; break;
  }
  time_t rawTime = timeClient.getEpochTime();
  struct tm* timeInfo = localtime(&rawTime);

  int date = timeInfo->tm_mday;
  int month = timeInfo->tm_mon;  // 0 = Jan, 3 = April, etc.

  String suffix = "th";
  if (date % 10 == 1 && date != 11) suffix = "st";
  else if (date % 10 == 2 && date != 12) suffix = "nd";
  else if (date % 10 == 3 && date != 13) suffix = "rd";

  const char* months[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };

  String fullDate = String(date) + suffix + " " + months[month];

  u8g2.setFont(u8g2_font_osr18_tf);

  u8g2.setCursor(3, 23);
  u8g2.print(timeBuffer);

  u8g2.setFont(u8g2_font_6x10_mf);
  u8g2.print(period);
  u8g2.setCursor(5, 40);
  u8g2.setFont(u8g2_font_timR10_tf);
  u8g2.print(dayOfWeek);
  u8g2.setFont(u8g2_font_timR10_tf);
  u8g2.setCursor(65, 40);
  u8g2.print(fullDate);
  u8g2.sendBuffer();

  //delay(1000);  // Wait 1 second before updating
}
