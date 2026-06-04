#include <Arduino_LED_Matrix.h>
#include <WiFiS3.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ArduinoMqttClient.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include "networkinfo.h"
#include "display.h"

#define screenWidth 128 
#define screenHight 64 

#define oledReset -1
#define screenAdress 0x3D 
Adafruit_SSD1306 display(screenWidth, screenHight, &Wire1, oledReset);

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dhtSensor(DHTPIN, DHTTYPE);

char ssid2[] = ssid;
char pass[] = password;
int status = WL_IDLE_STATUS;
float temp, hum;
unsigned long previousDelay = 0; 
unsigned long lastDebouncetime = 0;
const unsigned long debounceDelay = 250;
long interval = 3000; 
int redLed = 6, greenLed = 7, checkLoop = 0;
bool enableMtqq = false;
bool mtqqEnabled = true;
char tempValue[10] = " C";
char humValue[10] = " %";
char tempConvert[10];
char humConvert[10];
char showIP[10] = "IP: ";
char showIP2[20];
const char broker[] = "test.mosquitto.org";
const char topic[]  = "Sensordata";
int port = 1883;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
ArduinoLEDMatrix showOptions;

void showDisplay(String showText)
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 30);
  display.println(showText);
  display.display();      
  delay(2000);
}

void connectMtqq(float temp, float hum)
{
   String rawData = "Temperature: " + String(temp) + " C Humitidy: " + String(hum) +" %";
   const char* mtqqData = rawData.c_str();

   if (!mqttClient.connect(broker, port)) 
   {
      Serial.print("MQTT connection failed! Error code = ");
      Serial.println(mqttClient.connectError());
      mtqqEnabled = false;
      showOptions.loadFrame(error);
   }
  else
  {
    mqttClient.beginMessage(topic);
    mqttClient.print(mtqqData);
    mqttClient.endMessage();
  } 
}

void setup() 
{
  Serial.begin(9600);
  dhtSensor.begin();
  WiFi.begin(ssid2,pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  delay(2000);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, screenAdress)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  Serial.println("IP adress: ");
  Serial.println(WiFi.localIP());
  delay(500);
  WiFi.localIP().toString().toCharArray(showIP2, 16);
  strcat(showIP, showIP2);

  display.clearDisplay();
  display.setTextSize(1.5); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("SensorViewer ver 1.4"));
  display.setCursor(0, 15);
  display.println(F("Ken Ekholm"));
  display.setCursor(0, 30);
  display.println(F("All rights reserved."));
  display.setCursor(0, 45);
  display.println(showIP);
  display.display();    

  showOptions.begin();
  showOptions.loadFrame(heart);
  delay(7000);
  mqttClient.setId("esp32s3");
  if (!mqttClient.connect(broker, port)) 
  {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    mtqqEnabled = false;
    showOptions.loadFrame(error);
  }
  else
  {
    Serial.println("Connected.");
    showOptions.loadFrame(chip);
  } 
}

void loop() 
{
  unsigned long currentDelay = millis();
  if (currentDelay - previousDelay >= interval) 
  { 
    temp = dhtSensor.readTemperature();
    hum = dhtSensor.readHumidity();
    if (isnan(hum) || isnan(temp)) 
    {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    previousDelay = currentDelay;  
    if (mtqqEnabled == true)
    {
      connectMtqq(temp, hum);
    } 

    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %  Temperature: ");
    Serial.print(temp);
    Serial.println(" *C");

    dtostrf(temp, 8, 2, tempConvert);
    strcat(tempConvert, tempValue);
    dtostrf(hum, 8, 2, humConvert);
    strcat(humConvert, humValue);

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(30, 0);
    display.println(F("Temperature"));
    display.setCursor(20, 15);
    display.println(tempConvert);
    display.setCursor(35, 30);
    display.println(F("Humitidy"));
    display.setCursor(20, 45);
    display.println(humConvert);
    display.display(); 
    checkLoop++;
    switch (checkLoop)
    {
      case 16:
        showOptions.loadFrame(arrowleft);
        break;
      case 20:
        showOptions.loadFrame(arrowright);
        break;
      case 24:
        if (mtqqEnabled == true)
        {
          showOptions.loadFrame(chip);
        }
        else
        {
          showOptions.loadFrame(error);
        }
        checkLoop = 0;
        break;
    }
  }  
}
