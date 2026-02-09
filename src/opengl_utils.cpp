#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <opengl_utils.hpp>
#include <iostream>
#include <camera.hpp>
#include <stb_image/stb_image.h>

void cleanupOpenGL(const openglState &state) {
    glfwDestroyWindow(state.window);
    glfwTerminate();
}

void setWindowIcon(const openglState &state) {
    GLFWimage images[1];
    images[0].pixels = stbi_load(
        RESOURCES_PATH "Logo/Polyblast.png",
        &images[0].width,
        &images[0].height,
        nullptr,
        4
    );

    if (images[0].pixels) {
        glfwSetWindowIcon(state.window, 1, images);
        stbi_image_free(images[0].pixels);
    } else {
        std::cout << "Failed to load window icon\n";
    }
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

    glfwSetWindowUserPointer(state.window, &state);

    setWindowIcon(state);

    glViewport(0, 0, state.width, state.height);

    // allow blending of transparent pixels
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Make cursor invisible
    glfwSetInputMode(state.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // call mouse_callback when mouse moves
    glfwSetCursorPosCallback(state.window, mouseCallback);
    glfwSetScrollCallback(state.window, scrollCallback);

    return initSuccess;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}