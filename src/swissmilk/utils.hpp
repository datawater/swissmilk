#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstdint>

#define SMATTR_PACKED __attribute__((__packed__))
#define SMATTR_ALLIGNED(x) __attribute__((aligned ((x))))
#define SMATTR_ALWAYS_INLINE __attribute__((always_inline))
#define SMATTR_COLD __attribute__((cold))
#define SMATTR_CONST __attribute__((const))
#define SMATTR_HOT __attribute__((hot))
#define SMATTR_OPTIMIZE(x) __attribute__((optimize, (x)))

#define SM_ERROR(...) do {fprintf(stderr, __VA_ARGS__); abort();} while(0);

typedef unsigned int uint;
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;