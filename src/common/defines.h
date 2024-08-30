#ifndef DEFINES_H
#define DEFINES_H

#define UNUSED(x) (void)(x)
#define SUPPRESS_UNUSED __attribute__((unused))
#define INTERRUPT_FUNCTION(vector) void __attribute__((interrupt(vector)))

#define MODULO_2(x) (x & 1)
#define IS_ODD(x) MODULO_2(x)


#define CYCLES_1MHZ (1000000u)
#define CYCLES_16MHZ (16u * CYCLES_1MHZ)
#define CYCLES_PER_MS (CYCLES_16MHZ / 1000u)
#define ms_TO_CYCLES(ms) (CYCLES_PER_MS * ms)
#define BUSY_WAIT_ms(ms) (__delay_cycles(ms_TO_CYCLES(ms)))

#define MCLK CYCLES_16MHZ
#define SMCLK MCLK

#define TIMER_INPUT_DIVIDER_3 (8u)
#define TIMER_MC_MASK (0x0030) // used to clear the MC register 

#endif