#include<msp430.h>
#include "app/led.h"
#include "drivers/io.h"

static void test_blink_led(void) {
    const struct  io_config led_config = 
    {
        /* data */
        .select = IO_SELECT_GPIO,
        .dir = IO_DIR_OUTPUT,
        .resistor = IO_RESISTOR_DISABLED,
        .out = IO_OUT_LOW

    };
    io_configure(IO_TEST_LED, &led_config);
}

int main(void) {
    test_blink_led();
    volatile unsigned int i;
    WDTCTL = WDTPW + WDTHOLD; // stop watchdog timer
    io_out_e out = IO_OUT_LOW;

    while (1)
    {
        out = (out == IO_OUT_LOW)? IO_OUT_HIGH: IO_OUT_LOW;
        io_set_out(IO_TEST_LED, out);
        for ( i = 10000; i >0; i--);   // delay
        
    }
    
}