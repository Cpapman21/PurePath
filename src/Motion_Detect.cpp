
#include "Motion_Detect.h"
#include "Adafruit_ADXL343.h"
#include "Particle.h"

int Motion_Count;

void Motion::Initalize(int I2C_add) {
    pinMode(Pwr_Enable,OUTPUT);
    pinMode(INPUT_PIN_INT1, INPUT);
    digitalWrite(Pwr_Enable,HIGH);
    Motion_Count = 0;
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



void Motion::Motion_Detect() {
    int State_Bit;
    while (Motion_Count < 100){
        if (digitalRead(INPUT_PIN_INT1 ) == HIGH) {
            uint8_t int_source = accel.readRegister(REG_INT_SOURCE);
            if (int_source & 0x10) {
                Serial.println("Activity detected!");
                Motion_Count++;
                Serial.println(Motion_Count);
                delay(100);
            }   
        }
        
        else
            Serial.print("Idle");
            delay(100);
    }

    if(Motion_Count == 100) {
        Serial.println("Ok we are moving! Lets start sending data");
        Motion_Count = 0;
        Moving = true;
    }


}