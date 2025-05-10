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

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);
//Motion Accel1;


const unsigned int BATTERY_CAPACITY = 850; // e.g. 850mAh battery

void setupBQ27441(void)
{
  // Use lipo.begin() to initialize the BQ27441-G1A and confirm that it's
  // connected and communicating.
  if (!lipo.begin()) // begin() will return true if communication is successful
  {
	// If communication fails, print an error message and loop forever.
    Serial.println("Error: Unable to communicate with BQ27441.");
    Serial.println("  Check wiring and try again.");
    Serial.println("  (Battery must be plugged into Battery Babysitter!)");
    while (1) ;
  }
  Serial.println("Connected to BQ27441!");
  
  // Uset lipo.setCapacity(BATTERY_CAPACITY) to set the design capacity
  // of your battery.
  lipo.setCapacity(BATTERY_CAPACITY);
}

int printBatteryStats()
{
  // Read battery stats from the BQ27441-G1A
  unsigned int soc = lipo.soc();  // Read state-of-charge (%)
  unsigned int volts = lipo.voltage(); // Read battery voltage (mV)
  int current = lipo.current(AVG); // Read average current (mA)
  unsigned int fullCapacity = lipo.capacity(FULL); // Read full capacity (mAh)
  unsigned int capacity = lipo.capacity(REMAIN); // Read remaining capacity (mAh)
  int power = lipo.power(); // Read average power draw (mW)
  int health = lipo.soh(); // Read state-of-health (%)

  // Now print out those values:
  String toPrint = String(soc) + "% | ";
  toPrint += String(volts) + " mV | ";
  toPrint += String(current) + " mA | ";
  toPrint += String(capacity) + " / ";
  toPrint += String(fullCapacity) + " mAh | ";
  toPrint += String(power) + " mW | ";
  toPrint += String(health) + "%";
  
  Serial.println(toPrint);
  return volts;
}

void printCurrentTime();

Motion Accel1;
PCF85063A global_timer;


void setup(void)
{
  Serial.begin(9600);
  //setupBQ27441();
  Accel1.Set_ID(12345);
  Accel1.Initalize(0x53);
  delay(2000);
  //global_timer.setTime(4,25,24);
  //global_timer.setDate(0,14,5,2025);
  //printCurrentTime();
  Serial.print("Begin Program");
}

void loop(void)
{
  Accel1.Motion_Detect();
  delay(100);

}

void printCurrentTime() {
  switch( global_timer.getWeekday() )
  {
    case 0:
      Serial.print("Sunday , ");
      break;
    case 1:
      Serial.print("Monday , ");
      break;
    case 2:
      Serial.print("Tuesday , ");
      break;
    case 3:
      Serial.print("Wednesday , ");
      break;
    case 4:
      Serial.print("Thursday , ");
      break;
    case 5:
      Serial.print("Friday , ");
      break;
    case 6:
      Serial.print("Saturday , ");
      break;
  }

  Serial.print(global_timer.getDay()); Serial.print(".");
  Serial.print(global_timer.getMonth()); Serial.print(".");
  Serial.print(global_timer.getYear()); Serial.print(". ");
  Serial.print(global_timer.getHour()); Serial.print(":");
  Serial.print(global_timer.getMinute()); Serial.print(":");
  Serial.println(global_timer.getSecond());
}