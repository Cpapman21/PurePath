
#include "Motion_Detect.h"
#include "Adafruit_ADXL343.h"



void Motion::setRange(adxl34x_range_t range) {
    accel.setRange(range);
}
    
void Motion::setDataRate(adxl3xx_dataRate_t rate) {
    accel.setDataRate(rate);
}


void Motion::Initalize(int I2C_add) {
    accel.begin(I2C_add);
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

    return true;
}
