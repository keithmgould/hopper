#ifndef __LEG_IMU__
#define __LEG_IMU__

#include <Adafruit_Sensor.h>            // IMU
#include <Adafruit_BNO055.h>            // IMU
#include <Wire.h>                       // I2C for IMU

/*
    The Inertial Measurement Unit (IMU) reads from (currently) the BNO055.
    We might want to abstract away the specific chip at a later date. For now
    this class is simply a convenience wrapper for the BNO055 IMU.

    The readouts involve yaw, Leg's angle from "balanced," and 
    yawDot, which is the rate of change of yaw. Also roll and rollDot.

    yaw and roll are produced via black-box IMU magic, while yawDot 
    and rollDot are produced only via the IMU's gyrometer.
*/
class Imu{
  private:

  Adafruit_BNO055 bno = Adafruit_BNO055(55, 40);
  float yawOffset, yaw, yawDot;
  float rollOffset, roll, rollDot;
  Averager yawDotData = Averager(5);

  imu::Vector<3> eulerDegrees;
  imu::Vector<3> gyr;

  void fetchFromImu(){
    eulerDegrees = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  }

  // in radians
  float rawYaw() {
    return 0.0174533 * eulerDegrees.z(); // degrees to radians;
  }

  // in radians
  float rawRoll() {
    return 0.0174533 * eulerDegrees.y(); // degrees to radians;
  }

  // in radians/sec
  // float rawYawDot() {
  //   gyr = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  //   return -gyr.x();
  // }

  public:

  Imu(){
    yawOffset = YAW_OFFSET;
    rollOffset = ROLL_OFFSET;

    yaw = yawDot = 0;
    roll = rollDot = 0;
  }

  void setup(){
  //Check to see if the Inertial Sensor is wired correctly and functioning normally
    Serial.print("Initializing IMU...");
    if (!bno.begin(bno.OPERATION_MODE_IMUPLUS)) {
      Serial.println("Inertial Sensor failed, or not present");
    }
    bno.setExtCrystalUse(true);
    // bno.setAxisRemap();
    // bno.setAxisSign();
    Serial.println("Done!");
  }

  // void pushyawDotData(){
  //   yawDotData.push(rawYawDot());
  // }

  float getYaw(){ return yaw; }
  // float getYawDot(){ return yawDot; }
  // float getYawOffset(){ return yawOffset; }

  float getRoll(){ return roll; }
  // float getRollDot(){ return rollDot; }
  // float getRollOffset(){ return rollOffset; }

  bool isEmergency(){
    return fabs(eulerDegrees.z()) > 30 || fabs(eulerDegrees.y()) > 5;
  }

  // Due to micro leveling imperfections, the IMU is not perfectly level when Leg
  // is balanced. This offset allows software to account for this and update when
  // necessary.
  void setYawOffset(float newOffset){ yawOffset = newOffset; }
  void setRollOffset(float newOffset){ rollOffset = newOffset; }

  // calculates and stores yaw and yawDot.
  void update(){
    fetchFromImu();
    yaw = rawYaw() + yawOffset;
    roll = rawRoll() + rollOffset;
    // yawDot = yawDotData.computeAverage();
  }
};

#endif
