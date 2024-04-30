#pragma once

#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "Shader.h"
#include "Window.h"
#include "Transform.h"

class Camera
{
public:
	glm::mat4 mProjection = glm::mat4(1.0f);
	glm::mat4 mView = glm::mat4(1.0f);

	// Prevents the camera from jumping around when first clicking left click
	bool mFirstClick = true;

	// Stores the width and height of the window
	int mWidth;
	int mHeight;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float mSpeed = 10.0f;
	float mSensitivity = 100.0f;

	// Camera constructor to set up initial values
	Camera();

	// Updates the camera matrix to the Vertex Shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane,
		const std::shared_ptr<Window> window, Transform transform);
	// Exports the camera matrix to a shader
	void sendCameraInfoToGpu(std::shared_ptr<Shader> shader, Transform transform) const;
};
