# Sensor DataViewer 2.

The goal with this project was to display temperature and humitidy data to a oled display and transfer same data over MQTT protocol
to an another device. It was accomplished with help of a Arduino Uno R4 Wifi board and a DHT22 sensor. In my case I use the Adafruit SSD1306 model as my 
oled display. The Arduino UNO R4 WiFi comes with a built in 12x8 LED Matrix, that is available to be programmed to display graphics, animations or act as an interface
which I have used in this project. The code is written in C++ programming language with the help of Arduino IDE complitator. 
More info about **[Arduino IDE](https://www.arduino.cc/en/software)**.

Included Arduino libraries for this project.

```
#include <WiFiS3.h>            // Library for the wifi connection.
#include <DHT.h>               // Library for the DHT22 Sensor.
#include <DHT_U.h>             // Library for the DHT22 Sensor.
#include <PubSubClient.h>      // Library for the mtqq protocol.
#include <Adafruit_SSD1306.h>  // Library for the oled display.
#include <Adafruit_GFX.h>      // Library for the oled display.
#include <network.h>           // Info about your wireless network.
#include <display.h>           // Diffrerents Led Matrix configurations.
```

### MQTT (Message Queuing Telemetry Transport)
It is a lightweight, publish-subscribe network protocol designed for machine-to-machine (M2M) communication and the Internet of Things (IoT). It is ideal for low-bandwidth, high-latency, 
or unreliable networks, making it the standard for connecting remote devices, sensors, and mobile applications with minimal power consumption. 
More info about **[MQTT](https://en.wikipedia.org/wiki/MQTT)**. 

### This project consist of

- Arduino Uno R4 Wifi (in my case) or any other Arduino board with Wifi feature of your choosing.
- 1 psc Adafruit SSD1306 oled display 
- 1 psc DHT22 sensor
- 1 pcs push button
- 1 psc RGB led with 2 pins (indicating status of mtqq protocol transsmission). 
- Jump wires

<img width="348" height="295" alt="dht22" src="https://github.com/user-attachments/assets/d3ca62ba-9182-493c-a95a-1ab8c3f5866c" />

##### Sensor DHT22 pinout.

<img width="300" height="300" alt="oled3" src="https://github.com/user-attachments/assets/240e1925-592e-4e6b-b15a-fcbe9b600036" />

##### Picture of Adafruit SSD1306 oled display.

## Schematics
<img width="493" height="337" alt="arduino" src="https://github.com/user-attachments/assets/82cf334d-5a39-40c5-a373-8dc09ceaac59" /><br />

Rgb led's two pins are connected to the pins 6 and 7.<br />
Push button is connected to pin 3 (workings as an interrupt).<br />
DHT22 sensor is connected to pin 2, 3,3V and GND. <br />
Adafruit SSD1306 oled display is connected to Arduino with help of qwiic cable.

### Qwiic connector

Qwiic connector is a standardized 4-pin JST SH connector (1 mm pitch) developed by SparkFun Electronics for rapid, solder-free hardware prototyping. 
It allows you to quickly plug sensors, displays, and actuators directly into microcontrollers using the I2C communication protocol.

### MQTT broker installation.

Here is a short description how to install your own broker, in this case I have chhosen Mosquitto, which can be used to send MQTT messages from the Arduino device to another device. 
In my case the device is installed with Ubuntu 25.10 operatingsystem.
First install mosquitto-clients and optionally mosquitto if you want to use the Ubuntu device also as MQTT broker (server). 
```console
sudo apt install mosquitto-clients
sudo apt install mosquitto
```
Then start using Mosquitto ny typing.
```console
sudo systemctl start mosquitto
```
Optionally if you wan't that the Mosquitto service starts automatically when device boots, then type.
```console
sudo systemctl enable mosquitto
```
Optionally for testing your mqtt project, can use these test brokers before you for example install your own mqtt broker.
- test.mosquitto.org
- broker.hivemq.com

### Example of a MQTT output with Mosquitto

https://github.com/user-attachments/assets/43e05c0d-fe26-4879-b46f-6a964fa270de

Here is sample C# code that also output MQTT messages from the Arduino device to a console window with help of the M2Mqtt plugin.
```
using System.Text;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages; 
MqttClient client = new MqttClient("192.168.0.239"); # Broker ip adress.
client.MqttMsgPublishReceived += new MqttClient.MqttMsgPublishEventHandler(client_MqttMsgPublishReceived);

string clientId = Guid.NewGuid().ToString();
client.Connect(clientId);
client.Subscribe(new string[] { "Sensordata" }, new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE });
# Sensordata function as MQTT topic to enable the MQTT broker to identify the appropriate publishers and subscribers for message transmission.

static void client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e)
{
    Console.WriteLine( Encoding.UTF8.GetString(e.Message));
}
```






