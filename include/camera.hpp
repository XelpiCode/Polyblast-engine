#pragma once
#include <glm/glm.hpp>
#include "GLFW/glfw3.h"

class Camera {
    public:

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    const float cameraSpeed = 3.0f;

    Camera();

    void processInput(GLFWwindow* window, float deltaTime);

    glm::mat4 getViewMatrix() const;
};
