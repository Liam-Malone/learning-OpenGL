#include <stdint.h>

#ifndef nullptr
#define nullptr NULL
#endif

#define global static

/* unsigned int types */
typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

/* signed int types */
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

/* float types */
typedef float f32;
typedef double f64;

#define dyn_arr(T) struct { \
    T* arr;                 \
    u64 len;                \
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

/* Shader data types */
typedef struct Shader Shader;
struct Shader {
    u32 id;    /* Shader Program ID */
    i32 *locs; /* Shader Locations Array */
};

typedef enum ShaderUniformDataType {
        shader_uniform_f32 = 0,       /* Shader uniform type: float */
        shader_uniform_vec2f32,            /* Shader uniform type: vec2 (2 float) */
        shader_uniform_vec3f32,            /* Shader uniform type: vec3 (3 float) */
        shader_uniform_vec4f32,            /* Shader uniform type: vec4 (4 float) */
        shader_uniform_i32,             /* Shader uniform type: int */
        shader_uniform_vec2i32,           /* Shader uniform type: ivec2 (2 int) */
        shader_uniform_vec3i32,           /* Shader uniform type: ivec3 (3 int) */
        shader_uniform_vec4i32,           /* Shader uniform type: ivec4 (4 int) */
        shader_uniform_sampler2d        /* Shader uniform type: sampler2d */
} ShaderUniformDataType;

typedef enum ShaderAttributeDataType {
        shader_attribute_f32 = 0,     /* Shader attribute type: float */
        shader_attribute_vec2f32,          /* Shader attribute type: vec2 (2 float) */
        shader_attribute_vec3f32,          /* Shader attribute type: vec3 (3 float) */
        shader_attribute_vec4f32           /* Shader attribute type: vec4 (4 float) */
} ShaderAttributeDataType;

global Shader Shader_load(const char* restrict vs_filepath, const char* restrict fs_filepath);
global i32 Shader_get_uniform_location(Shader shader, const char* restrict value);
global void Shader_set_value(Shader shader, i32 location, void* value, ShaderUniformDataType data_type);
global void Shader_unload(Shader shader);
global void Shader_use(Shader shader);
