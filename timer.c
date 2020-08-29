#include "timer.h"

extern unsigned char sec;
extern unsigned int counter,adc_value,ssd;
extern unsigned char i;

void timer_init() {
    OPTION_REG = 0b10010010;
    TMR0 = 6;
}


void __interrupt () timer() {
    if (INTCONbits.TMR0IF == 1) {
        if ((counter%100) ==0) {
            adc_value=adc();
            ssd=adc_value;
        }
        if(counter==1000)
        {
            counter=0;
            if(i==2)
            {
                sec++;
            }
            if(bin_read(port_C, 5) == 1)
            {
            bin_toggle(port_B , 7);
            }
        }
        counter++;
        TMR0 = 6;
        INTCONbits.TMR0IF = 0;
    }

}

