#pragma once

#include <glad/gl.h>
#include <bufferObjects/VBO.hpp>

class VAO {
    public:

    GLuint ID = 0;

    VAO();
    ~VAO();

    void LinkAttribute(
        VBO& VBO,
        GLuint index,
        GLint size,
        GLenum type,
        GLboolean normalized,
        GLsizei stride,
        const void* pointer
    );

    void Bind();

    void Unbind();

    void Delete();
};