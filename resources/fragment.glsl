#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D containerTex;
uniform sampler2D tetoTex;

void main() {
    FragColor = texture(containerTex, TexCoord);
}