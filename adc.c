#include "adc.h"
unsigned int arr[10]={0};
char j=0;
void adc_init() {
    bin_direction(port_A, 2, input);
    ADCON0 = 0b00010000;
    ADCON1 = 0b10000010;
}

int adc() {
    unsigned char z;
    unsigned int d,t;
    ADCON0 |= 0b00000001;
    __delay_ms (2);
    ADCON0 |= 0b00000100;
    while (ADCON0bits.GO_DONE == 1);
    d = ((ADRESH << 8) | ADRESL)/ 2;
    arr[j]=d;
    j++;
    if(j==10)
    {
        j=0;
    }
    t=0;
    for(z=0;z<10;z++)
    {
        t+=arr[z];
    }
    d=t/10;
    return d;
}
