#pragma once

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <optional>

#define SMATTR_PACKED __attribute__((__packed__))
#define SMATTR_ALLIGNED(x) __attribute__((aligned((x))))
#define SMATTR_ALWAYS_INLINE __attribute__((always_inline))
#define SMATTR_COLD __attribute__((cold))
#define SMATTR_CONST __attribute__((const))
#define SMATTR_HOT __attribute__((hot))
#define SMATTR_OPTIMIZE(x) __attribute__((optimize, (x)))
#define SMATTR_DEPRECATED __attribute__((deprecated))

#define SM_ERROR(...)                 \
    do {                              \
        fprintf(stderr, __VA_ARGS__); \
        abort();                      \
    } while (0);

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

#if __SIZEOF_LONG_DOUBLE__ == 8
typedef long double f64;
#elif __SIZEOF_LONG_DOUBLE__ == 10
typedef long double f80;
#elif __SIZEOF_LONG_DOUBLE__ == 16
typedef long double f128;
#else
#error "Unsupported size of long double"
#endif

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