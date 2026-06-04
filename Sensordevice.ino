#include <WiFiS3.h>
#include <DHT.h>
#include <DHT_U.h>
#include <PubSubClient.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include "networkinfo.h"

#define cs_Value 10
#define dc_Value 9
#define rst_Value 8
Adafruit_ST7735 tft_Display = Adafruit_ST7735(cs_Value , dc_Value, rst_Value);

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
int redLed = 6, greenLed = 7, buttonState = 3, allow = 0;
volatile bool enableMtqq = false;

IPAddress server(192, 168, 0, 239);
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void showDisplay(String showText)
{

  tft_Display.fillScreen(ST7735_BLACK);
  tft_Display.setCursor(10, 30);
  tft_Display.println(showText);      
  delay(2000);
  tft_Display.fillScreen(ST7735_BLACK);
  allow = 0;
}

void connectMtqq(float temp, float hum)
{
   String rawData = "Temperature: " + String(temp) + " C Humitidy: " + String(hum) +" %";
   const char* mtqqData = rawData.c_str();

  if (client.connect("arduinoClient")) 
  {
    Serial.println("Connected.");
    client.publish("Sensordata",mtqqData);
  }   
  else
  {
    Serial.println("Not connected.");
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
  Serial.println(WiFi.localIP());
  client.setServer(server, 1883);

  tft_Display.initR(INITR_BLACKTAB);
  tft_Display.fillScreen(ST7735_BLACK);
  tft_Display.setTextColor(ST7735_WHITE);
  tft_Display.setRotation(1);
  tft_Display.setTextSize(2);

  if (!isnan(hum) || !isnan(temp)) {
    temp = dhtSensor.readTemperature();
    hum = dhtSensor.readHumidity();
  }
  else
  {  
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  tft_Display.setTextColor(ST7735_WHITE);
  tft_Display.setCursor(10, 10);
  tft_Display.println("Temperature");
  tft_Display.setCursor(10, 30);
  tft_Display.println(String(temp));
  tft_Display.setCursor(10, 50);
  tft_Display.println("Humidity");
  tft_Display.setCursor(10, 70);
  tft_Display.println(String(hum)); 

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buttonState, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), statusValue, CHANGE);
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
}

void loop() 
{
  unsigned long currentDelay = millis();
  if (currentDelay - previousDelay >= interval) 
  {
    previousDelay = currentDelay;  
   // tft_Display.setTextColor(ST7735_BLACK);
  //  tft_Display.setTextColor(ST7735_WHITE);
    tft_Display.fillRect(10, 30, 10, 30, ST7735_BLACK);
    tft_Display.setCursor(10, 30);
    tft_Display.fillRect(10, 70, 10, 70, ST7735_BLACK);
    tft_Display.setCursor(10, 70);
    if (!isnan(hum) || !isnan(temp)) {
      temp = dhtSensor.readTemperature();
      hum = dhtSensor.readHumidity();
      Serial.println("Value read!");
    }
    else
    {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    if  (enableMtqq == true)
    {
      connectMtqq(temp, hum);
      Serial.println("Tranfer.");
      if (allow == 1)
      {
        showDisplay("MTQQ Enabled");
        Serial.println("MTQQ Enabled");
        allow = 0;
      } 

    }
    else
    {
      if (allow == 1)
      {
        showDisplay("MTQQ Disabled.");
        Serial.println("MTQQ Disabled");
        allow = 0;
      } 
    }  

    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %  Temperature: ");
    Serial.print(temp);
    Serial.println(" *C");
    tft_Display.setTextColor(ST7735_WHITE);
    tft_Display.setCursor(10, 10);
    tft_Display.println("Temperature");
    tft_Display.setCursor(10, 30);
    tft_Display.println(String(temp) + " C");
    tft_Display.setCursor(10, 50);
    tft_Display.println("Humidity");
    tft_Display.setCursor(10, 70);
    tft_Display.println(String(hum) + " %");
  }  
}

void statusValue()
{
  if (millis() - lastDebouncetime > debounceDelay) 
  {
    lastDebouncetime = millis();
    allow = 1;
    if (enableMtqq == false)
    {
      enableMtqq = true;
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, HIGH);
    }
    else
    {
      enableMtqq = false;
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);
    }
  } 
}

