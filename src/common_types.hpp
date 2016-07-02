#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <stdint.h>

// TODO(Cristián): Should this always use uint64?
#define KILOBYTES(amount) ((amount) * 1024LL)
#define MEGABYTES(amount) (KILOBYTES(amount) * 1024LL)
#define GIGABYTES(amount) (MEGABYTES(amount) * 1024LL)
#define TERABYTES(amount) (GIGABYTES(amount) * 1024LL)

#define ASSERT(expression) if(!(expression)) { *(volatile int *)0 = 0; }
#define ARRAY_COUNT(Array) (sizeof(Array) / sizeof((Array)[0]))

// Convenient typedef taken from stdint.h
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32 bool32;

typedef float real32;
typedef double real64;

#endif
