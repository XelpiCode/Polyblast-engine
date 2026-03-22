#version 460 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D containerTex;
uniform sampler2D tetoTex;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {

    // calculating the direction of light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // calculating the diffuse impact
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // ambient light
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // getting mixed texture
    vec4 teto = texture(tetoTex, TexCoord);
    vec4 container = texture(containerTex, TexCoord);
    vec4 tetoContainerColor = mix(container, teto, teto.a);

    vec4 result = tetoContainerColor * vec4(ambient + diffuse, 1.0);
    FragColor = result;

//    vec3 result =  (ambient + diffuse) * objectColor;
//    FragColor = vec4(result, 1.0);
}