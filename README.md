# Sensor Data Viewer.

The goal with this project was to display temperature and humitidy data to a oled display and transfer same data over mtqq protocol
to an another device. It was accomplished with help of Arduino Uno R4 Wifi board and DHT22 sensor. It also done possible to turn off mtqq protocol transsmission
with help of button. A rgb led lights up green coloe when mtqq protocol transsmission is turned on, otherwise it the color is red. In my case I uses the ST7735S model as my 
oled display. The code is written in C++ programming language with the help of Arduino IDE complitator. You can find more info about Arduino IDE from this link. https://www.arduino.cc/en/software.

Included Arduino libraries for this project.

```
#include <WiFiS3.h>           # Library for the wifi connection.
#include <DHT.h>              # Library for the DHT22 Sensor.
#include <DHT_U.h>            # Library for the DHT22 Sensor.
#include <PubSubClient.h>     # Library for the mtqq protocol.
#include <Adafruit_ST7735.h>  # Library for the oled display.
#include <Adafruit_GFX.h>     # Library for the oled display.
```

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
DHT22 sensor is connected to pin 2, 3,3V and GND. <br />
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
Then start using Mosquitto ny typing.
```console
sudo systemctl start mosquitto
```
Optionally if you wan't that the Mosquitto service starts automatically when device boots, then type.
```console
sudo systemctl enable mosquitto
```
### Example of a mtqq output with Mosquitto

https://github.com/user-attachments/assets/43e05c0d-fe26-4879-b46f-6a964fa270de

Here is sample C# code that also output mtqq messages from the Arduino device to a console window with help of the M2Mqtt plugin.
```
using System.Text;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages; 
MqttClient client = new MqttClient("192.168.0.239"); # Broker ip adress.
client.MqttMsgPublishReceived += new MqttClient.MqttMsgPublishEventHandler(client_MqttMsgPublishReceived);

string clientId = Guid.NewGuid().ToString();
client.Connect(clientId);
client.Subscribe(new string[] { "Sensordata" }, new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE });

static void client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e)
{
    Console.WriteLine( Encoding.UTF8.GetString(e.Message));
}
```






