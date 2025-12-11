#pragma once

#include <stb_image/stb_image.h>
#include <glad/gl.h>

class Texture {
    public:
    GLuint ID;
    GLenum type;

    Texture(
        const char* texPath,
        GLenum texType,
        GLenum format,
        GLenum pixelType
    );
    ~Texture();

    void Bind(GLuint unit) const;
    void Unbind();

};
