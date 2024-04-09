
#include"StaticModel.h"
#include"Animator.h"

const unsigned int width = 800;
const unsigned int height = 800;


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "Nomad", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	Light light{};
	light.loadLightIndicator();

	// Creates camera object
	Camera camera(width, height, glm::vec3(0, 120, 300));

	SkeletalModel skeletalModel{};
	skeletalModel.loadModel("Forgotten.FBX");
	Animation animation("ForgottenWalk.FBX", &skeletalModel);
	Animator animator(&animation);

	float angle = glm::radians(270.0f);
	glm::vec3 axis(1, 0, 0); // Y-axis
	skeletalModel.mModelMatrix = glm::rotate(skeletalModel.mModelMatrix, angle, axis);

	//StaticModel model{};
	//model.loadModel("boblampclean.md5mesh");
	//float angle2 = glm::radians(-45.0f);
	//model.mModelMatrix = glm::rotate(model.mModelMatrix, angle2, axis);


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Specify the color of the background
		glClearColor(0.02f, 0.11f, 0.1f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		camera.inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		animator.updateAnimation(deltaTime);
		auto transforms = animator.getFinalBoneMatrices();


		// Draws different meshes
		skeletalModel.draw(camera, light, transforms);
		//model.draw(camera, light);

		light.drawIndicator(camera);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
