#include <WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

const char* ssid = "kaeittisak"; // ชื่อ WiFi
const char* password = "123456789"; // รหัสผ่าน WiFi

unsigned long myChannelNumber = 2486739; // หมายเลขช่องของคุณบน ThingSpeak
const char * myWriteAPIKey = "8YIKV9SRO3WB67WO"; // API Key สำหรับเขียนข้อมูล

const int sensorPin = 33;  // เชื่อมต่อขา A0 เข้ากับ GPIO36 

WiFiClient  client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password); // เชื่อมต่อ WiFi

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  ThingSpeak.begin(client); // สร้างการเชื่อมต่อ ThingSpeak
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  float lux = calculateLux(sensorValue); // คำนวณค่า LUX

  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  Serial.print("Lux: ");
  Serial.println(lux);

  ThingSpeak.setField(1, sensorValue); // ส่งค่า sensorValue ไปยังฟิลด์ที่ 1
  ThingSpeak.setField(2, lux); // ส่งค่า LUX ไปยังฟิลด์ที่ 2

  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  delay(20000); // รอ 20 วินาที ก่อนส่งค่าใหม่
}

float calculateLux(int sensorValue) {
  // สมมติฐาน: ใช้สูตรเบื้องต้นสำหรับการแปลงค่าเซ็นเซอร์เป็น LUX
  // โปรดปรับสูตรนี้ตามลักษณะเฉพาะของเซ็นเซอร์แสงที่คุณใช้
  float lux = sensorValue * 0.5; // ตัวอย่างสูตรคำนวณแบบง่าย
  return lux;
}
