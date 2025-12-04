#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <opengl_utils.hpp>
#include <shader.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>


float vertices[] = {
    // positions          // colors           // texture coords
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   -1.0f, -1.0f,   // top right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   -1.0f, 0.0f,   // bottom right
   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, -1.0f    // top left
};

unsigned int indices[] = {
    2, 3, 1,   // first triangle
    3, 0, 1
};

int main() {

    auto state = openglState();
    if (!initOpenGL(state)) cleanupOpenGL(state);

    Shader Shader(RESOURCES_PATH "vertex.glsl", RESOURCES_PATH "fragment.glsl");

// TODO : Need to abstract buffers
#pragma region Buffers

    // Making buffer objects
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // Binding buffers
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex attribute pointers

    // for coords
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // for colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // for tex coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // EBO binding
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

#pragma endregion

#pragma region Textures

    // generate an empty texture
    GLuint tetoTexture;
    glGenTextures(1, &tetoTexture);
    glBindTexture(GL_TEXTURE_2D, tetoTexture);

    // set texture filtering and wrapping options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load the texture
    int tetoTxWidth, tetoTxHeight, tetoTxNrChannels;
    unsigned char* tetoTxdata = stbi_load(
        RESOURCES_PATH "teto.jpg",
        &tetoTxWidth,
        &tetoTxHeight,
        &tetoTxNrChannels,
        false
    );

    if (tetoTxdata) {

        // put texture data onto the empty texture
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            tetoTxWidth,
            tetoTxHeight,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            tetoTxdata
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    // clear unused image data
    stbi_image_free(tetoTxdata);

#pragma endregion

    while (!glfwWindowShouldClose(state.window)) {

        processInput(state.window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Shader.use();

        glBindTexture(GL_TEXTURE_2D, tetoTexture);

        // to render the triangles
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(state.window);
        glfwPollEvents();
    }

    cleanupOpenGL(state);
    return 0;
}