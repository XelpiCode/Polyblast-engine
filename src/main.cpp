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

    Shader objectShader(RESOURCES_PATH "Shaders/object.vert", RESOURCES_PATH "Shaders/object.frag");
    Shader lightShader(RESOURCES_PATH "Shaders/light.vert", RESOURCES_PATH "Shaders/light.frag");

    // set textures
    const Texture containerTex(RESOURCES_PATH "container2.png", TexFilter::Linear, TexWrap::Repeat);
    const Texture containerSpecTex(RESOURCES_PATH "container2_specular.png", TexFilter::Linear, TexWrap::Repeat);

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

        objectShader.use();

        // set lighting uniforms
        objectShader.setVec3("viewPos", state.camera.cameraPos);

        // directional light
        objectShader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        objectShader.setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        objectShader.setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
        objectShader.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

        // point lights
        glm::vec3 pointLightPositions[] = {
            glm::vec3( 0.7f,  0.2f,  2.0f),
            glm::vec3( 2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3( 0.0f,  0.0f, -3.0f)
        };

        // point light #1
        objectShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        objectShader.setVec3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        objectShader.setVec3("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        objectShader.setVec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        objectShader.setFloat("pointLights[0].constant", 1.0f);
        objectShader.setFloat("pointLights[0].linear", 0.09f);
        objectShader.setFloat("pointLights[0].quadratic", 0.032f);

        // point light #2
        objectShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        objectShader.setVec3("pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        objectShader.setVec3("pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        objectShader.setVec3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        objectShader.setFloat("pointLights[1].constant", 1.0f);
        objectShader.setFloat("pointLights[1].linear", 0.09f);
        objectShader.setFloat("pointLights[1].quadratic", 0.032f);

        // point light #3
        objectShader.setVec3("pointLights[2].position", pointLightPositions[2]);
        objectShader.setVec3("pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        objectShader.setVec3("pointLights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        objectShader.setVec3("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        objectShader.setFloat("pointLights[2].constant", 1.0f);
        objectShader.setFloat("pointLights[2].linear", 0.09f);
        objectShader.setFloat("pointLights[2].quadratic", 0.032f);

        // point light #4
        objectShader.setVec3("pointLights[3].position", pointLightPositions[3]);
        objectShader.setVec3("pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        objectShader.setVec3("pointLights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        objectShader.setVec3("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        objectShader.setFloat("pointLights[3].constant", 1.0f);
        objectShader.setFloat("pointLights[3].linear", 0.09f);
        objectShader.setFloat("pointLights[3].quadratic", 0.032f);

        // spotlight
        objectShader.setVec3("spotLight.position", state.camera.cameraPos);
        objectShader.setVec3("spotLight.direction", state.camera.cameraFront);
        objectShader.setVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
        objectShader.setVec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        objectShader.setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        objectShader.setFloat("spotLight.constant", 1.0f);
        objectShader.setFloat("spotLight.linear", 0.09f);
        objectShader.setFloat("spotLight.quadratic", 0.032f);
        objectShader.setFloat("spotLight.innerCutOff", glm::cos(glm::radians(12.5f)));
        objectShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

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

        // setting material values
        containerTex.Bind(0);
        objectShader.setInt("material.diffuse", 0);

        containerSpecTex.Bind(1);
        objectShader.setInt("material.specular", 1);

        objectShader.setFloat("material.shininess", 32.0f);

        // for 10 cubes

        for(unsigned int i = 0; i < 10; i++)
        {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * static_cast<float>(i);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            objectShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // // for a single cube
        //
        // objectShader.setMat4("model", glm::mat4(1.0f));
        // glDrawArrays(GL_TRIANGLES, 0, 36);


        #pragma endregion

        #pragma region light model matrix

        lightShader.use();

        lightShader.setMat4("view", view);
        lightShader.setMat4("projection", projection);

        // // single light Cube
        // auto lightModel = glm::mat4(1.0f);
        // lightModel = glm::translate(lightModel, lightPos);
        // lightModel = glm::scale(lightModel, glm::vec3(0.2f));
        //
        // // send light source cube to light shader
        // lightShader.setMat4("model", lightModel);
        //
        // lightVAO.Bind();
        // glDrawArrays(GL_TRIANGLES, 0, 36);

        // 4 light cubes
        for(auto pointLightPosition : pointLightPositions) {
            auto lightModel = glm::mat4(1.0f);
            lightModel = glm::translate(lightModel, pointLightPosition);
            lightModel = glm::scale(lightModel, glm::vec3(0.2f));
            lightShader.setMat4("model", lightModel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        #pragma endregion


        glfwSwapBuffers(state.window);
        glfwPollEvents();
    }

    cleanupOpenGL(state);
    return 0;
}