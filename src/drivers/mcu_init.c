#include<msp430.h>
#include "mcu_init.h"

static inline void watchdog_setup(void)
{
    // Stop watchdog
    WDTCTL = WDTPW + WDTHOLD;

}

void mcu_init(void)
{
    // Must stop and configure watchdog before anything else
    watchdog_setup();
}