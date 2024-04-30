#include "LightComponent.h"
#include "Actor.h"
#include "Locator.h"

LightComponent::LightComponent()
{
	mLight = std::make_shared<Light>();
}

void LightComponent::update()
{
}

void LightComponent::init()
{
}
