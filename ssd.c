#include "ssd.h"

extern unsigned int ssd;


void ssd_init() {
    bin_direction(port_A, 4, output);
    bin_direction(port_A, 5, output);
}


void seven_segment() {
    unsigned char a[10] = {63, 48, 91, 79, 102, 109, 125, 7, 127, 111};
    unsigned char h, d;
    h = ssd/10;
    d = ssd%10;
    bin_write(port_A, 4, 1);
    port_write(port_D,a[h] );
    __delay_ms (1);
    bin_write(port_A, 4, 0);
    bin_write(port_A, 5, 1);
    port_write(port_D, a[d]);
    __delay_ms (1);
    bin_write(port_A, 5, 0);

}
