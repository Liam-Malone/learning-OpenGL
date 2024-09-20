#version 440 core

out vec4 FragColor;

in vec3 frag_col;
in vec2 TexCoord;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main() {
    // Mix the 2 textures together
    FragColor = vec4(frag_col.zyx, 1.0) * mix(texture(tex1, TexCoord),
                    texture(tex2, TexCoord),
                    0.2);
}

