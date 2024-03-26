#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <DHT.h>

const char* ssid = "kaeittisak"; // ชื่อ WiFi
const char* password = "123456789"; // รหัสผ่าน WiFi
unsigned long myChannelNumber = 2486739; // หมายเลขช่องของคุณบน ThingSpeak
const char * myWriteAPIKey = "8YIKV9SRO3WB67WO"; // API Key สำหรับเขียนข้อมูล

const int DHTPIN = D4; // เชื่อมต่อขา DATA ของ DHT22 เข้ากับ GPIO D4 (GPIO2)
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  WiFi.begin(ssid, password); // เชื่อมต่อ WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  ThingSpeak.begin(client); // สร้างการเชื่อมต่อ ThingSpeak
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  ThingSpeak.setField(1, temperature); // ส่งค่าอุณหภูมิไปยังฟิลด์ที่ 1
  ThingSpeak.setField(2, humidity); // ส่งค่าความชื้นไปยังฟิลด์ที่ 2
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  delay(20000); // รอ 20 วินาที ก่อนอ่านค่าใหม่
}