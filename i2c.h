#ifndef i2c_H_INCLUDED
#define i2c_H_INCLUDED
#include "GPIO.h"
#include <pic16f877a.h>
void i2c_init();
void I2C_Start();
unsigned char I2C_read();
unsigned char I2c_write(unsigned char data);
void I2c_stop();
void EEPROM_W(char add,char data);
unsigned char EEPROM_R(char add);

#endif 