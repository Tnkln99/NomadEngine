#include "SandBoxScene.h"

#include "CameraComponent.h"
#include "LightComponent.h"
#include "ResourceManager.h"
#include "SkeletalModelComponent.h"
#include "StaticModelComponent.h"
#include "Timer.h"

void SandBoxScene::init()
{
	Scene::init();
	//ResourceManager::loadStaticModel("Bob", "boblampclean.md5mesh");
	//ResourceManager::loadStaticModel("Forgotten", "Forgotten.FBX");
	//ResourceManager::loadStaticModel("Cube", "Cube.obj");
	ResourceManager::loadStaticModel("Cloth", "ClothSim.obj");

	ResourceManager::loadSkeletalModel("Vampire", "dancing_vampire.dae");
	//ResourceManager::loadSkeletalModel("Bob", "boblampclean.md5mesh");

	Actor staticActor;
	mActors["ClothSim"] = staticActor;
	mActors["ClothSim"].mTransform.mPos = glm::vec4{ 0, 2 , 0, 0 };
	mActors["ClothSim"].mTransform.mScale = glm::vec4{ 1 };
	mActors["ClothSim"].mTransform.mEulerRot = glm::vec4{ -30, -90, -90, 0 };
	auto staticModelComp = mActors["ClothSim"].addComponent<StaticModelComponent>();
	staticModelComp->mStaticModel = ResourceManager::getStaticModel("Cloth");

	for(int i = 0; i < 0; i++)
	{
		Actor skeletalModel;
		std::string name;
		name = "SkeletalModel" + i;
		mActors[name] = skeletalModel;
		mActors[name].mTransform.mPos = glm::vec4{ i, 0 , 0, 0 };
		mActors[name].mTransform.mScale = glm::vec4{ 0.1f };
		mActors[name].mTransform.mEulerRot = glm::vec4{0, 0, 0, 0 };
		auto skeletalModelComp = mActors[name].addComponent<SkeletalModelComponent>();
		skeletalModelComp->mSkeletalModel = ResourceManager::getSkeletalModel("Vampire");
	}
}

void SandBoxScene::beginPlay()
{
	Scene::beginPlay();
}

void SandBoxScene::sceneUi()
{
	Scene::sceneUi();
}

void SandBoxScene::update(float dt)
{
	Scene::update(dt);
}
