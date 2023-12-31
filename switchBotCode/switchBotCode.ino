/* Blynk Device Info */
#define BLYNK_TEMPLATE_ID           "TEMPLATE ID"
#define BLYNK_TEMPLATE_NAME         "TEMPLATE NAME"
#define BLYNK_AUTH_TOKEN            "AUTH TOKEN"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

#define SERVO_PIN 0
#define PRESS_DEG 0
#define UNPRESS_DEG 180

// WiFi credentials.
char ssid[] = "WIFI NAME";
char pass[] = "WIFI PASSWORD";

bool servoPress = false;
bool servoOpen = false;

unsigned long prevTime = 0;
unsigned long currentTime = 0;
const long interval = 1500;

Servo  servo;

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt();
  if(pinValue == 1)
    servoPress = true;
}


void setup()
{
  servo.attach(SERVO_PIN);
  
  servo.write(UNPRESS_DEG);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

}

void loop()
{
  Blynk.run();
  currentTime = millis(); 
  if(servoPress)
  {
    servo.write(PRESS_DEG);
    prevTime = currentTime;
    servoOpen = true;
    servoPress = false;
  }
  if(servoOpen && ((currentTime - prevTime) >= interval))
  {
    servo.write(UNPRESS_DEG);
    prevTime = currentTime;
    servoOpen = false;
  }
  
}
