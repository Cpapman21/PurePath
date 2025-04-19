#include <Wire.h>
#include <limits.h>
#include "Adafruit_ADXL343.h"



/** Interrupt service routine for INT1 events. */
void int1_isr(void);


/** Interrupt service routine for INT2 events. */
void int2_isr(void);


/** Configures the HW interrupts on the ADXL343 and the target MCU. */
void config_interrupts(void);

