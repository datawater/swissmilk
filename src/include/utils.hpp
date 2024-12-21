#pragma once

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <optional>

#include "backtrace.hpp"

#ifdef __linux__

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif  // _GNU_SOURCE

#include <unistd.h>

#define __GET_THREAD_ID() gettid()

#else  // __linux__
#define __GET_THREAD_ID() -1
#endif  // else __linux__

#define SMATTR_PACKED __attribute__((__packed__))
#define SMATTR_ALLIGNED(x) __attribute__((aligned((x))))
#define SMATTR_ALWAYS_INLINE __attribute__((always_inline))
#define SMATTR_COLD __attribute__((cold))
#define SMATTR_CONST __attribute__((const))
#define SMATTR_HOT __attribute__((hot))
#define SMATTR_OPTIMIZE(x) __attribute__((optimize, (x)))
#define SMATTR_DEPRECATED __attribute__((deprecated))

#define SM_ERROR(...)                                                       \
    do {                                                                    \
        fprintf(stderr, "thread %d panicked at %s:%d\n", __GET_THREAD_ID(), \
                __FILE__, __LINE__);                                        \
        fprintf(stderr, __VA_ARGS__);                                       \
                                                                            \
        fputc('\n', stderr);                                                \
        print_backtrace();                                                  \
        fputc('\n', stderr);                                                \
        abort();                                                            \
    } while (0);

#define SM_TODO(...)                                                      \
    do {                                                                  \
        char* __va_args_str = (char*)malloc(sizeof(char) * 256);          \
        char* __error_str = (char*)malloc(sizeof(char) * 300);            \
        assert(__va_args_str != NULL && __error_str != NULL);             \
                                                                          \
        sprintf(__va_args_str, __VA_ARGS__);                              \
        sprintf(__error_str, "not yet implemented. %s\n", __va_args_str); \
                                                                          \
        SM_ERROR(__error_str);                                            \
    } while (0);

#define SM_DEFINE_GETTER(type, name) \
    type get_##name() const { return name; }

#define SM_DEFINE_GETTER_CONST_PTR(type, name) \
    const type *get_##name() const { return static_cast<const type *>(&name); }

#define SM_DEFINE_SETTER(type, name) \
    void set_##name(const type &value) { name = value; }

#define SM_DEFINE_GETTER_SETTER(type, name) \
    SM_DEFINE_GETTER(type, name)            \
    SM_DEFINE_SETTER(type, name)

typedef unsigned int uint;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;
typedef long double fld_t;

enum class ResultType { Ok, Error };

template <typename O, typename E>
class Result {
   private:
    ResultType type;
    std::optional<O> ok_value;
    std::optional<E> error;

   public:
    inline bool is_ok() { return this->type == ResultType::Ok; }
    inline bool is_err() { return this->type == ResultType::Error; }

    inline O unwrap() { return this->ok_value.value(); }
    inline O unwrap_or(O or_value) { return this->ok_value.value_or(or_value); }
    inline O unwrap_or_else(std::function<O(void)> func) {
        return this->ok_value.value_or(func());
    }
    inline O unwrap_error() { return this->error.value(); }
};