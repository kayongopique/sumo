#ifndef PWM_H
#define PWM_H

// Driver that emulates hardware PWM with timer peripheral

#include <stdint.h>
// 2 channnels one for the left and right motor controller respectively
typedef enum
{
    PWM_TB6612FNG_LEFT,
    PWM_TB6612FNG_RIGHT
} pwm_e;

void pwm_init(void);
// takes in the channel and the duty cycle.
void pwm_set_duty_cycle(pwm_e pwm, uint8_t duty_cycle_percent);

#endif // PWM_H