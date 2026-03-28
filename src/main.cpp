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
#include <camera.hpp>

float vertices[] = {
    // positions        // texCoords   // normals

    // back face
    -0.5f,-0.5f,-0.5f,  0.0f,0.0f,     0.0f,0.0f,-1.0f,
     0.5f,-0.5f,-0.5f,  1.0f,0.0f,     0.0f,0.0f,-1.0f,
     0.5f, 0.5f,-0.5f,  1.0f,1.0f,     0.0f,0.0f,-1.0f,
     0.5f, 0.5f,-0.5f,  1.0f,1.0f,     0.0f,0.0f,-1.0f,
    -0.5f, 0.5f,-0.5f,  0.0f,1.0f,     0.0f,0.0f,-1.0f,
    -0.5f,-0.5f,-0.5f,  0.0f,0.0f,     0.0f,0.0f,-1.0f,

    // front face
    -0.5f,-0.5f, 0.5f,  0.0f,0.0f,     0.0f,0.0f, 1.0f,
     0.5f,-0.5f, 0.5f,  1.0f,0.0f,     0.0f,0.0f, 1.0f,
     0.5f, 0.5f, 0.5f,  1.0f,1.0f,     0.0f,0.0f, 1.0f,
     0.5f, 0.5f, 0.5f,  1.0f,1.0f,     0.0f,0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,  0.0f,1.0f,     0.0f,0.0f, 1.0f,
    -0.5f,-0.5f, 0.5f,  0.0f,0.0f,     0.0f,0.0f, 1.0f,

    // left face
    -0.5f, 0.5f, 0.5f,  1.0f,0.0f,    -1.0f,0.0f,0.0f,
    -0.5f, 0.5f,-0.5f,  1.0f,1.0f,    -1.0f,0.0f,0.0f,
    -0.5f,-0.5f,-0.5f,  0.0f,1.0f,    -1.0f,0.0f,0.0f,
    -0.5f,-0.5f,-0.5f,  0.0f,1.0f,    -1.0f,0.0f,0.0f,
    -0.5f,-0.5f, 0.5f,  0.0f,0.0f,    -1.0f,0.0f,0.0f,
    -0.5f, 0.5f, 0.5f,  1.0f,0.0f,    -1.0f,0.0f,0.0f,

    // right face
     0.5f, 0.5f, 0.5f,  1.0f,0.0f,     1.0f,0.0f,0.0f,
     0.5f, 0.5f,-0.5f,  1.0f,1.0f,     1.0f,0.0f,0.0f,
     0.5f,-0.5f,-0.5f,  0.0f,1.0f,     1.0f,0.0f,0.0f,
     0.5f,-0.5f,-0.5f,  0.0f,1.0f,     1.0f,0.0f,0.0f,
     0.5f,-0.5f, 0.5f,  0.0f,0.0f,     1.0f,0.0f,0.0f,
     0.5f, 0.5f, 0.5f,  1.0f,0.0f,     1.0f,0.0f,0.0f,

    // bottom face
    -0.5f,-0.5f,-0.5f,  0.0f,1.0f,     0.0f,-1.0f,0.0f,
     0.5f,-0.5f,-0.5f,  1.0f,1.0f,     0.0f,-1.0f,0.0f,
     0.5f,-0.5f, 0.5f,  1.0f,0.0f,     0.0f,-1.0f,0.0f,
     0.5f,-0.5f, 0.5f,  1.0f,0.0f,     0.0f,-1.0f,0.0f,
    -0.5f,-0.5f, 0.5f,  0.0f,0.0f,     0.0f,-1.0f,0.0f,
    -0.5f,-0.5f,-0.5f,  0.0f,1.0f,     0.0f,-1.0f,0.0f,

    // top face
    -0.5f, 0.5f,-0.5f,  0.0f,1.0f,     0.0f,1.0f,0.0f,
     0.5f, 0.5f,-0.5f,  1.0f,1.0f,     0.0f,1.0f,0.0f,
     0.5f, 0.5f, 0.5f,  1.0f,0.0f,     0.0f,1.0f,0.0f,
     0.5f, 0.5f, 0.5f,  1.0f,0.0f,     0.0f,1.0f,0.0f,
    -0.5f, 0.5f, 0.5f,  0.0f,0.0f,     0.0f,1.0f,0.0f,
    -0.5f, 0.5f,-0.5f,  0.0f,1.0f,     0.0f,1.0f,0.0f
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

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    auto state = openglState(2560, 1440);
    glfwSetWindowUserPointer(state.window, &state);

    if (!initOpenGL(state)) cleanupOpenGL(state);

    Shader objectShader(RESOURCES_PATH "object.vert", RESOURCES_PATH "object.frag");
    Shader lightShader(RESOURCES_PATH "light.vert", RESOURCES_PATH "light.frag");

    const Texture containerTex(RESOURCES_PATH "container.jpg", TexFilter::Linear, TexWrap::Repeat);
    const Texture tetoTex(RESOURCES_PATH "teto.png", TexFilter::Linear, TexWrap::Repeat);

#pragma region Buffers

    // Making buffer objects
    VAO objectVAO{};
    objectVAO.Bind();

    VBO VBO1(vertices, sizeof(vertices));

    // EBO EBO1(indices, sizeof(indices));

    // Vertex attribute pointers

    // for coords
    objectVAO.LinkAttribute(
        VBO1,
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        nullptr
    );

    // for tex coords
    objectVAO.LinkAttribute(
        VBO1,
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        reinterpret_cast<void *>(3 * sizeof(float))
    );

    // for normals
    objectVAO.LinkAttribute(
        VBO1,
        2,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        reinterpret_cast<void *>(5 * sizeof(float))
    );

    // unbind buffer
    VBO1.Unbind();
    objectVAO.Unbind();


    // for light shaders
    VAO lightVAO{};
    lightVAO.Bind();
    lightVAO.LinkAttribute(
        VBO1,
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8* sizeof(float),
        nullptr
    );

#pragma endregion

    double lastTime = glfwGetTime();
    int frameCount = 0;

    while (!glfwWindowShouldClose(state.window)) {

        // delta time
        const auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // FPS monitoring
        frameCount++;
        double currentTime = glfwGetTime();
        double elapsed = currentTime - lastTime;

        if (elapsed >= 1.0f) {
            double fps = frameCount / elapsed;

            std::string title = "Polyblast - FPS: " + std::to_string(static_cast<int>(fps));
            glfwSetWindowTitle(state.window, title.c_str());

            frameCount = 0;
            lastTime = currentTime;
        }

        // process input
        processInput(state.window);
        state.camera.processInput(state.window, deltaTime);

        // clear previous frame
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // light cube pos
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        lightPos.x = sin(glfwGetTime()) * 3.0f;
        lightPos.z = cos(glfwGetTime()) * 3.0f;

        objectShader.use();

        // set lighting uniforms
        objectShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f)); // coral color
        objectShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));   // white light
        objectShader.setVec3("lightPos", lightPos);

        // send textures to shader
        containerTex.Bind(0);
        objectShader.setInt("containerTex", 0);

        tetoTex.Bind(1);
        objectShader.setInt("tetoTex", 1);

        // view
        auto view = state.camera.getViewMatrix();
        objectShader.setMat4("view", view);

        objectShader.setVec3("viewPos", state.camera.cameraPos);

        // use the buffer for drawing stuff
        objectVAO.Bind();

        // projection
        const glm::mat4 projection = glm::perspective(
            glm::radians(state.camera.camFov),
            static_cast<float>(state.width) / static_cast<float>(state.height),
            0.1f,
            100.0f
        );
        objectShader.setMat4("projection", projection);

        #pragma region object model matrix

        #pragma region model matrix

        for (unsigned int i = 0; i < 10; i++) {

            auto model = glm::mat4(1.0f);
            const float angle = 20.0f * static_cast<float>(i);

            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(
                model, glm::radians(angle),
                glm::vec3(1.0f, 0.3f, 0.5f)
            );

            objectShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        #pragma endregion

        #pragma endregion

        #pragma region light model matrix

        lightShader.use();

        lightShader.setMat4("view", view);
        lightShader.setMat4("projection", projection);

        lightShader.use();

        // lightCube transformations
        auto lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));

        // send light source cube to light shader
        lightShader.setMat4("model", lightModel);

        lightVAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        #pragma endregion


        glfwSwapBuffers(state.window);
        glfwPollEvents();
    }

    cleanupOpenGL(state);
    return 0;
}