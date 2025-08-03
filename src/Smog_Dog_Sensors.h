#include <Arduino.h>
#include <SensirionI2CSen5x.h>
#include "SparkFun_Ublox_Arduino_Library_183.h"
#include "Adafruit_ADS1X15.h"
#include "Particle.h"
#include <Wire.h>


class Smog_Dog_Sensors {

    private:
        SensirionI2CSen5x sen5x;
        SFE_UBLOX_GPS myGPS;
        Adafruit_ADS1015 ads;
        int I2C_Address = 0x62;
        int GPS_Address = 0x42;
        int ADC_Address = 0x48;
        //int Interanl_Temp_Address = A7; // Internal temperature sensor pin

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

        void ADC_Initalize();
        void NO2_Data();
        void CO_Data();
        void O3_Data();
        void H2S_Data();

};