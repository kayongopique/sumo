#include<msp430.h>
#include "defines.h"
#include "assert_handler.h"
#include <stdint.h>

/* The TI compiler provides intrinsic support for calling a specific opcode, which means
 * you can write __op_code(0x4343) to trigger a software breakpoint (when LAUNCHPAD FET
 * debugger is attached). MSP430-GCC does not have this intrinsic, but 0x4343 corresponds
 * to assembly instruction "CLR.B R3". */
#define BREAKPOINT __asm volatile("CLR.B R3");


#define GPIO_OUTPUT_LOW(port, bit)                                                                 \
    do {                                                                                           \
        P##port##SEL &= ~(BIT##bit);                                                               \
        P##port##SEL2 &= ~(BIT##bit);                                                              \
        P##port##DIR |= BIT##bit;                                                                  \
        P##port##REN &= ~(BIT##bit);                                                               \
        P##port##OUT &= ~(BIT##bit);                                                               \
    } while (0)                                                                       

static void assert_blink_led(void)
{
    GPIO_OUTPUT_LOW(2, 6); // Test LED (Nsumo)
    while (1) {
        // Blink LED on both targets in case the wrong target was flashed
        P2OUT ^= BIT6;
        BUSY_WAIT_ms(250);
    };
}

/* Minimize code dependency in this function to reduce the risk of accidently calling
 * a function with an assert in it, which would cause the assert_handler to be called
 * recursively until stack overflow. */
void assert_handler(uint16_t program_counter)
{
    BREAKPOINT
    assert_blink_led();
    UNUSED(program_counter);
}