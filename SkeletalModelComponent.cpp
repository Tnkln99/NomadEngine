#include "SkeletalModelComponent.h"
#include "Locator.h"
#include "Actor.h"

SkeletalModelComponent::SkeletalModelComponent()
{
}

void SkeletalModelComponent::update(float dt)
{
}

void SkeletalModelComponent::init()
{
	const std::shared_ptr<SkeletalModelComponent> result = std::dynamic_pointer_cast<SkeletalModelComponent>(mOwner->mComponents.back());
	Locator::getRendererService()->registerModel(result);
}

bool SkeletalModelComponent::shouldDraw()
{
	return mSkeletalModel != nullptr;
}

std::shared_ptr<Shader> SkeletalModelComponent::getShader()
{
	return mSkeletalModel->getShader();
}

void SkeletalModelComponent::draw(const glm::mat4 modelMatrix)
{
}
