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
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

// unsigned int indices[] = {
//     2, 3, 1,   // first triangle
//     3, 0, 1
// };

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

int main() {

    auto state = openglState();
    if (!initOpenGL(state)) cleanupOpenGL(state);

    // allow blending of transparent pixels
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enable depth buffer
    glEnable(GL_DEPTH_TEST);

    Shader Shader(RESOURCES_PATH "vertex.glsl", RESOURCES_PATH "fragment.glsl");

    Texture containerTex(RESOURCES_PATH "container.jpg", TexFilter::Linear, TexWrap::Repeat);
    Texture tetoTex(RESOURCES_PATH "teto.png", TexFilter::Linear, TexWrap::Repeat);

#pragma region Buffers

    // Making buffer objects
    VAO VAO1{};
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));

    // EBO EBO1(indices, sizeof(indices));

    // Vertex attribute pointers

    // for coords
    VAO1.LinkAttribute(VBO1,
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        nullptr
    );

    // for tex coords
    VAO1.LinkAttribute(
        VBO1,
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        reinterpret_cast<void *>(3 * sizeof(float))
    );

    // unbind buffer
    VBO1.Unbind();
    VAO1.Unbind();

#pragma endregion

    // projection
    glm::mat4 projection = glm::perspective(
        glm::radians(60.0f),
        static_cast<float>(state.width) / static_cast<float>(state.height),
        0.1f,
        100.0f
    );

    Shader.use();

    Shader.setMat4("projection", projection);

    while (!glfwWindowShouldClose(state.window)) {

        processInput(state.window);

        // clear previous frame
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // send textures to shader
        containerTex.Bind(0);
        Shader.setInt("containerTex", 0);

        tetoTex.Bind(1);
        Shader.setInt("tetoTex", 1);

        #pragma region lookAt-matrix

        constexpr float radius = 7.0f;
        auto camX = static_cast<float>(sin(glfwGetTime()) * radius);
        auto camZ = static_cast<float>(cos(glfwGetTime()) * radius);

        // view
        auto view = glm::mat4(1.0f);
        view = glm::lookAt(
            glm::vec3(camX, 0.0, camZ),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        Shader.setMat4("view", view);

        #pragma endregion

        VAO1.Bind();

        #pragma region model matrix

        for (unsigned int i = 0; i < 10; i++) {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            Shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        #pragma endregion

        // Draw triangles
        // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(state.window);
        glfwPollEvents();
    }

    cleanupOpenGL(state);
    return 0;
}