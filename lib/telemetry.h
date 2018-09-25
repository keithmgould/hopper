#ifndef __LEG_TELEMETRY__
#define __LEG_TELEMETRY__

#include <SoftwareSerial.h>

SoftwareSerial mySerial(RX_FROM_CNC, TX_TO_CNC); // RX, TX

// singleton
class Telemetry{
	private:
		

		static Telemetry* instance;
		Telemetry();

		void init(){
			mySerial.begin(115200);
		}

	public:

		SoftwareSerial serial(){
			return mySerial;
		}

		static Telemetry* getInstance(){
			if (instance == 0)
	    {
	        instance = new Telemetry();
	        instance->init();
	    }

	    return instance;
		}
};

Telemetry* Telemetry::instance = 0;



#endif