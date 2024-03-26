#define BLYNK_TEMPLATE_ID "TMPL6c_P5tST4"
#define BLYNK_TEMPLATE_NAME "finaliot"
#define BLYNK_AUTH_TOKEN "5JgTBl3E12FE4gCCzqoXobsun8bWPAi5"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char ssid[] = "kaeittisak";
char pass[] = "123456789";

#define DHTPIN 33
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const int ledPin = 2;
bool ledState = false;
bool shouldBlink = false;

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  delay(100);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  dht.begin();

  pinMode(ledPin, OUTPUT);
  timer.setInterval(1000L, sendSensorData);
  timer.setInterval(500L, blinkLed);
}

void blinkLed() {
  if (shouldBlink) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    Blynk.virtualWrite(V3, ledState ? 255 : 0);
  } else {
    digitalWrite(ledPin, LOW);
    Blynk.virtualWrite(V3, 0);
  }
}

void sendSensorData() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);

  if (temperature > 30 || humidity > 70) {
    Blynk.virtualWrite(V4, "ค่าเกินปกติ!");
    shouldBlink = true;
  } else {
    Blynk.virtualWrite(V4, "ค่าปกติ");
    shouldBlink = false;
  }
}

void loop() {
  Blynk.run();
  timer.run();
}