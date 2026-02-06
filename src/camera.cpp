#include <camera.hpp>
#include "GLFW/glfw3.h"
#include "glm/ext/matrix_transform.hpp"

Camera::Camera()
:   cameraPos(0.0f, 0.0f, 3.0f),
    cameraFront(0.0f, 0.0f, -1.0f),
    cameraUp(0.0f, 1.0f, 0.0f)
{}

void Camera::processInput(GLFWwindow* window, float deltaTime) {
    const float normalSpeed = cameraSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraFront * normalSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraFront * normalSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * normalSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * normalSpeed;
    }
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
