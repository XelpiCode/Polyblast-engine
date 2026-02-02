#pragma once

#include <glad/gl.h>
#include <string>
#include <optional>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class TexFilter {
    Nearest,
    Linear,
};

enum class TexWrap {
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    ClampToBorder,
};

class Texture {
    public:

    GLuint ID = 0;

    Texture(
        const std::string& path,
        TexFilter filter,
        TexWrap wrap,
        std::optional<glm::vec4> borderColor = std::nullopt
    );

    ~Texture();

    void Bind();

    void Unbind();
};
