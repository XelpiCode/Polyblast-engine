#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D containerTex;
uniform sampler2D tetoTex;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {
    vec4 teto = texture(tetoTex, TexCoord);
    vec4 container = texture(containerTex, TexCoord);
//    FragColor = mix(container, teto, teto.a) * vec4(lightColor * objectColor, 1.0);
    FragColor = vec4(lightColor * objectColor, 1.0);
}