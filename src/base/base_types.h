#include <stdint.h>

#define glue(s1, s2) s1 ## s2

#ifdef _debug 
#define TODO(msg) 
#else
#define TODO(msg) static_assert(false, "\n      :: TODO: " ## msg ## " ::")
#endif

#define auto static_assert(false, "No `auto` in the codebase!!");

#ifndef nullptr
#define nullptr NULL
#endif

#define global static
#define _interal static

/* unsigned integer types */
typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

/* signed integer types */
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

/* floating point types */
typedef float f32;
typedef double f64;


/* Units */
#define KB(n)  (((u64)(n)) << 10)
#define MB(n)  (((u64)(n)) << 20)
#define GB(n)  (((u64)(n)) << 30)
#define TB(n)  (((u64)(n)) << 40)

#define AlignPow2(x,b) (((x) + (b) - 1)&(~((b) - 1)))

/* Slice "Type" */
#define slice(T) struct {  \
    T* ptr;                \
    u64 len;               \
}

/* Dynamic List Type*/
#define list(T) struct {  \
    T* ptr;               \
    u64 len;              \
    u64 cap;              \
} 

