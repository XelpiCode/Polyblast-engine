#version 460 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D tetoTex;

uniform vec3 objectColor;
uniform vec3 viewPos;

uniform mat4 view;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
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

    vec3 viewlightPos = vec3(view * vec4(light.position, 1.0)); // convert lightPos from world to view space

    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(viewlightPos - FragPos); // calculating the direction of light
    float diff = max(dot(norm, lightDir), 0.0); // calculating the diffuse impact or angle
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

    // specular lighting
    vec3 viewDir = normalize(-FragPos); // (cameraPos = 0 in view space) cameraPos - FragPos
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

//    // for mixed texture
//    vec4 teto = texture(tetoTex, TexCoord * -1); // multiply by -1 to make it erect
//    vec3 container = texture(material.diffuse, TexCoord).rgb;
//    vec3 tetoContainerColor = mix(container, teto.rgb, teto.a);
//    vec3 ambient2 = light.ambient * tetoContainerColor;
//    vec3 diffuse2 = light.diffuse * diff * tetoContainerColor;
//
//    vec3 result = ambient2 + diffuse2 + specular;

    // for normal texture
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}