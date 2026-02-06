#pragma once
#include "GLFW/glfw3.h"

struct openglState {
    GLFWwindow* window{};
    int width = 1920;
    int height = 1080;
};

bool initOpenGL(openglState &state);
void cleanupOpenGL(const openglState &state);
void processInput(GLFWwindow *window);