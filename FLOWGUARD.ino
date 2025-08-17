#define BLYNK_TEMPLATE_ID "TMPLe3oykRJ3w"
#define BLYNK_TEMPLATE_NAME "Water level monitoring"
#define BLYNK_AUTH_TOKEN "5VGZfGNAQKyxMIXq8I1g6234dKM6GHuVMT"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define trig D5   // Trig pin
#define echo D6   // Echo pin

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "asus";
char pass[] = "shetty555";
int depth = 40; // Tank depth in cm

BlynkTimer timer;

void waterlevel() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
  Serial.println(cm);
  
  long level = depth - cm;
  if (level < 0) level = 0;

  level = map(level, 0, depth, 0, 100);
  Blynk.virtualWrite(V0, level);
}

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, waterlevel);
}

void loop() {
  Blynk.run();
  timer.run();
}
