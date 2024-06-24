#include "StaticModelComponent.h"
#include "ResourceManager.h"
#include "Actor.h"
#include "Locator.h"

StaticModelComponent::StaticModelComponent()
{
}

void StaticModelComponent::update(float dt)
{
	
}

void StaticModelComponent::beginPlay()
{
}

void StaticModelComponent::init()
{
	const std::shared_ptr<StaticModelComponent> result = std::dynamic_pointer_cast<StaticModelComponent>(mOwner->mComponents.back());
	Locator::getRendererService().registerModel(result);
}

std::shared_ptr<Shader> StaticModelComponent::getShader()
{
	return mStaticModel->getShader();
}

void StaticModelComponent::draw(const glm::mat4 modelMatrix)
{
	mStaticModel->draw(modelMatrix);
}

bool StaticModelComponent::shouldDraw()
{
	return mStaticModel != nullptr;
}
