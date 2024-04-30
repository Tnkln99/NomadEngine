#include "LightComponent.h"
#include "Actor.h"
#include "Locator.h"

LightComponent::LightComponent()
{
	Locator::getRendererService()->registerLight(std::make_shared<LightComponent>(*this));
	mLight = std::make_shared<Light>();
}

void LightComponent::update()
{
}

void LightComponent::init()
{
}
