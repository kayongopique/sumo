#ifndef ASSERT_HANDLER_H

#include <stdint.h>

#define ASSERT(expression)                                                                         \
    do {                                                                                           \
        if (!(expression)) {                                                                       \
           uint16_t pc;                                                                           \
            asm volatile("mov pc, %0" : "=r"(pc));                                                 \
            assert_handler(pc);                                                                     \
        }                                                                                          \
    } while (0)
    
// TODO: Decide what this should do
#define ASSERT_INTERRUPT(expression)                                                               \
    do {                                                                                           \
        if (!(expression)) {                                                                       \
            while (1) { }                                                                          \
        }                                                                                          \
    } while (0)

void assert_handler(uint16_t program_counter);
#endif