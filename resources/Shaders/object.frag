#version 460 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;

    vec3 direction;
    float innerCutOff; // should be cosine values
    float outerCutOff; // should be cosine values

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform mat4 view;
uniform vec3 viewPos;
uniform Material material;

// light uniforms
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

// MAKE SURE TO NORMALIZE THE NORMALS !!!
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 FragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 FragPos, vec3 viewDir);

void main() {

    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // directional
    vec3 result = calcDirLight(dirLight, norm, viewDir);

    // point lights
    for (int i = 0; i < NR_POINT_LIGHTS; i++)
    result += calcPointLight(pointLights[i], norm, FragPos, viewDir);

    // spot light
    result += calcSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // combine results
    vec3 ambient  = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 FragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - FragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // combine results
    vec3 ambient = light.ambient * vec3 (texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3 (texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3 (texture(material.specular, TexCoords));

    return (ambient + diffuse + specular) * attenuation;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 FragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - FragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // spot light calc
    float theta = dot(lightDir,  normalize(-light.direction));
    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)) * intensity;
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)) * intensity;

    return (ambient + diffuse + specular) * attenuation;
}
