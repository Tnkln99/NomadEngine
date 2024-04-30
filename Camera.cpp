#include"Camera.h"



Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::mWidth = width;
	Camera::mHeight = height;
	mPosition = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Makes camera look in the right direction from the right position
	mView = glm::lookAt(mPosition, mPosition + mOrientation, mUp);
	// Adds perspective to the scene
	mProjection = glm::perspective(glm::radians(FOVdeg), (float)mWidth / mHeight, nearPlane, farPlane);

	// Sets new camera matrix
	mCameraMatrix = mProjection * mView;
}

void Camera::sendCameraInfoToGpu(std::shared_ptr<Shader> shader) const
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader->mId, "projection"), 1, GL_FALSE, glm::value_ptr(mProjection));
	glUniformMatrix4fv(glGetUniformLocation(shader->mId, "view"), 1, GL_FALSE, glm::value_ptr(mView));
}