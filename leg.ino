#include "./lib/includes.h"

Puppeteer puppet;
Imu my_imu;

String buildTelemetry(){
  String log = String(my_imu.getYaw(),4);
  log += "," + String(my_imu.getRoll(),4);
  return log;
}

void sendTelemetry(){
  String log = buildTelemetry();
  mySerial.println(log);
}

void setup()
{
  mySerial.begin(115200);
  my_imu.setup();
  puppet.reset_pose();
}

float foo;
void loop(){
  my_imu.update();
  puppet.reset_pose();
  sendTelemetry();
  // foo = puppet.stand(my_imu.getYaw(), my_imu.getRoll());
  // telemetrySerial.println(foo);
//  puppet.lean_forward();
  delay(15);
}
