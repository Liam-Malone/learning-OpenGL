#version 440 core

out vec4 FragColor;

in vec3 frag_col;

void main() {
    FragColor = vec4(frag_col, 1.0);
}

