


// This #include statement was automatically added by the Particle IDE.
#include "Particle.h"
#include "Smog_Dog_Sensors.h"
#include "Motion_Detect.h"
#include "SdFat.h"
#include "stdio.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);


Motion Accel_1;
Smog_Dog_Sensors  Sensors;
Smog_Dog_Sensors* Sensors_P = &Sensors;

SdFat sd;
int chipSelect1 = A5;
//void tryMeFirst();


void setup()
{

  Serial.begin(115200);
  delay(1000);
  Wire.begin();
  pinMode(D3,OUTPUT);
  digitalWrite(D3,HIGH);
  //tryMeFirst();
  Sensors.SE55_Initalize();
  Sensors.GPS_Initalize();
  String name("Smog Dog");
}

void loop()
{
  Sensors.S55_Data();
  Sensors.GPS_Data();
  String payload = String::format("{\"temp\":%.1f,\"rh\":%.1f}", Sensors_P ->ambientTemperature , Sensors_P->ambientHumidity );
  Particle.publish("Test Load",payload);
  delay(2000);
  
}


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
  

}