#include <stdint.h>

#ifdef _debug 
#define TODO 
#else
#define TODO static_assert(false, "DO NOT COMPILE A RELEASE BUILD WITHOUT RESOLVING TODOs")
#endif

#define auto static_assert(false, "No `auto` in the codebase!!");

#ifndef nullptr
#define nullptr NULL
#endif

#define global static

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

#define slice(T) struct { \
    T* ptr;               \
    u64 len;              \
}

#define dyn_arr(T) struct { \
    T* ptr;                 \
    u64 len;                \
    u64 cap;                \
} 

typedef struct Color Color;
struct Color {
    f32 r;
    f32 g;
    f32 b;
    f32 a;
};
