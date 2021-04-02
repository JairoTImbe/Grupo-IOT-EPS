#define _DISABLE_TLS_
// other includes goes here
#include <ThingerESP8266.h>
//configuraciones para la plataforma
#define USERNAME "JairoTimbe"
#define DEVICE_ID "abc"
#define DEVICE_CREDENTIAL "kcGTbFTMI28kI&"

#define SSID "CanarNet_Familia Timbe"
#define SSID_PASSWORD "bj_A8DePraty"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

//variables globales
float celsius=0;
int LED_D1=5;
int SensorTemp=A0;

void setup() {
  Serial.begin(115200); 
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_D1, OUTPUT);
  //conf wifi
  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_BUILTIN);
  thing["LED_D1"] << digitalPin(LED_D1);
  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(celsius);
}

void loop() {

  thing.handle();
  //lectura del sensor de temperatura
  int analogValue = analogRead(SensorTemp);
  float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU
  celsius = millivolts/10;
  Serial.println(celsius);
  delay(500);
  
  
}
