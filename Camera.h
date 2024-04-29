#pragma once

#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "Shader.h"

class Camera
{
public:
	// Stores the main vectors of the camera
	glm::vec3 mPosition;
	glm::vec3 mOrientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 mUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 mProjection = glm::mat4(1.0f);
	glm::mat4 mView = glm::mat4(1.0f);
	glm::mat4 mCameraMatrix = glm::mat4(1.0f);

	// Prevents the camera from jumping around when first clicking left click
	bool mFirstClick = true;

	// Stores the width and height of the window
	int mWidth;
	int mHeight;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float mSpeed = 10.0f;
	float mSensitivity = 100.0f;

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);

	// Updates the camera matrix to the Vertex Shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exports the camera matrix to a shader
	void sendCameraInfoToGpu(std::shared_ptr<Shader> shader) const ;
	// Handles camera inputs
	void inputs(GLFWwindow* window);
};
