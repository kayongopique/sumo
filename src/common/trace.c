#ifndef DISABLE_TRACE

#include "trace.h"
#include "assert_handler.h"
#include <stdbool.h>
#include "../drivers/uart.h"
#include "../../external/printf/printf.h"
#include <stdarg.h>

static bool initialized = false;
void trace_init(void)
{
    ASSERT(!initialized);
    uart_init();
    initialized = true;
}
// call function after uart init
void trace(const char *format, ...)
{
    ASSERT(initialized);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

#endif // DISABLE_TRACE