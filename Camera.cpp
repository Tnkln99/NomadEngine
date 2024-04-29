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



void Camera::inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mPosition += mSpeed * mOrientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mPosition += mSpeed * -glm::normalize(glm::cross(mOrientation, mUp));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mPosition += mSpeed * -mOrientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mPosition += mSpeed * glm::normalize(glm::cross(mOrientation, mUp));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		mPosition += mSpeed * mUp;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		mPosition += mSpeed * -mUp;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		mSpeed = 0.5f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		mSpeed = 0.1f;
	}


	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (mFirstClick)
		{
			glfwSetCursorPos(window, (mWidth / 2), (mHeight / 2));
			mFirstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = mSensitivity * (float)(mouseY - (mHeight / 2)) / mHeight;
		float rotY = mSensitivity * (float)(mouseX - (mWidth / 2)) / mWidth;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(mOrientation, glm::radians(-rotX), glm::normalize(glm::cross(mOrientation, mUp)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, mUp) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			mOrientation = newOrientation;
		}

		// Rotates the Orientation left and right
		mOrientation = glm::rotate(mOrientation, glm::radians(-rotY), mUp);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (mWidth / 2), (mHeight / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		mFirstClick = true;
	}
}