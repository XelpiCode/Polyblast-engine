#version 460 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D containerTex;
uniform sampler2D tetoTex;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 viewPos;

uniform mat4 view;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main() {

    vec4 viewlightPos = view * vec4(lightPos, 1.0); // convert lightPos from world to view space

    // ambient light
    vec3 ambient = light.ambient * material.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(viewlightPos) - FragPos); // calculating the direction of light
    float diff = max(dot(norm, lightDir), 0.0); // calculating the diffuse impact or angle
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // specular lighting
    vec3 viewDir = normalize(-FragPos); // (cameraPos = 0 in view space) cameraPos - FragPos
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    // getting mixed texture
    vec4 teto = texture(tetoTex, TexCoord);
    vec4 container = texture(containerTex, TexCoord);
    vec4 tetoContainerColor = mix(container, teto, teto.a);

//    vec4 result = tetoContainerColor * vec4(ambient + diffuse + specular, 1.0);
//    FragColor = result;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}