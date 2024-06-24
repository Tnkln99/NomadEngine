#pragma once

#include<glad/glad.h>
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include <iostream>
#include "imgui/imgui_impl_glfw.h"



class Window
{
public:
	Window(const std::string& name, int width, int height);

	bool shouldCloseWindow();
	void clear();
	void swapBuffers();
	void pollEvents();
	void terminate();

	const int getWidth();
	const int getHeight();

	void setUpImgui() const
	{
		ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
	}
private:
	int mWidth;
	int mHeight;
	GLFWwindow* mWindow = nullptr;
	std::string mName;
};

