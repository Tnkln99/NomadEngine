#include"Camera.h"
#include <glm/gtx/euler_angles.hpp>


Camera::Camera()
{
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane,
	const std::shared_ptr<Window> window, Transform transform)
{
	// Assuming transform.mEulerRot is glm::vec3 containing Euler angles in radians
	glm::mat4 rotMatrix = glm::eulerAngleYXZ(transform.mEulerRot.y, transform.mEulerRot.x, transform.mEulerRot.z);
	glm::vec3 forwardDir = glm::vec3(rotMatrix * glm::vec4(0, 0, -1, 0)); // Transform forward vector by rotation matrix
	glm::vec3 cameraTarget = transform.mPos + forwardDir; // Camera looks at this point

	mView = glm::lookAt(transform.mPos, cameraTarget, transform.mUp); // Set the view matrix
	// Adds perspective to the scene
	mProjection = glm::perspective(glm::radians(FOVdeg), (float)mWidth / mHeight, nearPlane, farPlane);
}

void Camera::sendCameraInfoToGpu(std::shared_ptr<Shader> shader, Transform transform) const
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader->mId, "projection"), 1, GL_FALSE, glm::value_ptr(mProjection));
	glUniformMatrix4fv(glGetUniformLocation(shader->mId, "view"), 1, GL_FALSE, glm::value_ptr(mView));
}