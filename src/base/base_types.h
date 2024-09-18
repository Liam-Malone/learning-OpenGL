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

typedef struct Vec4 Vec4;
struct Vec4 {
    float x;
    float y;
    float z;
    float w;
};

typedef struct Vec3 Vec3;
struct Vec3 {
    float x;
    float y;
    float z;
};

typedef struct Vec2 Vec2;
struct Vec2 {
    float x;
    float y;
};

typedef struct Color Color;
struct Color {
    float r;
    float g;
    float b;
    float a;
};

typedef Vec2 Velocity;
typedef Vec3 Position;

/* Shader data types */
typedef struct Shader Shader;
struct Shader {
    u32 id;    /* Shader Program ID */
    i32 *locs; /* Shader Locations Array */
};

typedef enum ShaderUniformDataType {
        shader_uniform_float = 0,       /* Shader uniform type: float */
        shader_uniform_vec2,            /* Shader uniform type: vec2 (2 float) */
        shader_uniform_vec3,            /* Shader uniform type: vec3 (3 float) */
        shader_uniform_vec4,            /* Shader uniform type: vec4 (4 float) */
        shader_uniform_int,             /* Shader uniform type: int */
        shader_uniform_ivec2,           /* Shader uniform type: ivec2 (2 int) */
        shader_uniform_ivec3,           /* Shader uniform type: ivec3 (3 int) */
        shader_uniform_ivec4,           /* Shader uniform type: ivec4 (4 int) */
        shader_uniform_sampler2d        /* Shader uniform type: sampler2d */
} ShaderUniformDataType;

typedef enum ShaderAttributeDataType {
        shader_attribute_float = 0,     /* Shader attribute type: float */
        shader_attribute_vec2,          /* Shader attribute type: vec2 (2 float) */
        shader_attribute_vec3,          /* Shader attribute type: vec3 (3 float) */
        shader_attribute_vec4           /* Shader attribute type: vec4 (4 float) */
} ShaderAttributeDataType;

global Shader Shader_load(const char* restrict vs_filepath, const char* restrict fs_filepath);
global i32 Shader_get_uniform_location(Shader shader, const char* restrict value);
global void Shader_set_value(Shader shader, void* value, ShaderUniformDataType data_type);
global void Shader_unload(Shader shader);
global void Shader_use(Shader shader);
