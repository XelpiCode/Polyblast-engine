#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <opengl_utils.hpp>
#include <iostream>

void cleanupOpenGL(openglState &state) {
    glfwDestroyWindow(state.window);
    glfwTerminate();
}


bool initOpenGL(openglState &state) {
    bool initSuccess = true;

    if (!glfwInit()) {
        std::cout << "Failed to initialize glfw.\n";
        initSuccess = false;
    }

    state.window = glfwCreateWindow(state.width, state.height, "OpenGL window", nullptr, nullptr);
    if (!state.window) {
        std::cout << "Failed to create window.\n";
        initSuccess = false;
    }
    glfwMakeContextCurrent(state.window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cout << "Failed to initialize glad.\n";
        initSuccess = false;
    }

    glViewport(0, 0, state.width, state.height);

    return initSuccess;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}