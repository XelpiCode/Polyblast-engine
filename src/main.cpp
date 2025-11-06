#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>


struct openglState {
    GLFWwindow* window{};
    int width = 800;
    int height = 600;
};

bool initOpenGL(openglState &state);
void cleanupOpenGL(openglState &state);
void processInput(GLFWwindow *window);

int main() {

    auto state = openglState();
    if (!initOpenGL(state)) cleanupOpenGL(state);

    std::cout << "Hello, World!" << std::endl;

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