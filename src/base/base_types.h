#include <stdint.h>

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

typedef struct Vec4f32 Vec4f32;
struct Vec4f32 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

typedef struct Vec3f32 Vec3f32;
struct Vec3f32 {
    f32 x;
    f32 y;
    f32 z;
};

typedef struct Vec2f32 Vec2f32;
struct Vec2f32 {
    f32 x;
    f32 y;
};

typedef struct Vec4i32 Vec4i32;
struct Vec4i32 {
    i32 x;
    i32 y;
    i32 z;
    i32 w;
};

typedef struct Vec3i32 Vec3i32;
struct Vec3i32 {
    i32 x;
    i32 y;
    i32 z;
};

typedef struct Vec2i32 Vec2i32;
struct Vec2i32 {
    i32 x;
    i32 y;
};

typedef struct Color Color;
struct Color {
    f32 r;
    f32 g;
    f32 b;
    f32 a;
};

typedef Vec2f32 Velocity;
typedef Vec3f32 Position;
