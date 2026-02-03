#pragma once
#include "GLFW/glfw3.h"

struct openglState {
    GLFWwindow* window{};
    int width = 1200;
    int height = 1000;
};

bool initOpenGL(openglState &state);
void cleanupOpenGL(openglState &state);
void processInput(GLFWwindow *window);