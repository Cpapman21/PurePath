


// This #include statement was automatically added by the Particle IDE.
#include "Particle.h"
#include "Smog_Dog_Sensors.h"
#include "Motion_Detect.h"
#include "SdFat.h"
#include "stdio.h"
#include <chrono>


SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);
SerialLogHandler logHandler(LOG_LEVEL_INFO);


Motion Accel_1;
Motion* Accel_1_P = &Accel_1;
Smog_Dog_Sensors  Sensors;
Smog_Dog_Sensors* Sensors_P = &Sensors;

void Motor_Enable();

enum State {
    STATE_WAIT_CONNECTED = 0,
    STATE_PUBLISH,
    STATE_PUBLISH_WAIT,
    STATE_SLEEP,
    Moving
};

State state;

SdFat sd;
//Adafruit_ADS1015 ads;
String payload;
//void tryMeFirst();
unsigned long stateTime;
unsigned long lastCheck = 0;          // Timer for IDLE checks
unsigned long lastPublish = 0;        // Timer for data publish
const unsigned long idleInterval = 200;   // 200ms check interval
const unsigned long publishInterval = 1000; // 1 second for publish

void setup()
{

  Serial.begin(115200);
  Wire.begin();
  pinMode(D2,OUTPUT);
  digitalWrite(D2,LOW);
  delay(500);
  //Sensors.SE55_Initalize();
  //Sensors.GPS_Initalize();
  //Accel_1.Set_ID(12345);
  //Accel_1.Initalize(0x53);
  String name("Smog Dog");
  state = STATE_WAIT_CONNECTED;
  Particle.connect();
  m_count = 0;
  stateTime = millis();
  Serial.print("Starting!");
}

void loop()
{
  switch (state){

  case STATE_WAIT_CONNECTED: // Idle State
    //Accel_1.Motion_Detect();
    if(m_count < 100) {
      state = STATE_WAIT_CONNECTED;
      m_count += 1;
      delay(250);
    }
    else if(m_count >= 100) {
      state = STATE_PUBLISH;
      m_count = 0; // Reset the counter
    }
    break;
  case STATE_PUBLISH : // Moving State

    digitalWrite(D2, HIGH);
    delay(250);
    digitalWrite(D2, LOW);
    delay(250);
   
    //Sensors.S55_Data();
    //Sensors.GPS_Data();

    payload = String::format("{\"temp\":%.1f,\"rh\":%.1f,\"ln\":%ld,\"la\":%ld,\"al\":%ld}", 
    23.4 , 
    69.60 , 
    234.2, 
    360.0, 
    215.5
      );

    Particle.publish("Test_Load",payload);
    delay(1000);
    state = STATE_PUBLISH;
    break;

  default:
    state = STATE_WAIT_CONNECTED; 
    break;
 
  }

}

/*
void tryMeFirst() {
	File myFile;

	// Initialize the library
	if (!sd.begin(chipSelect1, SD_SCK_MHZ(4))) {
		Serial.println("failed to open card");
		return;
	}

	// open the file for write at end like the "Native SD library"
  
	if (!myFile.open("test.txt", O_RDWR | O_CREAT | O_AT_END)) {
		Serial.println("opening test.txt for write failed");
		return;
	}
	// if the file opened okay, write to it:
	Serial.print("Writing to test.txt...");
	myFile.println("testing 1, 2, 3.");
	myFile.printf("fileSize: %d\n", myFile.fileSize());

	// close the file:
	myFile.close();
	Serial.println("done.");

	// re-open the file for reading:
	if (!myFile.open("test.txt", O_READ)) {
		Serial.println("opening test.txt for read failed");
		return;
	}
	Serial.println("test.txt content:");

	// read from the file until there's nothing else in it:
	int data;
	while ((data = myFile.read()) >= 0) {
		Serial.write(data);
	}
	// close the file:
	myFile.close();
  
};
*/
