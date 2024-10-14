#include "include/backtrace.hpp"

#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cxxabi.h>
#include <memory>

// https://stackoverflow.com/a/62160937
auto cpp_demangle(const char *abiName) {
    int status;
    char *ret = abi::__cxa_demangle(abiName, 0 /* output buffer */, 0 /* length */, &status);

    auto deallocator = ( [](char *mem) { if (mem) free((void*)mem); } );

    if (status) {
        // 0: The demangling operation succeeded.
        // -1: A memory allocation failure occurred.
        // -2: mangled_name is not a valid name under the C++ ABI mangling rules.
        // -3: One of the arguments is invalid.
        std::unique_ptr<char, decltype(deallocator) > retval(nullptr, deallocator);
        return retval;
    }

    //
    // Create a unique pointer to take ownership of the returned string so it
    // is freed when that pointers goes out of scope
    //
    std::unique_ptr<char, decltype(deallocator) > retval(ret, deallocator);
    return retval;
}

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
        
        auto name_unique = cpp_demangle(sym);
        auto name_cstr = name_unique.get();

        if (name_cstr == nullptr)
            name_cstr = sym;

        printf("0x%lx: (%s+0x%lx)\n", pc, name_cstr, offset);
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

#if defined(USE_LIBUNWIND)
    print_backtrace_using_libunwind();
#endif  // defined(USE_LIBUNWIND)
}