#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTexCoord;

out vec3 frag_col;
// uniform vec4 progCol;
out vec2 TexCoord;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    frag_col = aCol;
    TexCoord = aTexCoord;
}

