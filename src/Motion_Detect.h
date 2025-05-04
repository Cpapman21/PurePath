#include "Adafruit_ADXL343.h"
#include "Adafruit_Sensor.h"


class Motion {
    private:
        Adafruit_ADXL343 accel = Adafruit_ADXL343(Sensor_ID,&Wire);
        int32_t Sensor_ID;
    public:
        void setRange(adxl34x_range_t range);
        void Set_ID(int ID);
        void setDataRate(adxl3xx_dataRate_t rate);
        void Initalize(int I2C_add);
        void XYZ_Data();
        bool Motion_Detect();
    };
