#pragma once

#include <stb_image/stb_image.h>
#include <glad/gl.h>
#include <string>

class Texture {
    public:

    GLuint ID = 0;

    Texture(const std::string& texPath);

    ~Texture();

    void Bind();

    void Unbind();
};
