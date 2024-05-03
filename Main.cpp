#include"StaticModelComponent.h"
#include"SkeletalModelComponent.h"
#include "Actor.h"
#include"ResourceManager.h"
#include "Locator.h"
#include "Window.h"


int main()
{
	Window window{ "Nomad" , 800, 800};
	ResourceManager::loadShader("lightIndicator", "Light.vert", "Light.frag");
	ResourceManager::loadShader("SkeletalModel", "SkeletalModel.vert", "SkeletalModel.frag");
	ResourceManager::loadShader("StaticModel", "StaticModel.vert", "StaticModel.frag");

	ResourceManager::loadStaticModel("Bob", "boblampclean.md5mesh");
	ResourceManager::loadStaticModel("Forgotten", "Forgotten.FBX");

	ResourceManager::loadSkeletalModel("Vampire", "dancing_vampire.dae");
	ResourceManager::loadSkeletalModel("Bob", "boblampclean.md5mesh");

	Locator::getRendererService()->registerWindow(std::make_shared<Window>(window));

	Actor staticModelActor{};
	staticModelActor.mTransform.mPos = glm::vec4{ -20, 0 , 0, 0};
	staticModelActor.mTransform.mEulerRot = glm::vec4{ -90, 0, 0, 0 };
	auto staticModelComp = staticModelActor.addComponent<StaticModelComponent>();
	staticModelComp->mStaticModel = ResourceManager::getStaticModel("Bob");

	Actor skeletalModelActor{};
	skeletalModelActor.mTransform.mPos = glm::vec4{ 20, 0 , 0, 0 };
	skeletalModelActor.mTransform.mScale = glm::vec4{ 1.0f };
	skeletalModelActor.mTransform.mEulerRot = glm::vec4{ -90, 0, 0, 0 };
	auto skeletalModelComp = skeletalModelActor.addComponent<SkeletalModelComponent>();
	skeletalModelComp->mSkeletalModel = ResourceManager::getSkeletalModel("Bob");

	Actor lightActor{};
	lightActor.mTransform.mPos = glm::vec4{ 0 ,  70 , 100 , 1 };
	//std::cout << lightActor.mTransform.mPos.y << std::endl;
	auto lightComp = lightActor.addComponent<LightComponent>();

	Actor cameraActor{};
	cameraActor.mTransform.mPos = glm::vec4{ 0 ,  50 , 200 , 1 };
	auto cameraComp = cameraActor.addComponent<CameraComponent>();


	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	Locator::getRendererService()->changeRenderMode(FILL);

	while (!window.shouldCloseWindow())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		window.clear();

		staticModelActor.update(deltaTime);
		skeletalModelActor.update(deltaTime);
		cameraActor.update(deltaTime);
		lightActor.update(deltaTime);

		Locator::getRendererService()->render();

		window.swapBuffers();
		window.pollEvents();
	}

	window.terminate();
	return 0;
}
