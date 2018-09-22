#include <PololuMaestro.h>
#include <SoftwareSerial.h>

SoftwareSerial maestroSerial(6, 7); // rx, tx
MicroMaestro maestro(maestroSerial);

// SERVO CHANNELS
constexpr int CHANNEL_ANKLE_YAW = 3;
constexpr int CHANNEL_ANKLE_ROLL = 1;
constexpr int CHANNEL_KNEE = 0;
constexpr int CHANNEL_TOE = 2;

// LIMIT POSITIONS
constexpr int LIMIT_ANKLE_YAW_DOWN = 5000;
constexpr int LIMIT_ANKLE_YAW_UP = 8000;
constexpr int LIMIT_ANKLE_ROLL_LEFT = 5000;
constexpr int LIMIT_ANKLE_ROLL_RIGHT = 7000;
constexpr int LIMIT_KNEE_STRAIGHT = 4000;
constexpr int LIMIT_KNEE_BENT = 7000;
constexpr int LIMIT_TOE_STRAIGHT = 4000;
constexpr int LIMIT_TOE_FLEXED = 6000;

// RESET POSITIONS
constexpr int RESET_ANKLE_YAW = (LIMIT_ANKLE_YAW_DOWN + LIMIT_ANKLE_YAW_UP) / 2;
constexpr int RESET_ANKLE_ROLL = (LIMIT_ANKLE_ROLL_LEFT + LIMIT_ANKLE_ROLL_RIGHT) / 2;
constexpr int RESET_KNEE = LIMIT_KNEE_STRAIGHT;
constexpr int RESET_TOE = LIMIT_TOE_STRAIGHT;

// DELAY BETWEEN SERVO COMMANDS
constexpr int SERVO_SLEEP = 15;

void reset_pose(){
  maestro.setTarget(CHANNEL_ANKLE_ROLL,RESET_ANKLE_ROLL);
  maestro.setTarget(CHANNEL_ANKLE_YAW,RESET_ANKLE_YAW);
  maestro.setTarget(CHANNEL_TOE,RESET_TOE);
  maestro.setTarget(CHANNEL_KNEE,RESET_KNEE);
}

void move_from_to(int channel, int from, int to, int speed=20){
  int distance = to - from;
  for(int i = 0; i < abs(distance); i = i+speed){
    int final_i = distance < 0 ? -i : i;
    maestro.setTarget(channel,from + final_i);
    delay(SERVO_SLEEP);
  }
}

void toe_bend(){
  move_from_to(CHANNEL_TOE, RESET_TOE, LIMIT_TOE_FLEXED);
  move_from_to(CHANNEL_TOE, LIMIT_TOE_FLEXED, RESET_TOE);
}

void ankle_roll(){
  move_from_to(CHANNEL_ANKLE_YAW, RESET_ANKLE_YAW, LIMIT_ANKLE_YAW_UP);
  move_from_to(CHANNEL_ANKLE_ROLL, RESET_ANKLE_ROLL, LIMIT_ANKLE_ROLL_RIGHT);
  move_from_to(CHANNEL_ANKLE_YAW, LIMIT_ANKLE_YAW_UP, LIMIT_ANKLE_YAW_DOWN);
  move_from_to(CHANNEL_ANKLE_ROLL, LIMIT_ANKLE_ROLL_RIGHT, LIMIT_ANKLE_ROLL_LEFT);
  move_from_to(CHANNEL_ANKLE_YAW, LIMIT_ANKLE_YAW_DOWN, RESET_ANKLE_YAW);
  move_from_to(CHANNEL_ANKLE_ROLL, LIMIT_ANKLE_ROLL_LEFT, RESET_ANKLE_ROLL);
}

void knee_bend(){
  move_from_to(CHANNEL_KNEE, RESET_KNEE, LIMIT_KNEE_BENT);
  move_from_to(CHANNEL_KNEE, LIMIT_KNEE_BENT, RESET_KNEE);
}

void crouch(){
  
}

void spring(){}

void jump(){
  crouch();
  spring();
}

void setup()
{
  Serial.begin(9600);
  maestroSerial.begin(9600);
  reset_pose();
}

/* 
setTarget takes the channel number you want to control, and
the target position in units of 1/4 microseconds. A typical
RC hobby servo responds to pulses between 1 ms (4000) and 2
ms (8000).*/
void loop(){
//  jump();
  // ankle_roll();
 knee_bend();
 // toe_bend();
}
