// การทดลองที่ 1 

#include <TridentTD_LineNotify.h>

#define SSID        "IoT-Gateway"
#define PASSWORD    "11111111111111111111"
#define LINE_TOKEN  "xxxxxxxxxxxxxxxxxxx"

void setup() {
  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) 
  { 
    Serial.print("."); delay(400); 
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);

  // ตัวอย่างส่งข้อความ
  LINE.notify("Setup start...");

  // ตัวอย่างส่งข้อมูล ตัวเลข
  LINE.notify(123456789);          // จำนวนเต็ม
  

  // เลือก Line Sticker ได้จาก เอกสารใน classroom
  LINE.notifySticker(1,2);        // ส่ง Line Sticker ด้วย PackageID 1 , StickerID 100
  LINE.notifySticker("Go Go",1,3);  // ส่ง Line Sticker ด้วย PackageID 2 , StickerID 100  พร้อมข้อความ

  // ตัวอย่างส่ง รูปภาพ ด้วย url
  
  LINE.notifyPicture("KMUTNB","https://www.eng.kmutnb.ac.th/wp-content/uploads/2020/12/logo-kmutnb-final-800x214.jpg");
}

void loop() {

  LINE.notify("Hello world");
  delay(10000);
}
