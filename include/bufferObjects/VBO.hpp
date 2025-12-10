#ifndef VBO_H
#define VBO_H

#include<glad/gl.h>

class VBO {
    public:

    GLuint ID = 0;

    VBO(const float *vertices, GLsizeiptr size);
    ~VBO();

    void Bind();

    void Unbind();

    void Delete();

};

#endif