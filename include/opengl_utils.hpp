#pragma once
#include "GLFW/glfw3.h"

struct openglState {
    GLFWwindow* window{};
    int width = 800;
    int height = 600;
};

bool initOpenGL(openglState &state);
void cleanupOpenGL(openglState &state);
void processInput(GLFWwindow *window);