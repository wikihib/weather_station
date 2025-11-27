#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <WiFiClient.h>
#include <WiFi.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define DHTPIN 7 //dht podpiete do digital7
#define DHTTYPE DHT22

// || podmien na swoje dane ||
const char* ssid = "nazwa sieci";
const char* password = "haslo sieci";
const char* host = "ipv4 z ipconfig";

WiFiClient client;

DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP280 bmp;

int uvPin = A1; //uv podpiete do analog1
int uvIndex;
// int buzzerPin = 3;

void setup()
{
  //siec
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(". ");
  }
  Serial.println("\nPołączono z WiFi");


  lcd.init();
  lcd.backlight();
  dht.begin();
  // pinMode(buzzerPin, OUTPUT);
}


void loop()
{
  float temp = dht.readTemperature();
  float wilg = dht.readHumidity();
  float cisn = bmp.readPressure() / 100.0F; // hPa
  int analogValue = analogRead(uvPin);

  float voltage = analogValue * 5.0 / 1023.0;

  if (voltage < 0.227) uvIndex = 0;
  else if (voltage < 0.318) uvIndex = 1;
  else if (voltage < 0.408) uvIndex = 2;
  else if (voltage < 0.503) uvIndex = 3;
  else if (voltage < 0.606) uvIndex = 4;
  else if (voltage < 0.696) uvIndex = 5;
  else if (voltage < 0.795) uvIndex = 6;
  else if (voltage < 0.881) uvIndex = 7;
  else if (voltage < 0.976) uvIndex = 8;
  else if (voltage < 1.068) uvIndex = 9;
  else if (voltage < 1.150) uvIndex = 10;
  else uvIndex = 11;

  if (client.connect(host, 80)) {

    String postData = "temp=" + String(temp, 1) +
                      "&wilg=" + String(wilg, 1) +
                      "&uv=" + String(uvIndex);

    // sprawdzamy czy cisnienie jest poprawne
    if (!isnan(cisn) && cisn > 0.0) {
        postData += "&cisn=" + String(cisn, 1);
    }

    client.println("POST /insert.php HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(postData.length()));
    client.println("Connection: close");
    client.println();
    client.print(postData);

    Serial.println("Wysłano: " + postData);
}
client.stop();

  // || uzywane gdy jest podlaczony buzzer; wlacza sie przy wysokim uv ||

  // if(uvIndex >= 7) {
    // tone(buzzerPin, 3000);
  // }else {
    // noTone(buzzerPin);
  // }

  // || uzywane gdy jest podpiety LCD ||

  // lcd.setCursor(0, 0);
  // lcd.print("T:");
  // lcd.print(temp, 1);
  // lcd.print("C ");

  // lcd.print("W:");
  // lcd.print(wilg, 1);
  // lcd.print("%");

  // lcd.setCursor(0, 1);
  // lcd.print("UV:");
  // if(uvIndex < 10) lcd.print(" ");
  // lcd.print(uvIndex);

  delay(10000);
}
