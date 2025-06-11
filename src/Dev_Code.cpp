


// This #include statement was automatically added by the Particle IDE.
#include "Particle.h"
#include "Smog_Dog_Sensors.h"
#include "Motion_Detect.h"

//Smog_Dog_Sensors Sensor;
Motion Accel_1;
Smog_Dog_Sensors Sensors;

void setup()
{

  Serial.begin(115200);
  delay(1000);
  Wire.begin();
  Sensors.SE55_Initalize();

 
}

void loop()
{
  Sensors.S55_Data();
  Serial.println(Sensors.ambientTemperature);
}


void tryMeFirst() {
	//File myFile;

	// Initialize the library
	//if (!sd.begin(chipSelect1, SD_SCK_MHZ(4))) {
		//Serial.println("failed to open card");
		//return;
	//}



  

	// open the file for write at end like the "Native SD library"
  /*
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
  */

}