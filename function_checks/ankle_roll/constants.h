#ifndef __LEG_CONSTANTS__
#define __LEG_CONSTANTS__

// IMU
constexpr float YAW_OFFSET = 0.0; 	// due to minorly non-level IMU
constexpr float ROLL_OFFSET = 0.0; 	// due to minorly non-level IMU

// PINOUTS
constexpr int RX_FROM_MAESTRO = 6;	// to Maestro TX
constexpr int TX_TO_MAESTRO = 7; 		// to Maestro RX
constexpr int RX_FROM_CNC = 8;			// to Bluetooth TX
constexpr int TX_TO_CNC = 9; 				// to Bluetooth RX

// SERVO CHANNELS
constexpr int CHANNEL_TOE = 0;
constexpr int CHANNEL_ANKLE_ROLL = 1;
constexpr int CHANNEL_ANKLE_YAW = 3;
constexpr int CHANNEL_KNEE = 2;


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
constexpr int RESET_ANKLE_YAW = 3000;
constexpr int RESET_ANKLE_ROLL = (LIMIT_ANKLE_ROLL_LEFT + LIMIT_ANKLE_ROLL_RIGHT) / 2;
constexpr int RESET_KNEE = LIMIT_KNEE_STRAIGHT;
constexpr int RESET_TOE = LIMIT_TOE_STRAIGHT;

// DELAY BETWEEN SERVO COMMANDS
constexpr int SERVO_SLEEP = 15;

#endif