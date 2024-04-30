#include"Camera.h"



Camera::Camera()
{
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane,
	const std::shared_ptr<Window> window, Transform transform)
{
	// Makes camera look in the right direction from the right position
	mView = glm::lookAt(transform.mPos, transform.mPos + transform.mEulerRot, transform.mUp);
	// Adds perspective to the scene
	mProjection = glm::perspective(glm::radians(FOVdeg), (float)mWidth / mHeight, nearPlane, farPlane);
}

void Camera::sendCameraInfoToGpu(std::shared_ptr<Shader> shader, Transform transform) const
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader->mId, "projection"), 1, GL_FALSE, glm::value_ptr(mProjection));
	glUniformMatrix4fv(glGetUniformLocation(shader->mId, "view"), 1, GL_FALSE, glm::value_ptr(mView));
}