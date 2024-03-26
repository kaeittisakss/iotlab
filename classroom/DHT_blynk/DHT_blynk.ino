#define BLYNK_TEMPLATE_ID "TMPL67hoMQtAyx"
#define BLYNK_TEMPLATE_NAME "xxxxxxxx"
#define BLYNK_AUTH_TOKEN "8yPyZQUR7fXuUzjN1Xmd4U3n8A21xcDmSv"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN D4        
#define DHTTYPE DHT22
#define LED_1 D1      //V4    
#define LED_2 D2      //V3    


char ssid[] = "WiFi-Name";
char pass[] = "123456789";
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


//-------------------------- LED ---------------------------------- //
BLYNK_WRITE(V2)
{
  int value = param.asInt();
  digitalWrite(LED_1, value);
  Blynk.virtualWrite(V4, value);
}

BLYNK_WRITE(V3)
{
  int value = param.asInt();
  digitalWrite(LED_2, value);
  Blynk.virtualWrite(V5, value);
}


// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  Blynk.syncAll();
}

// This function sends DHT22 sensor readings to Virtual Pins V0 and V1
void myTimerEvent()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(t) || isnan(h))
  {
    Serial.println("Error Reading DHT 22 !!!");
    delay(1000);
    return;
  }
  else
  {
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(3000L, myTimerEvent);
  dht.begin();
}


void loop()
{
  Blynk.run();
  timer.run();
}