#include"StaticModelComponent.h"
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
	staticModelActor.mTransform.mPos = glm::vec4{ -20, 0 , 0, 0};
	staticModelActor.mTransform.mEulerRot = glm::vec4{ -45, 0, 0, 0 };
	auto staticModelComp = staticModelActor.addComponent<StaticModelComponent>();
	staticModelComp->mStaticModel = ResourceManager::getStaticModel("Bob");

	Actor staticModelActor2{};
	staticModelActor2.mTransform.mPos = glm::vec4{ 20, 0 , 0, 0 };
	staticModelActor2.mTransform.mScale = glm::vec4{ 0.7f };
	staticModelActor2.mTransform.mEulerRot = glm::vec4{ -45, 0, 0, 0 };
	auto staticModelComp2 = staticModelActor2.addComponent<StaticModelComponent>();
	staticModelComp2->mStaticModel = ResourceManager::getStaticModel("Forgotten");
	

	Actor lightActor{};
	lightActor.mTransform.mPos = glm::vec4{ 0 ,  50 , 190 , 1 };
	//std::cout << lightActor.mTransform.mPos.y << std::endl;
	auto lightComp = lightActor.addComponent<LightComponent>();

	Actor cameraActor{};
	cameraActor.mTransform.mPos = glm::vec4{ 0 ,  50 , 200 , 1 };
	auto cameraComp = cameraActor.addComponent<CameraComponent>();


	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	renderer.changeRenderMode(FILL);

	while (!window.shouldCloseWindow())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		window.clear();

		
		staticModelActor.update(deltaTime);
		staticModelActor2.update(deltaTime);
		cameraActor.update(deltaTime);
		lightActor.update(deltaTime);

		Locator::getRendererService()->render();

		//animator.updateAnimation(deltaTime);
		//auto transforms = animator.getFinalBoneMatrices();
		//Draws different meshes
		//skeletalModel.draw(camera, light, transforms, debugBoneIndex);


		window.swapBuffers();
		window.pollEvents();
	}

	window.terminate();
	return 0;
}
