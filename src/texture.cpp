#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include <texture.hpp>
#include <iostream>
#include <string>

static GLint  TexWrapMap[] = {
    GL_REPEAT,
    GL_MIRRORED_REPEAT,
    GL_CLAMP_TO_EDGE,
    GL_CLAMP_TO_BORDER
};

static GLint  TexFilterMap[] = {
    GL_NEAREST,
    GL_LINEAR
};

Texture::Texture(
    const std::string& path,
    TexFilter filter,
    TexWrap wrap,
    std::optional<glm::vec4> borderColor
) {

    // generate empty texture
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // set filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TexFilterMap[static_cast<int>(filter)]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TexFilterMap[static_cast<int>(filter)]);

    if (wrap == TexWrap::ClampToBorder) {
        if (!borderColor) { borderColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f); }

        // set border color
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(*borderColor));
    }

    // set wrapping for x and y (s and t)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TexWrapMap[static_cast<int>(wrap)]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TexWrapMap[static_cast<int>(wrap)]);

    // load the texture file
    int texWidth, texHeight, texChannels;
    unsigned char* texData = stbi_load(
        path.c_str(),
        &texWidth,
        &texHeight,
        &texChannels,
        4
    );

    // put texture data on the empty texture
    if (texData) {
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            texWidth,
            texHeight,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            texData
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    // clear image data
    stbi_image_free(texData);

}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

// NOLINTNEXTLINE(readability-make-member-function-const)
void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, ID);
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
