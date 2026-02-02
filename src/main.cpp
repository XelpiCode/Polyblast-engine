#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <opengl_utils.hpp>
#include <shader.hpp>
#include <bufferObjects/VBO.hpp>
#include <bufferObjects/VAO.hpp>
#include <bufferObjects/EBO.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <texture.hpp>

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

    // allow blending of transparent pixels
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader Shader(RESOURCES_PATH "vertex.glsl", RESOURCES_PATH "fragment.glsl");

    Texture containerTex(RESOURCES_PATH "container.jpg", TexFilter::Linear, TexWrap::Repeat);
    Texture tetoTex(RESOURCES_PATH "teto.png", TexFilter::Linear, TexWrap::Repeat);

#pragma region Buffers

    // Making buffer objects
    VAO VAO1{};
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));

    EBO EBO1(indices, sizeof(indices));

    // Vertex attribute pointers

    // for coords
    VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    // for colors
    VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    // for tex coords
    VAO1.LinkAttribute(VBO1, 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));

    // unbind buffer
    VBO1.Unbind();
    VAO1.Unbind();

#pragma endregion

#pragma region matrices

    // model
    auto model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(2.0f));

    // view
    auto view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // projection
    glm::mat4 projection = glm::perspective(
        glm::radians(60.0f),
        static_cast<float>(state.width) / static_cast<float>(state.height),
        0.1f,
        100.0f
    );

#pragma endregion

    Shader.use();

    Shader.setMat4("projection", projection);
    Shader.setMat4("view", view);
    Shader.setMat4("model", model);

    while (!glfwWindowShouldClose(state.window)) {

        processInput(state.window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // send textures to shader
        containerTex.Bind(0);
        Shader.setInt("containerTex", 0);

        tetoTex.Bind(1);
        Shader.setInt("tetoTex", 1);

        // to render the triangles
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(state.window);
        glfwPollEvents();
    }

    cleanupOpenGL(state);
    return 0;
}