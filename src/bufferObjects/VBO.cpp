#include <bufferObjects/VBO.hpp>

VBO::VBO(const float *vertices, const GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
};

// NOLINTNEXTLINE(readability-make-member-function-const)
void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
};

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

// NOLINTNEXTLINE(readability-make-member-function-const)
void VBO::Delete() {
    if (ID != 0) {
        glDeleteBuffers(1, &ID);
        ID = 0; // Reset ID after deletion to prevent double-free
    }
};

VBO::~VBO() {
    Delete();
}
