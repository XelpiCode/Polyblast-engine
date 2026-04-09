#pragma once

#include <string>
#include "shader.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
};

class Mesh {
    public:

    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh(
        std::vector<Vertex> vertices,
        std::vector<unsigned int> indices,
        std::vector<Texture> textures
    );

    void Draw(Shader &shader);

    private:

    unsigned int VAO, VBO, EBO;
    void setupMesh();
};