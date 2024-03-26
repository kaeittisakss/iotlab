#define BLYNK_TEMPLATE_ID "TMPL6c_P5tST4"
#define BLYNK_TEMPLATE_NAME "finaliot"
#define BLYNK_AUTH_TOKEN "5JgTBl3E12FE4gCCzqoXobsun8bWPAi5"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "kaeittisak";
char pass[] = "123456789";

const int sensorPin = 33; 
const int ledPin = 2; 

bool ledState = false; // LED กระพริบ
bool shouldBlink = false; // ตัวแปรสำหรับกำหนดว่า LED ควรจะกระพริบหรือไม่

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

  pinMode(ledPin, OUTPUT);

   // ตั้งเวลาเพื่อเรียกฟังก์ชัน sendSensorData ทุก ๆ 1 วินาที
  timer.setInterval(1000L, sendSensorData);

    // ตั้งเวลาเพื่อเรียกฟังก์ชัน blinkLed ทุก ๆ 500 มิลลิวินาทีสำหรับการกระพริบ LED
  timer.setInterval(500L, blinkLed);
}

// ฟังก์ชันสำหรับกระพริบ LED
void blinkLed() {
  if (shouldBlink) {
    ledState = !ledState; // สลับสถานะ LED
    digitalWrite(ledPin, ledState); // ตั้งค่า LED
    Blynk.virtualWrite(V3, ledState ? 255 : 0); // อัพเดต LED บน Blynk
  } else {
    digitalWrite(ledPin, LOW); // หากไม่ควรกระพริบ, ให้ปิด LED
    Blynk.virtualWrite(V3, 0); // ตั้งค่า LED เป็น OFF
  }
}

void sendSensorData() {
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  Blynk.virtualWrite(V1, sensorValue); 
  
  if (sensorValue > 3500) {
    //digitalWrite(ledPin, HIGH); // เปิด LED
    Blynk.virtualWrite(V2, "ค่าเกินปกติ!"); 
    shouldBlink = true; // ตั้งค่าให้ LED กระพริบ
  } else {
    Blynk.virtualWrite(V2, "ค่าปกติ"); 
    shouldBlink = false; // หยุดกระพริบ LED
  }
}

void loop() {
  Blynk.run();
  timer.run(); 
}
