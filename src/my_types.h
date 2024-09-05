#define global static
#define internal static

#ifdef true 
typedef enum {
    false,
    true,
} bool;
#endif

#ifndef nullptr
#define nullptr NULL
#endif

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
