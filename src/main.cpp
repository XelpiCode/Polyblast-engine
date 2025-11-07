#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <opengl_utils.hpp>
#include <ostream>

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

const char *vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main() {

    auto state = openglState();
    if (!initOpenGL(state)) cleanupOpenGL(state);

#pragma region VBO

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

#pragma endregion

#pragma region shader

    // Creating shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);

    // Compiling shaders
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    // Checking if compiling was successful
    int vertexSuccess;
    char infoLogVert[1024];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);
    if (!vertexSuccess) {
        glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLogVert);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogVert << std::endl;
    }

    int fragmentSuccess;
    char infoLogFrag[1024];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);
    if (!fragmentSuccess) {
        glGetShaderInfoLog(fragmentShader, 1024, nullptr, infoLogFrag);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogFrag << std::endl;
    }

    // Attaching and linking shaders into a program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // checking if linking was successful
    int programSuccess;
    char infoLogProgram[1024];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programSuccess);
    if (!programSuccess) {
        glGetProgramInfoLog(shaderProgram, 1024, nullptr, infoLogProgram);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILE_STATUS\n" << infoLogProgram << std::endl;
    }

    //remove shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

#pragma endregion

#pragma region VAO

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // After setting up the shaders and strides, use the shader
    glUseProgram(shaderProgram);

#pragma endregion

    while (!glfwWindowShouldClose(state.window)) {

        processInput(state.window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(state.window);
        glfwPollEvents();
    }

    cleanupOpenGL(state);
    return 0;
}