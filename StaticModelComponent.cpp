#include "StaticModelComponent.h"
#include "ResourceManager.h"
#include "Actor.h"
#include "Locator.h"

StaticModelComponent::StaticModelComponent()
{
}

void StaticModelComponent::update()
{
	
}

void StaticModelComponent::init()
{
	for(auto& comp : mOwner->mComponents)
	{
		if(comp.get() == this)
		{
			std::shared_ptr<StaticModelComponent> result = std::dynamic_pointer_cast<StaticModelComponent>(comp);
			std::cout << comp.get() << " " << this;
			Locator::getRendererService()->registerStaticModel(result);
		}
	}
}
