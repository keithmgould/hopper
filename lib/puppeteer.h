#ifndef __LEG_PUPPETEER__
#define __LEG_PUPPETEER__

#include <PololuMaestro.h>

SoftwareSerial maestroSerial(RX_FROM_MAESTRO, TX_TO_MAESTRO);
MicroMaestro maestro(maestroSerial);	

/* 
setTarget takes the channel number you want to control, and
the target position in units of 1/4 microseconds. A typical
RC hobby servo responds to pulses between 1 ms (4000) and 2
ms (8000).*/

struct Instruction { int channel; int from; int to; };

class Puppeteer{

	// Take a list of instructions (movements from/to) and execute 
	// them all simultaniously.
	// Each instruction has its own range and thus for them to all take the 
	// same time, the range must be interpolated

	void move_all_from_to(struct Instruction* instructions, int instruction_count, int duration_in_ms){
		int step_count = duration_in_ms / 15;
		int step_size;
		int distance;
		int final_j;
		Serial.println("move_all_from_to...");
		Serial.print(instructions->channel);
		Serial.print(", ");
		Serial.print(instructions->from);
		Serial.print(", ");
		Serial.println(instructions->to);
		Serial.print("instruction count: ");
		Serial.println(instruction_count);

		// step_count through time
		for(int j = 0; j < step_count; j++){
			Instruction* ptr = instructions;
			// step_count through each instruction
			for(int i = 0; i < instruction_count; i++, ptr++){
				distance = ptr->to - ptr->from;
				step_size = distance / step_count;
				final_j =  j * step_size;
				Serial.print("channel: ");
				Serial.print(ptr->channel);
				Serial.print(", distance: ");
				Serial.print(distance);
				Serial.print(", step_size: ");
				Serial.print(step_size);
				Serial.print(", j: ");
				Serial.print(j);
				Serial.print(", final_j: ");
				Serial.println(final_j);
				maestro.setTarget(ptr->channel, ptr->from + final_j);
			}
			Serial.println("---------------");
			delay(SERVO_SLEEP);
		}
	}

	void move_from_to(int channel, int from, int to, int speed=20){
	  int distance = to - from;
	  for(int i = 0; i < abs(distance); i = i+speed){
	    int final_i = distance < 0 ? -i : i;
	    maestro.setTarget(channel,from + final_i);
	    delay(SERVO_SLEEP);
	  }
	}

public:

	Puppeteer(){
		maestroSerial.begin(9600);
	}

	void reset_pose(){
	  maestro.setTarget(CHANNEL_ANKLE_ROLL,RESET_ANKLE_ROLL);
	  maestro.setTarget(CHANNEL_ANKLE_YAW,RESET_ANKLE_YAW);
	  maestro.setTarget(CHANNEL_TOE,RESET_TOE);
	  maestro.setTarget(CHANNEL_KNEE,RESET_KNEE);
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

	void lean_forward(){
		Instruction lean_forward[2] = {
			{CHANNEL_ANKLE_YAW, RESET_ANKLE_YAW, 6000},
			{CHANNEL_KNEE, RESET_KNEE, 5000}
		};

		Instruction lean_back[2] = {
			{CHANNEL_ANKLE_YAW, 6000, RESET_ANKLE_YAW},
			{CHANNEL_KNEE, 5000, RESET_KNEE}
		};
		
		Serial.println("about to bend");
		move_all_from_to(lean_forward, 2, 1000);

		Serial.println("about to straighten");
		move_all_from_to(lean_back, 2, 1000);
	}

	float stand(float yaw, float roll){
		float foo = RESET_ANKLE_ROLL + 1500 * roll;
		maestro.setTarget(CHANNEL_ANKLE_ROLL,foo);
		return foo;
	}
};

#endif