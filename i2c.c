#include "i2c.h"
#include "GPIO.h"
void i2c_init()
{
  SSPCON = 0b00101000;
  SSPCON2 = 0b00000000;
  SSPADD = 4;
  SSPSTAT = 0b00000000;
  bin_direction(port_C , 3, input);
  bin_direction(port_C , 4, input);
}


void I2C_Start()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
  SEN = 1;
}

unsigned char I2C_read()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
  RCEN = 1;
  while(!SSPIF);
  SSPIF = 0;
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
  return SSPBUF;
}

unsigned char I2c_write(unsigned char data)
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
  SSPBUF = data;
  while(!SSPIF);
  SSPIF = 0;
  return SSPCON2bits.ACKSTAT;
}

void I2c_stop()
{
while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
PEN = 1;
}

void EEPROM_W(char add,char data)
{
    I2C_Start();
    while(I2c_write(0xA0));
    while(I2c_write(add));
    I2c_write(data);
    I2c_stop();
}


unsigned char EEPROM_R(char add)
{
    unsigned char data;
    I2C_Start();
    while(I2c_write(0xA0));
    while(I2c_write(add));
    I2C_Start();
    while(I2c_write(0xA1));
    data=I2C_read();
    I2c_stop();
    return data;
}

