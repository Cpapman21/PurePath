#include "Adafruit_ADXL343.h"
#include "Adafruit_Sensor.h"


#define ACTIVITY_THRESHOLD 50  // 50 * 62.5mg = 3.125g

// --- Register Addresses ---
#define REG_THRESH_ACT      0x24  // Activity threshold
#define REG_ACT_INACT_CTL   0x27  // Axis enable + AC/DC coupling
#define REG_INT_ENABLE      0x2E  // Which interrupts to enable
#define REG_INT_MAP         0x2F  // Map interrupts to INT1 or INT2
#define REG_INT_SOURCE      0x30  // Which interrupt fired
#define REG_POWER_CTL       0x2D  // Power settings

// --- Bit Masks ---
#define BIT_ACTIVITY_INT    0x10  // Bit 4: Activity interrupt enable/status
#define BIT_MEASURE         0x08  // Bit 3: Enable measurement mode
#define BIT_ACT_AC_XYZ      0x70  // Bits 6–4: Enable AC-coupled activity detect on X, Y, Z

const int Pwr_Enable = D7;
const int INPUT_PIN_INT1 = D6;
const int INPUT_PIN_INT2 = D5;       // Connect this to INT1 or INT2
extern uint32_t m_count;
extern bool trigger;

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
        bool Moving;
        void (*handle)();
};


void MC_Counter();