#pragma once

#ifdef __has_include

#if __has_include(<libunwind.h>)  // __has_include(<execinfo.h>)
#define HAS_LIBUNWIND 1

#else  // __has_include(<libunwind.h>)

#define NO_BACKTRACE
#warning "No backtrace printing is available. Install libunwind"

#endif  // NO_BACKTRACE
#endif  // __has_include

#if defined(HAS_LIBUNWIND)

#define USE_LIBUNWIND
#define UNW_LOCAL_ONLY
#include <libunwind.h>

#endif  // defined(HAS_LIBUNWIND)

void print_backtrace(void);