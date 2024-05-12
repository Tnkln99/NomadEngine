#include "LightComponent.h"
#include "Actor.h"
#include "Locator.h"

LightComponent::LightComponent()
{
	mLight = std::make_shared<Light>();
}

void LightComponent::update(float dt)
{
}

void LightComponent::beginPlay()
{
}

void LightComponent::init()
{
	const std::shared_ptr<LightComponent> result = std::dynamic_pointer_cast<LightComponent>(mOwner->mComponents.back());
	Locator::getRendererService()->registerLight(result);
}
