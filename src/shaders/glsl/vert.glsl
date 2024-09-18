#version 440 core

layout (location = 0) in vec3 aPos;

out vec4 frag_col;
uniform vec4 progCol;

void main() {
    gl_Position = vec4(aPos, 1.0);
    frag_col = progCol;
}

