#include<msp430.h>
#include "app/led.h"
#include "drivers/io.h"
#include "drivers/io.h"
#include "drivers/mcu_init.h"
#include "drivers/led.h"
#include "common/assert_handler.h"

static void test_setup(void) {
    mcu_init();
} 

static void test_blink_led(void) {
    led_init();
}

int main(void) {
    test_blink_led();
    volatile unsigned int i;
   test_setup();
    led_state_e led_state = LED_STATE_OFF;

    while (1)
    {
        led_state = (led_state == LED_STATE_ON)? LED_STATE_OFF: LED_STATE_ON;
        led_set(LED_TEST, led_state);
        for ( i = 10000; i >0; i--);   // delay
        
    }
    
}