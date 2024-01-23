# ESP8266 DHT22 Thinger.io IoT Monitor

This Arduino code is designed for use with ESP8266 and DHT22 sensor to monitor temperature and humidity. It integrates with Thinger.io for remote monitoring and displays the data on an LCD screen. The code was developed by Michail Gouvalaris and Michail Kagiaogloy for academic use at the Dept. of Informatics and Telecommunication, University of Ioannina.

## Features
- Reads temperature and humidity from a DHT22 sensor.
- Calculates the average temperature over time.
- Integrates with Thinger.io for IoT monitoring.
- Displays data on an LCD screen.
- Added D4 output LED for additional functionality.

## Hardware Requirements
- ESP8266
- DHT22 sensor
- LCD screen (I2C)
- LED on D4 pin

## Software Requirements
- Arduino IDE 2.2.1
- Thinger.io account
- Thinger.io Arduino library
- DHT sensor library
- LiquidCrystal_I2C library

## Setup
1. Install the required libraries in the Arduino IDE.
2. Configure your Thinger.io account and obtain the necessary credentials.
3. Update the `arduino_secrets.h` file with your WiFi credentials and Thinger.io credentials.
4. Connect the hardware components as per the specified pins.
5. Upload the code to your ESP8266 board using the Arduino IDE.

## Configuration
- Adjust the `DHTPIN` and `DHTTYPE` variables for your specific setup.
- Modify the `numReadings` variable to change the number of readings to average over time.

## Usage
- The code continuously reads temperature and humidity, calculates the average, and sends data to Thinger.io.
- The LCD screen displays real-time humidity and temperature readings.
- The D4 pin controls an LED for additional functionality.

## Notes
- This code was last updated on January 23rd, 2024.
- For more details, refer to the [Thinger.io documentation](http://docs.thinger.io/arduino/).

Feel free to use, modify, and contribute to this project. If you encounter any issues or have suggestions for improvements, please open an issue or pull request.

**Disclaimer:** This code is intended for academic use and may require adjustments for different environments or setups. Use at your own risk.
