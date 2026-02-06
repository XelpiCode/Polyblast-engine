#pragma once
#include <glm/glm.hpp>
#include "GLFW/glfw3.h"

class Camera {
    public:

    float Yaw;
    float Pitch;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    const float cameraSpeed = 3.0f;

    glm::vec3 direction;

    Camera();

    void processInput(GLFWwindow* window, float deltaTime);

    glm::mat4 getViewMatrix() const;
};
