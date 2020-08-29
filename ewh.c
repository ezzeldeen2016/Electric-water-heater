#include <pic16f877a.h>
#include "i2c.h"
#include "GPIO.h"
#include "adc.h"
#include "timer.h"
#include "ssd.h"

#define _XTAL_FREQ  8000000
//______________________________PIC16F877A Configuration Bit Settings______________________________
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <xc.h>
//__________________________________init functions____________________________________________
void ports_init();
void set_temp_mode();
void on_state();
void off_state();
void set_temp_mode();

//_______________________________________________________________________________________________
unsigned int temp_set,adc_value;
unsigned int ssd;
unsigned char i;// holds the current state
unsigned char sec;
unsigned int counter,adc_value;

int main() {
    //______________________________initialize for different modes_______________________________
    void (*p[3])(void);
    p[0] = off_state;
    p[1] = on_state;
    p[2] = set_temp_mode;
    //______________________________initialize the ports_________________________________________
    ports_init();
    //______________________________initialize for different modes_______________________________
    adc_init();
    ssd_init();
    bin_direction(port_B, 0, input ); //for turning on/off the electric water heater
    bin_direction(port_B, 1, input ); //for getting into set mode to set the temp and decreasing the set temperature 
    bin_direction(port_B, 2, input ); //for getting into set mode to set the temp and increasing the set temperature 
    bin_direction(port_B, 7, output); 
    bin_direction(port_C, 2,output); // pin connected to heater
    bin_direction(port_C , 5,output); // pin connected to fan
    port_direction(port_D, output);
    //______________________________initialize functions_______________________________
    timer_init();
    i2c_init();
    //_________________________get the temperature that is stored in eeprom____________
    temp_set=EEPROM_R(0x00);
    //_________________________________________________________________________________
    if(temp_set==0xff)
    {
        temp_set=60;
    }
    INTCON = 0b11100000;
    while (1) {
        (*p[i])();
        if (bin_read(port_B, 0) == 0) {
            while (bin_read(port_B, 0) == 0);
            if (i == 0) {
                i = 1;
            } else {
                i = 0;
            }
        }


    }

}

void ports_init() {
    port_write(port_A, 0x00);
    port_write(port_B, 0x00);
    port_write(port_C, 0x00);
    port_write(port_D, 0x00);
    port_write(port_E, 0x00);
}

void set_temp_mode() {
    ssd=temp_set;
    if(sec%2==0)
    {
        seven_segment();
    }
    else
    {
    bin_write(port_A, 4, 0);
    bin_write(port_A, 5, 0);
    port_write(port_D, 0x00);
    }
    if(bin_read(port_B, 2) == 0)
    {
        while(bin_read(port_B, 2) == 0);
        temp_set+=5;
        sec=0;
        if(temp_set>75)
        {
            temp_set=75;
        }
    }
    if(bin_read(port_B, 1) == 0)
    {
        while(bin_read(port_B, 1) == 0);
        temp_set-=5;
        sec=0;
        if(temp_set<35)
        {
            temp_set=35;
        }
    }
    if(sec==5)
    {
        EEPROM_W(0x00,temp_set);
        sec=0;
        i=1;
    }
}


void on_state() {
    seven_segment();
    if(adc_value <= (temp_set -5))
    {
        bin_write(port_C , 2, 0);
        bin_write(port_C , 5, 1);
    }
    else if(adc_value >= (temp_set +5))
    {
        bin_write(port_C , 2, 1);
        bin_write(port_C , 5, 0);
        bin_write(port_B , 7, 1);
    }
    if ((bin_read(port_B, 2) == 0) || (bin_read(port_B, 1) == 0)) {
        while ((bin_read(port_B, 2) == 0) || (bin_read(port_B, 1) == 0));
        i=2;
    }

}

void off_state() {
    bin_write(port_A, 4, 0);
    bin_write(port_A, 5, 0);
    port_write(port_D, 0x00);
    bin_write(port_C , 2, 0);
    bin_write(port_C , 5, 0);
}
