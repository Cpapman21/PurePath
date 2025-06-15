#include <Arduino.h>
#include <SensirionI2CSen5x.h>
#include "SparkFun_Ublox_Arduino_Library_183.h"
#include "Particle.h"
#include <Wire.h>


class Smog_Dog_Sensors {

    private:
        SensirionI2CSen5x sen5x;
        SFE_UBLOX_GPS myGPS;
        int I2C_Address = 0x62;
        int GPS_Address = 0x42;

    public:
        float massConcentrationPm1p0;
        float massConcentrationPm2p5;
        float massConcentrationPm4p0;
        float massConcentrationPm10p0;
        float ambientHumidity;
        float ambientTemperature;
        float vocIndex;
        float noxIndex;

        long latitude;
        long longitude;
        long altitude;
        byte SIV;


        void SE55_Serial_Number();
        void SE55_ModuleVersion();
        void S55_Data();
        void SE55_Initalize();

        void GPS_Initalize();
        void GPS_Data();
        
};