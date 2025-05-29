
#include "Motion_Detect.h"
#include "Adafruit_ADXL343.h"
#include "Particle.h"

uint32_t m_count = 0;
bool trigger = false;

void MC_Counter() {
    m_count++;
    trigger = true;
}

void Motion::Initalize(int I2C_add) {
    pinMode(Pwr_Enable,OUTPUT);
    pinMode(INPUT_PIN_INT1, INPUT);
    digitalWrite(Pwr_Enable,HIGH);
    attachInterrupt(digitalPinToInterrupt(INPUT_PIN_INT1), MC_Counter , RISING);
    Moving = false;
    delay(500);
    accel.begin(I2C_add);
    if(!(accel.begin())){
        while (1)
        {
            Serial.print("Accel Not Detected Wiring Wrong!");
        }
    }
    uint8_t powerCtl = accel.readRegister(REG_POWER_CTL);
    accel.writeRegister(REG_POWER_CTL, powerCtl & ~BIT_MEASURE);
  
    // Set range (optional, for accuracy vs. max range)
    accel.setRange(ADXL343_RANGE_4_G);
  
    // Set activity threshold (1 LSB = 62.5 mg)
    accel.writeRegister(REG_THRESH_ACT, ACTIVITY_THRESHOLD);
  
    // Enable AC-coupled activity detection on X, Y, and Z
    accel.writeRegister(REG_ACT_INACT_CTL, BIT_ACT_AC_XYZ);
  
    // Enable activity interrupt only
    accel.writeRegister(REG_INT_ENABLE, BIT_ACTIVITY_INT);
  
    // Map activity interrupt to INT1 (0 = INT1, 1 = INT2)
    accel.writeRegister(REG_INT_MAP, 0x00); // All interrupts to INT1
  
    // Enable measurement mode
    powerCtl = accel.readRegister(REG_POWER_CTL);
    accel.writeRegister(REG_POWER_CTL, powerCtl | BIT_MEASURE);
  
    //attachInterrupt(INPUT_PIN_INT1,Motion_Detect,RISING);
    Serial.println("Activity interrupt initialized with raw bit masks.");
}

void Motion::Set_ID(int ID) {
    Sensor_ID = ID;
}

void Motion::XYZ_Data() {
    sensors_event_t event;
    accel.getEvent(&event);
    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
}



bool Motion::Motion_Detect() {
    while (m_count < 100){
        if (trigger=true) {
            uint8_t int_source = accel.readRegister(REG_INT_SOURCE);
            if (int_source & 0x10) {
                Serial.println("Activity detected!");
                m_count++;
                Serial.println(m_count);
                trigger = false;
            }   
        }
        
        else
            Serial.print("Idle");
            Moving = false;
    }

    if(m_count == 100) {
        Serial.println("Ok we are moving! Lets start sending data");
        m_count = 0;
        trigger = false;
        Moving = true;
    }

    return Moving;
}
