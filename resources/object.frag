#version 460 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D containerTex;
uniform sampler2D tetoTex;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec4 teto = texture(tetoTex, TexCoord);
    vec4 container = texture(containerTex, TexCoord);
    vec4 tetoContainerColor = mix(container, teto, teto.a);

//    vec4 result = tetoContainerColor * vec4(ambient, 1.0);
//    FragColor = result;

    vec3 result = objectColor * ambient;
    FragColor = vec4(result, 1.0);
}