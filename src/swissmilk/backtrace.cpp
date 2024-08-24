#include "include/backtrace.hpp"

#include <unistd.h>

#include <cstdio>
#include <cstdlib>

#ifdef USE_LIBUNWIND
void print_backtrace_using_libunwind(void) {
    unw_cursor_t cursor;
    unw_context_t context;
    unw_word_t offset, pc;
    char sym[256];

    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    printf("Stack trace (libunwind):\n");

    while (unw_step(&cursor) > 0) {
        unw_get_reg(&cursor, UNW_REG_IP, &pc);
        sym[0] = '\0';

        unw_get_proc_name(&cursor, sym, sizeof(sym), &offset);
        printf("0x%lx: (%s+0x%lx)\n", pc, sym, offset);
    }
}
#endif  // USE_LIBUNWIND

void print_backtrace(void) {
#ifndef NO_BACKTRACE
    if (getenv("SM_BACKTRACE") == NULL) {
        fprintf(stderr,
                "note: run with `SM_BACKTRACE=1` environment variable to "
                "display a backtrace\n");

        return;
    }
#endif

#if defined(USE_LIBUNWIND)  // USE_EXECINFO
    print_backtrace_using_libunwind();
#endif  // defined(USE_LIBUNWIND)
}