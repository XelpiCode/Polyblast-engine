#include <mesh.hpp>

Mesh::Mesh(
    const std::vector<Vertex> &vertices,
    const std::vector<unsigned int> &indices,
    const std::vector<MeshTexture> &textures
) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}