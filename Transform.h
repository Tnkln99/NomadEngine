#pragma once

#include <glm/matrix.hpp>
#include <glm/vec3.hpp>



class Transform
{
public:
    glm::vec3 mPos = { 0.0f, 0.0f, 0.0f };
    glm::vec3 mEulerRot = { 0.0f, 0.0f, 0.0f };
    glm::vec3 mScale = { 1.0f, 1.0f, 1.0f };
    glm::vec3 mUp = glm::vec3(0.0f, 1.0f, 0.0f);

    [[nodiscard]] glm::mat4 getModelMatrix() const;
private:
    //glm::mat4 mModelMatrix = glm::mat4(1.0f);
};

