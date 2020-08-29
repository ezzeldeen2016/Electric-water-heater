#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED
#define port_A 0x05
#define port_B 0x06
#define port_C 0x07
#define port_D 0x08
#define port_E 0x09
#define input 1
#define output 0
void port_direction(char add , char state);
char port_read(char add);
void port_write(char add , char value);
void bin_direction(char add , char bin,char state);
char bin_read(char add , char bin);
void bin_write(char add , char bin, char data);
void bin_toggle(char add , char bin);

#endif