#include "camera.hpp"
#include <GLFW/glfw3.h>

void Camera::processKeyboard(int key, float dt)
{
    float velocity = MovementSpeed * dt;

    if (key == GLFW_KEY_W)
        Position += Front * velocity;
    if (key == GLFW_KEY_S)
        Position -= Front * velocity;
    if (key == GLFW_KEY_A)
        Position -= Right * velocity;
    if (key == GLFW_KEY_D)
        Position += Right * velocity;
    if (key == GLFW_KEY_SPACE)
        Position.y += velocity;
    if (key == GLFW_KEY_LEFT_CONTROL)
        Position.y -= velocity;
}

void Camera::processMouse(float xoff, float yoff)
{
    xoff *= MouseSensitivity;
    yoff *= MouseSensitivity;

    Yaw += xoff;
    Pitch += yoff;

    if (Pitch > 89.0f)  Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;

    updateVectors();
}

void Camera::updateVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
