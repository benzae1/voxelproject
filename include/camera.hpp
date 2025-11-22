#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;

    Camera(glm::vec3 startPos)
        : Position(startPos), WorldUp(0, 1, 0),
        Yaw(-90.0f), Pitch(0.0f),
        MovementSpeed(10.0f), MouseSensitivity(0.1f)
    {
        updateVectors();
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void processKeyboard(int key, float deltaTime);
    void processMouse(float xOffset, float yOffset);

private:
    void updateVectors();
};
