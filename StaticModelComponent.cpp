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

void StaticModelComponent::init()
{
	const std::shared_ptr<StaticModelComponent> result = std::dynamic_pointer_cast<StaticModelComponent>(mOwner->mComponents.back());
	Locator::getRendererService()->registerStaticModel(result);
}
