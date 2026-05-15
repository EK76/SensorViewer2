# Sensor Data Viewer.

The goal with this project was to display temperature and humitidy data to a oled display and transfer same data over mtqq protocol
to an another device. It was accomplished with help of Arduino Uno R4 Wifi board and DHT22 sensor. It also done possible to turn off mtqq protocol transsmission
with help of button. A rgb led lights up green coloe when mtqq protocol transsmission is turned on, otherwise it the color is red. In my case I uses the ST7735S model as my 
oled display

### MQTT (Message Queuing Telemetry Transport)
It is a lightweight, publish-subscribe network protocol designed for machine-to-machine (M2M) communication and the Internet of Things (IoT). It is ideal for low-bandwidth, high-latency, 
or unreliable networks, making it the standard for connecting remote devices, sensors, and mobile applications with minimal power consumption.
More info about **[MQTT](https://en.wikipedia.org/wiki/MQTT)**-

### This project consist of

Arduino Uno R4 Wifi (in my case) or any other Arduino board with Wifi feature of your choosing.
1 psc ST7735S oled display 
1 psc DHT22 sensor
1 pcs push button
1 psc RGB led (indicating status of mtqq protocol transsmission).
2 pcs 330 Ohm resistors that are connected to rgb led.
Jump wires

<img width="348" height="295" alt="image" src="https://github.com/user-attachments/assets/ba184e96-0d59-44c3-baac-f302b08864b7" />
##### Sensor DHT22 pinout.

<img width="1260" height="504" alt="image" src="https://github.com/user-attachments/assets/fc17f73e-59f6-4ea4-9d5e-0b24323387d9" />
##### Sensor ST7735S oled display pinout.



