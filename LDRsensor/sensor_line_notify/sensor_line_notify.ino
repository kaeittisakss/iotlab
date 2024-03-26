//sensor + line ถ้าค่าเกิน3500ให้ส่งเเจ้นเตือน 1 ครั้ง พร้อมไฟกระพริบจนกว่าจะน้อยกว่า 3500

#include <WiFi.h>
#include <TridentTD_LineNotify.h>

const char* ssid     = "kaeittisak";
const char* password = "123456789";
const char* lineToken = "VVBuiUdqFPW7lJNR4r94J6tExU71HmHaLcJ08MizRIY";

const int sensorPin = 33;  // เชื่อมต่อขา A0 เข้ากับ GPIO33
const int ledPin = 2;      // สมมติว่า LED ต่อกับ GPIO2
bool isAlertSent = false;  // ใช้สำหรับตรวจสอบว่าส่งการแจ้งเตือนไปแล้วหรือยัง

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  
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
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  if (sensorValue > 3500 && !isAlertSent) {
    LINE.notify("Sensor value is above 3500!");
    isAlertSent = true;  // ป้องกันการส่งการแจ้งเตือนซ้ำ
  } else if (sensorValue <= 3500) {
    isAlertSent = false;
  }

  // กระพริบ LED ถ้าค่าเซ็นเซอร์มากกว่า 3500
  if (sensorValue > 3500) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  } else {
    digitalWrite(ledPin, LOW); // ปิด LED ถ้าค่าเซ็นเซอร์ต่ำกว่าหรือเท่ากับ 3500
  }

  delay(1000); // ควบคุมเวลาวนซ้ำ
}
