#include <ThingerESP8266.h>

#define USERNAME "JairoTimbe"
#define DEVICE_ID "abc"
#define DEVICE_CREDENTIAL "kcGTbFTMI28kI&"

#define SSID "CanarNet_Familia Timbe"
#define SSID_PASSWORD "bj_A8DePraty"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_BUILTIN);

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());
}

void loop() {
  thing.handle();
}
