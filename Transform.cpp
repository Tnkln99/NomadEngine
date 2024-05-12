#include "Transform.h"
#include <glm/trigonometric.hpp>
#include <glm/gtx/quaternion.hpp>

glm::mat4 Transform::getModelMatrix() const
{
    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
        glm::radians(mEulerRot.x),
        glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
        glm::radians(mEulerRot.y),
        glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
        glm::radians(mEulerRot.z),
        glm::vec3(0.0f, 0.0f, 1.0f));

    // Y * X * Z
    const glm::mat4 roationMatrix = transformY * transformX * transformZ;

    // translation * rotation * scale (also know as TRS matrix)
    return glm::translate(glm::mat4(1.0f), mPos) *
        roationMatrix *
        glm::scale(glm::mat4(1.0f), mScale);
}
