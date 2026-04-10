#pragma once

#include<glad/gl.h>

class VBO {
    public:

    GLuint ID = 0;

    VBO(const void *vertices, GLsizeiptr size);
    ~VBO();

    void Bind();

    void Unbind();

    void Delete();

};