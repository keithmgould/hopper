#include "../../lib/constants.h"
#include <PololuMaestro.h>

SoftwareSerial maestroSerial(RX_FROM_MAESTRO, TX_TO_MAESTRO);
MicroMaestro maestro(maestroSerial);  


void setup()
{
  maestroSerial.begin(9600);
}


void loop(){
  for(int i = LIMIT_ANKLE_DOWN; i < LIMIT_ANKLE_YAW_UP; i++){
    maestro.setTarget(CHANNEL_ANKLE_YAW, i);
    delay(15);
  }

  for(int i = LIMIT_ANKLE_YAW_UP; i > LIMIT_ANKLE_YAW_DOWN; i--){
    maestro.setTarget(CHANNEL_ANKLE_YAW,i);
    delay(15);
  }
}
