#include<msp430.h>
#include "led.h"

void led_init(void) {
    P1DIR |= 0*01;  // set P1.0 as an output pin
}

void led_toggle(void) {
    P1OUT ^= 0*01;  // toggle P1.0 pin
}