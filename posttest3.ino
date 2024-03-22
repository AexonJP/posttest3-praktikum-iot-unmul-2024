
#include <ThingerESP8266.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
// #include <String.h>
#include <ESP8266HTTPClient.h>
// #include <WiFiClient.h>

#define DHTPIN D4 // pin digital sensor DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define USERNAME "aexon" //Username thinger.io
#define DEVICE_ID "aexons" // Lihat pada setting dari device yang sudah dibuat di thinger.io
#define DEVICE_CREDENTIAL "aA123456" // Lihat pada setting dari device yang sudah dibuat di thinger.io (Generate random saja)
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

const char* ssid = "Aexons";
const char* password = "Aexon123";
float suhu, kelembaban;

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D5, OUTPUT);
  dht.begin();
  thing.add_wifi(ssid, password);
    thing["dht11"] >> [](pson& out){
      out["kelembaban"] = kelembaban;
      out["suhu"] = suhu;
    };
}

void loop() {
      thing.handle();
      float h = dht.readHumidity();
      // Read temperature as Celsius (the default)
      float t = dht.readTemperature();
      // Read temperature as Fahrenheit (isFahrenheit = true)
      // float f = dht.readTemperature(true);

      Serial.println(t);
      
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);

      if(t >= 36.00){
        digitalWrite(D1, HIGH);
        tone(D5, 1000);
      }
      else if(t < 36.00 && t > 30.00){
        digitalWrite(D2, HIGH);
        noTone(D5);
      }
      else{
        noTone(D5);
        digitalWrite(D3, HIGH);
      }
      kelembaban = h; // Update nilai kelembaban
      suhu = t;


    // }
    // else {
    //   Serial.println("WiFi Disconnected");
    // }
  //   lastTime = millis();
  // }

}
