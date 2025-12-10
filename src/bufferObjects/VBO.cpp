#include <bufferObjects/VBO.hpp>

VBO::VBO(const float *vertices, const GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
};

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

// NOLINTNEXTLINE(readability-make-member-function-const)
void VBO::Delete() {
    glDeleteBuffers(1, &ID);
};

VBO::~VBO() {
    glDeleteBuffers(1, &ID);
}
