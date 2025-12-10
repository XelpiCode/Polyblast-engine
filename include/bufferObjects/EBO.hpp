#ifndef EBO_H
#define EBO_H

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

#endif