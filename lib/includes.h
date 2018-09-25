#ifndef __LEG_INCLUDES__
#define __LEG_INCLUDES__

#include <StandardCplusplus.h>
#include <SoftwareSerial.h>
#include "./constants.h"
SoftwareSerial mySerial(RX_FROM_CNC, TX_TO_CNC); // RX, TX
#include "./puppeteer.h"
#include "./averager.h"
#include "./imu.h"

#endif