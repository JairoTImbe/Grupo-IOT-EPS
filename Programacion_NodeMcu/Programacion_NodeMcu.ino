
//#include "UbidotsMicroESP8266.h"
// Este archivo incluye una actualizacion de las librerias de Ubidots y observaras
// al conectarte a Ubidots que se crea otro dispostivo (Device) automaticamente
// tienes que configurar las etiquetas segun el nuevo dispositivo que se crea
// y adicionar la variable var_led  .... todo lo demás es identico 

#include "Ubidots.h"

#define DEVICE  "40f5202de2c5"  // Put here your Ubidots device label
#define VARIABLE  "var_led"  // Put here your Ubidots variable label
#define ID_TEMP "6060a75f1d84720a0164dab8" 
#define TOKEN  "BBFF-uAJoq4Lmyv2S4KjlkVVLiAFOKyBEqZ"  // Put here your Ubidots TOKEN

#define WIFISSID "CanarNet_Familia Timbe" // Put here your Wi-Fi SSID
#define PASSWORD "bj_A8DePraty" // Put here your Wi-Fi password

Ubidots client(TOKEN);

int LED_D1 = 5;
int SensorTemp=A0;
void setup() {
    Serial.begin(115200); 
    
    //client.wifiConnection(WIFISSID, PASSWORD);
    
    client.wifiConnect(WIFISSID, PASSWORD);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, 1);
    pinMode(LED_D1, OUTPUT);
    //client.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop() 
{
  //lectura de el sensor de temperatura
  int analogValue = analogRead(SensorTemp);
  float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU
  float celsius = millivolts/10;
  
    //obtener valor del boton "var_led" en la nube.
    float Valor_Led = client.get(DEVICE,VARIABLE);
    if (Valor_Led != ERROR_VALUE){
      Serial.print(F(">>>>>>>>> VALOR OBTENIDO POR EL LED: "));
      Serial.println(Valor_Led);
      
    }else{
      Serial.println(F("Error getting Valor_Led"));
    }

    //Encendido y apagado del led fisico

    if(Valor_Led==1.00){
      digitalWrite(LED_D1, HIGH);
      Serial.println("igual");
    }
    else{
      digitalWrite(LED_D1, LOW);
    }

    //envio de temperatura a la nube
    client.add(ID_TEMP, celsius); 
    client.send();
    delay(1000);
}
