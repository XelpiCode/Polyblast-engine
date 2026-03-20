#pragma once
#include <glm/glm.hpp>
#include "GLFW/glfw3.h"

class Camera {
    public:

    float yaw;
    float pitch;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    float lastX, lastY;

    const float cameraSpeed = 3.0f;
    const float cameraSensitivity = 0.08f;

    float camFov;

    glm::vec3 direction{};
    bool firstMouse = true;

    Camera(int width, int height, float fov);

    void processInput(GLFWwindow* window, float deltaTime);
    void processMouseScroll(float ypos);
    void processMouseMovement(float xpos, float ypos);

    [[nodiscard]] glm::mat4 getViewMatrix() const;
};

void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);