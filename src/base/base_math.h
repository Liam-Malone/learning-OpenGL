#include <math.h>

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


global i32 Vec4f32_mag(Vec4f32 vec);
global i32 Vec3f32_mag(Vec3f32 vec);
global i32 Vec2f32_mag(Vec2f32 vec);

global Vec4f32 Vec4f32_scale(Vec4f32 vec, i32 scalar);
global Vec3f32 Vec3f32_scale(Vec3f32 vec, i32 scalar);
global Vec2f32 Vec2f32_scale(Vec2f32 vec, i32 scalar);

global Vec4f32 Vec4f32_add(Vec4f32 vec_a, Vec4f32 vec_b);
global Vec3f32 Vec3f32_add(Vec3f32 vec_a, Vec3f32 vec_b);
global Vec2f32 Vec2f32_add(Vec2f32 vec_a, Vec2f32 vec_b);

global i32 Vec4i32_mag(Vec4i32 vec);
global i32 Vec3i32_mag(Vec3i32 vec);
global i32 Vec2i32_mag(Vec2i32 vec);

global Vec4i32 Vec4i32_scale(Vec4i32 vec, i32 scalar);
global Vec3i32 Vec3i32_scale(Vec3i32 vec, i32 scalar);
global Vec2i32 Vec2i32_scale(Vec2i32 vec, i32 scalar);

global Vec4i32 Vec4i32_add(Vec4i32 vec_a, Vec4i32 vec_b);
global Vec3i32 Vec3i32_add(Vec3i32 vec_a, Vec3i32 vec_b);
global Vec2i32 Vec2i32_add(Vec2i32 vec_a, Vec2i32 vec_b);

