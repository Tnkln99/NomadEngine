#pragma once

#include <glm/matrix.hpp>
#include <glm/vec3.hpp>



class Transform
{
public:
    glm::vec3 mPos = { 0.0f, 0.0f, 0.0f };
    glm::vec3 mEulerRot = { 0.0f, 0.0f, 0.0f };
    glm::vec3 mScale = { 1.0f, 1.0f, 1.0f };

    const glm::mat4 getModelMatrix();
private:
    glm::mat4 mModelMatrix = glm::mat4(1.0f);
};
