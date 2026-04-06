#version 460 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;

uniform mat4 view;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

struct Light {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main() {

    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(mat3(view) * (-light.direction)); // calculating the direction of light
    float diff = max(dot(norm, lightDir), 0.0); // calculating the diffuse impact or angle
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

    // specular lighting
    vec3 viewDir = normalize(-FragPos); // (cameraPos = 0 in view space) cameraPos - FragPos
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

    // for normal texture
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}