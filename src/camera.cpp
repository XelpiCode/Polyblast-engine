#include <camera.hpp>

#include "opengl_utils.hpp"
#include "GLFW/glfw3.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

Camera::Camera(int width, int height)
:   yaw(-90),
    pitch(0),

    cameraPos(0.0f, 0.0f, 3.0f),
    cameraFront(0.0f, 0.0f, -1.0f),
    cameraUp(0.0f, 1.0f, 0.0f) {

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch)) * cos(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw));

    lastX = width / 2.0f;
    lastY = height / 2.0f;
}

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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cameraPos += cameraUp * normalSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        cameraPos -= cameraUp * normalSpeed;
    }
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {

    auto* state = static_cast<openglState*>(glfwGetWindowUserPointer(window));

    Camera& cam = state->camera;

    if (cam.firstMouse) {
        cam.lastX = static_cast<float>(xpos);
        cam.lastY = static_cast<float>(ypos);
        cam.firstMouse = false;
    }

    auto xoffset = static_cast<float>(xpos) - cam.lastX;
    auto yoffset = static_cast<float>(cam.lastY - ypos);
    cam.lastX = static_cast<float>(xpos);
    cam.lastY = static_cast<float>(ypos);

    xoffset *= cam.cameraSensitivity;
    yoffset *= cam.cameraSensitivity;

    cam.yaw += xoffset;
    cam.pitch += yoffset;

    if (cam.pitch > 89.0f) {
        cam.pitch = 89.0f;
    }
    if (cam.pitch < -89.0f) {
        cam.pitch = -89.0f;
    }

    cam.direction.x = cos(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
    cam.direction.y = sin(glm::radians(cam.pitch)) * cos(glm::radians(cam.pitch));
    cam.direction.z = sin(glm::radians(cam.yaw));
    cam.cameraFront = glm::normalize(cam.direction);
}