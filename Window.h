#pragma once

#include<glad/glad.h>
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include <iostream>


class Window
{
public:
	Window(const std::string& name);

	bool shouldCloseWindow();
	void clear();
	void swapBuffers();
	void pollEvents();
	void terminate();

	const int getWidth();
	const int getHeight();
private:
	int mWidth = 500;
	int mHeight = 500;
	GLFWwindow* mWindow = nullptr;
	std::string mName;
};

