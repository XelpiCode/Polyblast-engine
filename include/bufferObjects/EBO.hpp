#pragma once

#include "glad/gl.h"

class EBO {
    public:

    GLuint ID = 0;

    EBO(const GLuint* indices, GLsizeiptr size);
    ~EBO();

    void Bind();

    void Unbind();

    void Delete();

};