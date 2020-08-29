#include "GPIO.h"

void port_direction(char add , char state)
{
    if(state==output)
        *((volatile unsigned char*)(add|0x80))=0x00;
    else
        *((volatile unsigned char*)(add|0x80))=0xff;
}

char port_read(char add)
{
	char data;
	data =*((volatile unsigned char*)(add));
    return data;
}

void port_write(char add , char value)
{
    *((volatile unsigned char*)(add))=value;
}
//________________________________________________________________

void bin_direction(char add , char bin, char state)
{
    if(state==input)
        *((volatile unsigned char*)(add|0x80))|=(1<<bin);
    else
        *((volatile unsigned char*)(add|0x80))&=~(1<<bin);
}

char bin_read(char add , char bin)
{
	unsigned char bin_value;
	bin_value =(*(volatile unsigned char *)(add)) & (1<<bin) ;
	if (bin_value==0) return 0 ;
	else return 1 ;
}

void bin_write(char add , char bin, char data)
{
    if(data)
    *((volatile unsigned char*)(add))|=(1<<bin);
    else
    *((volatile unsigned char*)(add))&=~(1<<bin);
}

void bin_toggle(char add , char bin)
{
    *((volatile unsigned char*)(add))^=(1<<bin);
}




