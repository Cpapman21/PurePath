#include "Smog_Dog_Sensors.h"



void Smog_Dog_Sensors::SE55_ModuleVersion() {
    uint16_t error;
    char errorMessage[256];

    unsigned char productName[32];
    uint8_t productNameSize = 32;

    error = sen5x.getProductName(productName, productNameSize);

    if (error) {
        Serial.print("Error trying to execute getProductName(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        Serial.print("ProductName:");
        Serial.println((char*)productName);
    }

    uint8_t firmwareMajor;
    uint8_t firmwareMinor;
    bool firmwareDebug;
    uint8_t hardwareMajor;
    uint8_t hardwareMinor;
    uint8_t protocolMajor;
    uint8_t protocolMinor;

    error = sen5x.getVersion(firmwareMajor, firmwareMinor, firmwareDebug,
                             hardwareMajor, hardwareMinor, protocolMajor,
                             protocolMinor);
    if (error) {
        Serial.print("Error trying to execute getVersion(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        Serial.print("Firmware: ");
        Serial.print(firmwareMajor);
        Serial.print(".");
        Serial.print(firmwareMinor);
        Serial.print(", ");

        Serial.print("Hardware: ");
        Serial.print(hardwareMajor);
        Serial.print(".");
        Serial.println(hardwareMinor);
    }
}

void Smog_Dog_Sensors::SE55_Serial_Number() {
    uint16_t error;
    char errorMessage[256];
    unsigned char serialNumber[32];
    uint8_t serialNumberSize = 32;

    error = sen5x.getSerialNumber(serialNumber, serialNumberSize);
    if (error) {
        Serial.print("Error trying to execute getSerialNumber(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        Serial.print("SerialNumber:");
        Serial.println((char*)serialNumber);
    }
}

void Smog_Dog_Sensors::SE55_Initalize() {
    sen5x.begin(Wire);
    uint16_t error;
    char errorMessage[256];
    error = sen5x.deviceReset();
    if (error) {
        Serial.print("Error trying to execute deviceReset(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }

        float tempOffset = 0.0;
    error = sen5x.setTemperatureOffsetSimple(tempOffset);
    if (error) {
        Serial.print("Error trying to execute setTemperatureOffsetSimple(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        Serial.print("Temperature Offset set to ");
        Serial.print(tempOffset);
        Serial.println(" deg. Celsius (SEN54/SEN55 only");
    }

    // Start Measurement
    error = sen5x.startMeasurement();
    if (error) {
        Serial.print("Error trying to execute startMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }

}

void Smog_Dog_Sensors::S55_Data() {
    uint16_t error;
    char errorMessage[256];
    // Read Measurement
    error = sen5x.readMeasuredValues(
        massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
        massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex,
        noxIndex);

    if (error) {
        Serial.print("Error trying to execute readMeasuredValues(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } 
    /*
    else {
        Serial.print("MassConcentrationPm1p0:");
        Serial.print(massConcentrationPm1p0);
        Serial.print("\t");
        Serial.print("MassConcentrationPm2p5:");
        Serial.print(massConcentrationPm2p5);
        Serial.print("\t");
        Serial.print("MassConcentrationPm4p0:");
        Serial.print(massConcentrationPm4p0);
        Serial.print("\t");
        Serial.print("MassConcentrationPm10p0:");
        Serial.print(massConcentrationPm10p0);
        Serial.print("\t");
        Serial.print("AmbientHumidity:");
        if (isnan(ambientHumidity)) {
            Serial.print("n/a");
        } else {
            Serial.print(ambientHumidity);
        }
        Serial.print("\t");
        Serial.print("AmbientTemperature:");
        if (isnan(ambientTemperature)) {
            Serial.print("n/a");
        } else {
            Serial.print(ambientTemperature);
        }
        Serial.print("\t");
        Serial.print("VocIndex:");
        if (isnan(vocIndex)) {
            Serial.print("n/a");
        } else {
            Serial.print(vocIndex);
        }
        Serial.print("\t");
        Serial.print("NoxIndex:");
        if (isnan(noxIndex)) {
            Serial.println("n/a");
        } else {
            Serial.println(noxIndex);
        }
    }
    */
}

void Smog_Dog_Sensors::ADC_Initalize() {
    if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
    //ads.setGain(ADS1015_REG_CONFIG_PGA_4_096V);
    //ads.setDataRate(ADS1015_REG_CONFIG_DR_128SPS);
    //ads.startADCReading(ADS1X15_REG_CONFIG_MUX_SINGLE_2, /*continuous=*/false);
}

void Smog_Dog_Sensors::NO2_Data() {

    // Placeholder for NO2 data retrieval logic
    // This function can be implemented to retrieve NO2 data from the sensor
   if (!ads.conversionComplete()) {
    return;
  }

  int16_t results = ads.getLastConversionResults();

  Serial.print("Differential: "); Serial.print(results); Serial.print("("); Serial.print(ads.computeVolts(results)); Serial.println("V)");

  // Start another conversion.
  ads.startADCReading(ADS1X15_REG_CONFIG_MUX_SINGLE_2, /*continuous=*/false);

}

void Smog_Dog_Sensors::CO_Data() {

    // Placeholder for PM data retrieval logic
    // This function can be implemented to retrieve PM data from the sensor
    Serial.println("CO Data retrieval not implemented yet.");

}

void Smog_Dog_Sensors::O3_Data() {

    // Placeholder for PM data retrieval logic
    // This function can be implemented to retrieve PM data from the sensor
    Serial.println("CO Data retrieval not implemented yet.");

}

void Smog_Dog_Sensors::H2S_Data() {

    // Placeholder for PM data retrieval logic
    // This function can be implemented to retrieve PM data from the sensor
    Serial.println("H2S Data retrieval not implemented yet.");

}

void Smog_Dog_Sensors::GPS_Initalize () {

    if (myGPS.begin() == false) //Connect to the Ublox module using Wire port
  {
    Serial.println(F("Ublox GPS not detected at default I2C address. Please check wiring. Freezing."));
    while (1){
        Serial.print("Cant Connect");
        delay(1000);
    }
  }

  myGPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
}

void Smog_Dog_Sensors::GPS_Data() {

    latitude = myGPS.getLatitude();
    //Serial.print(F("Lat: "));
    //Serial.print(latitude);

    longitude = myGPS.getLongitude();
    //Serial.print(F(" Long: "));
    //Serial.print(longitude);
    //Serial.print(F(" (degrees * 10^-7)"));

    altitude = myGPS.getAltitude();
    //Serial.print(F(" Alt: "));
    //Serial.print(altitude);
    //Serial.print(F(" (mm)"));

    SIV = myGPS.getSIV();
    //Serial.print(F(" SIV: "));
    //Serial.print(SIV);

}
