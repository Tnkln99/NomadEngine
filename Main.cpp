#include"StaticModelComponent.h"
#include "Actor.h"
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

	//SkeletalModel skeletalModel{};
	//skeletalModel.loadModel("Forgotten.FBX");
	//Animation animation("ForgottenWalk.FBX", &skeletalModel);
	//Animator animator(&animation);

	//float angle = glm::radians(270.0f);
	//skeletalModel.mModelMatrix = glm::rotate(skeletalModel.mModelMatrix, angle, axis);

	Renderer renderer;
	renderer.registerWindow(std::make_shared<Window>(window));
	Locator::registerRenderer(std::make_shared<Renderer>(renderer));


	Actor staticModelActor{};
	staticModelActor.mTransform.mPos = glm::vec4{ 1 };
	auto staticModelComp = staticModelActor.addComponent<StaticModelComponent>();
	staticModelComp->mStaticModel = ResourceManager::getStaticModel("Bob");
	std::cout << staticModelComp->mOwner->mTransform.mPos.y << std::endl;

	Actor lightActor{};
	lightActor.mTransform.mPos = glm::vec4{ 0 ,  50 , 0 , 1 };
	//std::cout << lightActor.mTransform.mPos.y << std::endl;
	auto lightComp = lightActor.addComponent<LightComponent>();
	Locator::getRendererService()->registerLight(lightComp);
	std::cout << lightComp->mOwner->mTransform.mPos.y << std::endl;

	Actor cameraActor{};
	cameraActor.mTransform.mPos = glm::vec4{ 0 ,  0 , 300 , 1 };
	auto cameraComp = cameraActor.addComponent<CameraComponent>();
	Locator::getRendererService()->registerCamera(cameraComp);
	std::cout << cameraComp->mOwner->mTransform.mPos.y << std::endl;


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
		cameraActor.update();
		lightActor.update();

		// Draws different meshes
		//skeletalModel.draw(camera, light, transforms, debugBoneIndex);
		//model->draw(camera, light);


		window.swapBuffers();
		window.pollEvents();
	}

	window.terminate();
	return 0;
}
