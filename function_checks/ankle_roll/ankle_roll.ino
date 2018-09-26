#include "./constants.h"
#include <SoftwareSerial.h>
#include <PololuMaestro.h>

SoftwareSerial maestroSerial(RX_FROM_MAESTRO, TX_TO_MAESTRO);
MicroMaestro maestro(maestroSerial);  


void setup()
{
  Serial.begin(9600);
  while (!Serial); 
  maestroSerial.begin(9600);
}


void loop(){
  Serial.println("wtf");
  for(int i = LIMIT_ANKLE_ROLL_LEFT; i < LIMIT_ANKLE_ROLL_RIGHT; i += 20){
    maestro.setTarget(CHANNEL_ANKLE_ROLL, i);
    delay(15);
  }
  Serial.println("wtf2");
  for(int i = LIMIT_ANKLE_ROLL_RIGHT; i > LIMIT_ANKLE_ROLL_LEFT; i -= 20){
    maestro.setTarget(CHANNEL_ANKLE_ROLL,i);
    delay(15);
  }
}
