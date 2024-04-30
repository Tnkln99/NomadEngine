#include"StaticModelComponent.h"
#include "Actor.h"
#include"Animator.h"
#include"ResourceManager.h"
#include "Locator.h"
#include "Window.h"

const unsigned int width = 800;
const unsigned int height = 800;


int main()
{
	Window window{ "Nomad" };

	ResourceManager::loadShader("lightIndicator", "Light.vert", "Light.frag");
	ResourceManager::loadShader("SkeletalModel", "SkeletalModel.vert", "SkeletalModel.frag");
	ResourceManager::loadShader("StaticModel", "StaticModel.vert", "StaticModel.frag");

	ResourceManager::loadStaticModel("Bob", "boblampclean.md5mesh");

	Light light{};
	light.loadLightIndicator();

	// Creates camera object
	Camera camera(width, height, glm::vec3(0, 0, 300));

	//SkeletalModel skeletalModel{};
	//skeletalModel.loadModel("Forgotten.FBX");
	//Animation animation("ForgottenWalk.FBX", &skeletalModel);
	//Animator animator(&animation);

	//float angle = glm::radians(270.0f);
	//skeletalModel.mModelMatrix = glm::rotate(skeletalModel.mModelMatrix, angle, axis);

	Actor staticModelActor{};
	staticModelActor.mTransform.mPos = glm::vec4{ 0 };
	auto staticModelComp = staticModelActor.addComponent<StaticModelComponent>(camera, light );
	staticModelComp->mStaticModel = ResourceManager::getStaticModel("Bob");

	Renderer renderer;
	renderer.registerLight(std::make_shared<Light>(light));
	renderer.registerCamera(std::make_shared<Camera>(camera));

	Locator::registerRenderer(std::make_shared<Renderer>(renderer));

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	int debugBoneIndex = 2;
	float lastIndexChangeTimer = glfwGetTime();

	staticModelActor.init();
	while (!window.shouldCloseWindow())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// 32 is integer for spacebar
		//if(glfwGetKey(window, 32) && (glfwGetTime() - lastIndexChangeTimer) > 1.0f  )
		//{
		//	debugBoneIndex++;
		//	if(skeletalModel.getBoneCount() < debugBoneIndex)
		//	{
		//		debugBoneIndex = 0;
		//	}
		//	lastIndexChangeTimer = glfwGetTime();
		//}

		// camera.inputs(window);
		// camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		

		window.clear();

		//animator.updateAnimation(deltaTime);
		//auto transforms = animator.getFinalBoneMatrices();
		staticModelActor.update();

		// Draws different meshes
		//skeletalModel.draw(camera, light, transforms, debugBoneIndex);
		//model->draw(camera, light);


		light.drawIndicator(camera);


		window.swapBuffers();
		window.pollEvents();
	}

	window.terminate();
	return 0;
}
