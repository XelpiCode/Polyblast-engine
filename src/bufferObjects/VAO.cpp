#include <bufferObjects/VAO.hpp>

VAO::VAO() {
     glGenVertexArrays(1, &ID);
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
void VAO::LinkAttribute(
     VBO& VBO,
     const GLuint index,
     const GLint size,
     const GLenum type,
     const GLboolean normalized,
     const GLsizei stride,
     const void* pointer
) {
     VBO.Bind();
     glVertexAttribPointer(index, size, type, normalized, stride, pointer);
     glEnableVertexAttribArray(index);
     VBO.Unbind();
};

// NOLINTNEXTLINE(readability-make-member-function-const)
void VAO::Bind() {
     glBindVertexArray(ID);

};

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
void VAO::Unbind() {
     glBindVertexArray(0);
};

VAO::~VAO() {
     if (ID != 0) {
          glDeleteVertexArrays(1, &ID);
          ID = 0; // Reset ID after deletion to prevent double-free
     }
}
