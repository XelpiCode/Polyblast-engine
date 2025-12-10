#include <bufferObjects/EBO.hpp>

#include "bufferObjects/VBO.hpp"

EBO::EBO(const GLuint *indices, const GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
};

// NOLINTNEXTLINE(readability-make-member-function-const)
void EBO::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
};

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
void EBO::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};

void EBO::Delete() {
    if (ID != 0) {
        glDeleteBuffers(1, &ID);
        ID = 0;
    }
};

EBO::~EBO() {
  Delete();
};

