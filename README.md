# ute_temp


ESP32-C3 Car Clock & Environment Display
This project is a custom-built digital clock and environment monitoring system designed for a 1990 Mitsubishi L200 Ute, which lacks a built-in clock or ambient indicators. The system utilizes an ESP32-C3 board, a 128x64 OLED display, and a DHT11 temperature/humidity sensor, and is powered via USB in the vehicle.

📦 Features
Accurate Clock via NTP Sync
The ESP32-C3 connects to a mobile hotspot and synchronizes the real-time clock using NTP servers, ensuring time is always accurate even after power loss.

Temperature & Humidity Monitoring
A DHT11 sensor reads the cabin’s temperature and humidity, displayed alongside the time.

OLED Display Interface
A 128x64 OLED screen shows the current time, temperature, and humidity in a clear, readable format designed for quick glancing while driving.

LED Strip Lighting Control
A connected RGB LED strip can be cycled through multiple colors (starting with white) using Button 1. Perfect for ambient lighting or night-time driving aesthetics.

Interactive Menu System
Button 2 opens a menu interface. One of the options allows the user to fetch and display real-time weather information via Wi-Fi and an online API.

Wi-Fi via Mobile Hotspot
Designed to work with your phone’s hotspot, enabling all online functionality including:

NTP time updates

Online weather fetching

🛠️ Hardware Components
ESP32-C3 Dev Board

128x64 OLED Display (I2C)

DHT11 Temperature & Humidity Sensor

WS2812B (or similar) RGB LED Strip

Two tactile buttons for user input

Power source: vehicle USB or 12V to 5V regulator

🔘 Button Functions
Button 1: Cycle LED colors (white, red, green, blue, etc.)

Button 2: Open menu

Menu includes options like weather display and future expandability

💡 Use Case
This system is ideal for older vehicles with no built-in digital display, providing modern functionality like internet-synced time, comfort metrics, and ambient lighting—enhanced by the flexibility of Wi-Fi features enabled through your smartphone hotspot.