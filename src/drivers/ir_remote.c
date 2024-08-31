#include "ir_remote.h"
#include <assert.h>
#include "../common/defines.h"
#include "../common/ring_buffer.h"
#include "../common/assert_handler.h"
#include <msp430.h>
#include <stdint.h>
#include "io.h"
#include <stdbool.h>

#ifndef DISABLE_IR_REMOTE

#define TICKS_PER_ms (SMCLK / TIMER_INPUT_DIVIDER_3 / 1000u)
#define TIMER_INTERRUPT_ms (1u)
#define TIMER_INTERRUPT_TICKS (TICKS_PER_ms * TIMER_INTERRUPT_ms)
static_assert(TIMER_INTERRUPT_TICKS <= 0xFFFF, "Ticks too large");
#define TIMER_TIMEOUT_ms (150u)

#define IR_CMD_BUFFER_ELEM_CNT (10u)
STATIC_RING_BUFFER(ir_cmd_buffer, IR_CMD_BUFFER_ELEM_CNT, uint8_t);

static uint8_t timer_ms = 0;
static uint16_t pulse_count = 0;

static union {
    struct
    {
        // cppcheck-suppress unusedStructMember
        uint8_t cmd_inverted;
        uint8_t cmd;
        // cppcheck-suppress unusedStructMember
        uint8_t addr_inverted;
        // cppcheck-suppress unusedStructMember
        uint8_t addr;
    } decoded;
    uint32_t raw;
} ir_message;

static void ir_timer_init(void)
{
    /* Configure timer to trigger interrupt after TIMER_INTERRUPT_TICKS
     * TASSEL_2: SMCLK
     * ID_3: Input divider 8 */
    TA1CTL = TASSEL_2 + ID_3;
    TA1CCR0 = TIMER_INTERRUPT_TICKS;
    TA1CCTL0 = CCIE; // enable the interrupt.
}

static void ir_timer_start(void)
{
    // MC_1: Count to CCR0
    TA1CTL = (TA1CTL & ~TIMER_MC_MASK) | MC_1 | TACLR;
    timer_ms = 0;
}

static void ir_timer_stop(void)
{
    // MC_0: Stop counter
    TA1CTL = (TA1CTL & ~TIMER_MC_MASK) | MC_0;
}

static inline bool is_valid_pulse(uint16_t pulse, uint8_t ms)
{
    // Roughly sanity check if pulse arrived within expected time
    if (pulse == 1) {
        return ms == 0;
    } else if (pulse == 2) {
        return ms < 10;
    } else if (3 <= pulse && pulse <= 34) {
        return ms < 5;
    } else if (pulse == 35) {
        return ms < 50;
    } else if (pulse == 36) {
        return ms < 5;
    } else if (pulse >= 37 && IS_ODD(pulse)) {
        return ms < 110;
    } else if (pulse >= 37) { // Even
        return ms < 5;
    } else {
        return false;
    }
}

// check if a bit is in bound of the message
static inline bool is_bit_pulse(uint16_t pulse)
{
    return 3 <= pulse && pulse <= 34;
}

// check if the message has been pulsed or the use is holding the button
static inline bool is_message_pulse(uint16_t pulse)
{
    return pulse == 34 || (pulse > 36 && IS_ODD(pulse));
}

static void isr_pulse(void)
{
    ir_timer_stop();
    pulse_count++;

    if (!is_valid_pulse(pulse_count, timer_ms)) {
        // Assume start of new message
        pulse_count = 1;
        ir_message.raw = 0;
    } else if (is_bit_pulse(pulse_count)) {
        ir_message.raw <<= 1; // shift raw 32 int to make room for the next bit
        ir_message.raw += (timer_ms >= 2) ? 1 : 0;
    }

    if (is_message_pulse(pulse_count)) {
        ring_buffer_put(&ir_cmd_buffer, &ir_message.decoded.cmd);
    }

    ir_timer_start();
}

INTERRUPT_FUNCTION(TIMER1_A0_VECTOR) isr_timer_a0(void)
{
    if (timer_ms < TIMER_TIMEOUT_ms) {
        timer_ms++;
    } else {
        ir_timer_stop();
        pulse_count = 0;
        ir_message.raw = 0;
        timer_ms = 0;
    }
}

#endif

ir_cmd_e ir_remote_get_cmd(void)
{
#ifndef DISABLE_IR_REMOTE
    io_disable_interrupt(IO_IR_REMOTE);
    ir_cmd_e cmd = IR_CMD_NONE;
    if (!ring_buffer_empty(&ir_cmd_buffer)) {
        ring_buffer_get(&ir_cmd_buffer, &cmd);
    }
    io_enable_interrupt(IO_IR_REMOTE);
    return cmd;
#else
    return IR_CMD_NONE;
#endif
}

void ir_remote_init(void)
{
#ifndef DISABLE_IR_REMOTE
    io_configure_interrupt(IO_IR_REMOTE, IO_TRIGGER_RISING, isr_pulse);
    io_enable_interrupt(IO_IR_REMOTE);
    ir_timer_init();
#endif
}