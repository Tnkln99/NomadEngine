#include "Window.h"
#include "Locator.h"

Window::Window(const std::string& name)
{
	mName = name;
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(mWidth, mHeight, mName.c_str(), NULL, NULL);
	// Error check if the window fails to create
	if (mWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(mWindow);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, mWidth, mHeight);
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
}

bool Window::shouldCloseWindow()
{
	return glfwWindowShouldClose(mWindow);
}

void Window::clear()
{
	// Specify the color of the background
	glClearColor(0.02f, 0.11f, 0.1f, 1.0f);
	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swapBuffers()
{
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(mWindow);
}

void Window::pollEvents()
{
	// Take care of all GLFW events
	glfwPollEvents();
}

void Window::terminate()
{
	// Delete window before ending the program
	glfwDestroyWindow(mWindow);
	// Terminate GLFW before ending the program
	glfwTerminate();
}

const int Window::getWidth()
{
	return mWidth;
}

const int Window::getHeight()
{
	return mHeight;
}
