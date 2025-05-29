/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "Adafruit_ADXL343.h"
#include "Adafruit_MPL3115A2.h"
#include "Adafruit_Sensor.h"
#include "PCF85063A.h"
#include <Adafruit_BusIO_Register.h>
#include "DFRobot_SHT20.h"
#include "SensirionI2CSen5x.h"
#include "SparkFunBQ27441.h"
#include "BQ27441_Definitions.h"
#include "Motion_Detect.h"
#include "SparkFun_u-blox_GNSS_Arduino_Library.h"
#include <Wire.h> //Needed for I2C to GPS

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SFE_UBLOX_GNSS Test_GPS;
//Motion Accel1;
const unsigned int BATTERY_CAPACITY = 850; // e.g. 850mAh battery
long lastTime = 0; //Tracks the passing of 2000ms (2 seconds)

Motion Accel1;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  Serial.println("Initializing GPS...");

  if (Test_GPS.begin() == false) {
    Serial.println("GNSS not detected. Check wiring.");
  }

  Test_GPS.setI2COutput(COM_TYPE_UBX); // Use UBX binary protocol
  Test_GPS.setNavigationFrequency(1); // 1Hz update rate

  Serial.println("GPS Initialized.");
}

void loop() {
  // Update location data
  long latitude = Test_GPS.getLatitude();
  long longitude = Test_GPS.getLongitude();
  int32_t altitude = Test_GPS.getAltitude();
  uint8_t sats = Test_GPS.getSIV(); // Satellites in view

  Serial.print("Lat: ");
  Serial.print(latitude / 10000000.0, 7);
  Serial.print(", Lon: ");
  Serial.print(longitude / 10000000.0, 7);
  Serial.print(", Alt: ");
  Serial.print(altitude / 1000.0);
  Serial.print(" m, Sats: ");
  Serial.println(sats);
  Serial.print("FUCK");

  delay(1000);
}

