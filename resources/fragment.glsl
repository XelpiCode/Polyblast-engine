#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D containerTex;
uniform sampler2D tetoTex;

void main() {
    vec4 teto = texture(tetoTex, TexCoord);
    vec4 container = texture(containerTex, TexCoord);
    FragColor = mix(container, teto, teto.a);
}