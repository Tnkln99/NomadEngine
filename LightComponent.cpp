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
	for (auto& comp : mOwner->mComponents)
	{
		if (comp.get() == this)
		{
			const std::shared_ptr<LightComponent> result = std::dynamic_pointer_cast<LightComponent>(comp);
			std::cout << comp.get() << " " << this;
			Locator::getRendererService()->registerLight(result);
		}
	}
}
