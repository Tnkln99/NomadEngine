#include "Scene.h"

#include "CameraComponent.h"
#include "LightComponent.h"
#include "ResourceManager.h"


void Scene::init()
{
	ResourceManager::loadStaticModel("Sphere", "Sphere.obj");

	Actor light;
	mActors["Light"] = light;
	mActors["Light"].mTransform.mPos = glm::vec4{ 0 ,  10 , 10 , 1 };
	//std::cout << lightActor.mTransform.mPos.y << std::endl;
	auto lightComp = mActors["Light"].addComponent<LightComponent>();

	Actor camera;
	mActors["Camera"] = camera;
	mActors["Camera"].mTransform.mPos = glm::vec4{ 0 ,  0 , 50 , 1 };
	auto cameraComp = mActors["Camera"].addComponent<CameraComponent>();
}

void Scene::beginPlay()
{
	for(const auto & actor : mActors)
	{
		actor.second.beginPlay();
	}
}

void Scene::sceneUi()
{

}

void Scene::update(float dt)
{
	for (const auto& actor : mActors)
	{
		actor.second.update(dt);
	}
}
