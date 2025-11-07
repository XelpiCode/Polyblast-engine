#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <opengl_utils.hpp>

int main() {

    auto state = openglState();
    if (!initOpenGL(state)) cleanupOpenGL(state);

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