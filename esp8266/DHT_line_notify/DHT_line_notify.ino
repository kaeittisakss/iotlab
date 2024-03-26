#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>
#include <DHT.h>

#define DHTTYPE DHT22

const char* ssid        = "kaeittisak";
const char* password    = "123456789";
const char* lineToken   = "VVBuiUdqFPW7lJNR4r94J6tExU71HmHaLcJ08MizRIY";

const int dhtPin  = D3;  // เปลี่ยนเป็นขาที่เชื่อมต่อกับ DHT22 บน ESP8266
const int ledPin  = D4;  // เปลี่ยนเป็นขาที่เชื่อมต่อกับ LED บน ESP8266

DHT dht(dhtPin, DHTTYPE);

bool isAlertSent = false;

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    
    dht.begin();
    
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi.");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" Connected!");
    
    LINE.setToken(lineToken);
}

void loop() {
    float temperature = dht.readTemperature();
    float humidity    = dht.readHumidity();
    
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    
    if (temperature > 35.0 && !isAlertSent) {
        LINE.notify("Temperature is above 35°C!");
        isAlertSent = true;
    } else if (temperature <= 35.0) {
        isAlertSent = false;
    }
    
    if (temperature > 35.0) {
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
    } else {
        digitalWrite(ledPin, LOW);
    }
    
    delay(2000);
}