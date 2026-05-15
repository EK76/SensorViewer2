# Sensor Data Viewer.

The goal with this project was to display temperature and humitidy data to a oled display and transfer same data over mtqq protocol
to an another device. It was accomplished with help of Arduino Uno R4 Wifi board and DHT22 sensor. It also done possible to turn off mtqq protocol transsmission
with help of button. A rgb led lights up green coloe when mtqq protocol transsmission is turned on, otherwise it the color is red. In my case I uses the ST7735S model as my 
oled display. You can find more info about Arduino IDE from this link. https://www.arduino.cc/en/software.

### MQTT (Message Queuing Telemetry Transport)
It is a lightweight, publish-subscribe network protocol designed for machine-to-machine (M2M) communication and the Internet of Things (IoT). It is ideal for low-bandwidth, high-latency, 
or unreliable networks, making it the standard for connecting remote devices, sensors, and mobile applications with minimal power consumption.
More info about **[MQTT](https://en.wikipedia.org/wiki/MQTT)**-

### This project consist of

Arduino Uno R4 Wifi (in my case) or any other Arduino board with Wifi feature of your choosing.
- 1 psc ST7735S oled display 
- 1 psc DHT22 sensor
- 1 pcs push button
- 1 psc RGB led (indicating status of mtqq protocol transsmission).
- 2 pcs 330 Ohm resistors that are connected to rgb led.
- Jump wires

<img width="348" height="295" alt="dht22" src="https://github.com/user-attachments/assets/d3ca62ba-9182-493c-a95a-1ab8c3f5866c" />

##### Sensor DHT22 pinout.

<img width="575" height="213" alt="oled2" src="https://github.com/user-attachments/assets/882acfb6-e734-4784-a6bb-8b93a47490d0" />

##### Sensor ST7735S oled display pinout.

## Schematics
<img width="493" height="337" alt="arduino" src="https://github.com/user-attachments/assets/82cf334d-5a39-40c5-a373-8dc09ceaac59" />

Rgb led two pins are connected to the pins 6 and 7.
Push button is connected to pin 3 (workings as an interrupt).
DHT22 sensor is connected to pin 2, 3,3V and GND. <br /><br />
#### Oled display ST7735S connection
- Pin RST -> pin 8.
- Pin DC -> pin 9.
- Pin RST -> pin 8.
- Pin LED -> pin 3,3V or pin 5V.
- Pin VCC -> pin 5V.
- Pin GND -> pin GND.
  
Here is a short description how to receive mtqq messages with help of Mosquitto from the Arduino device to another device. In my case the device is installe with Ubuntu 25.10 operatingsystem.
First install mosquitto-clients and optionally mosquitto if you want use the Ubuntu device as mtqq broker (server).
```console
sudo apt install mosquitto-clients
sudo apt install mosquitto
```
```console
Then start using Mosquitto ny typing.
sudo systemctl start mosquitto
```
Optionally if you wan't that the Mosquitto service starts automatically then type.
```console
sudo systemctl enable mosquitto
```

