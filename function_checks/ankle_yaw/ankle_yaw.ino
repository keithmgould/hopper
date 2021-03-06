#include "./constants.h"
#include <SoftwareSerial.h>
#include <PololuMaestro.h>

SoftwareSerial maestroSerial(RX_FROM_MAESTRO, TX_TO_MAESTRO);
MicroMaestro maestro(maestroSerial);  


void setup()
{
  Serial.begin(9600);
  maestroSerial.begin(9600);
}


void loop(){
  Serial.println("wtf");
  for(int i = 4000; i < 5000; i += 20){
    maestro.setTarget(0, i);
    delay(15);
  }
  Serial.println("wtf2");
  for(int i = 5000; i > 4000; i -= 20){
    maestro.setTarget(0,i);
    delay(15);
  }
}
