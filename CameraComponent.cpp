#include "CameraComponent.h"
#include "Locator.h"
#include "Actor.h"

CameraComponent::CameraComponent()
{
	mCamera = std::make_shared<Camera>();
}

void CameraComponent::update()
{
	
}

void CameraComponent::init()
{
	for (auto& comp : mOwner->mComponents)
	{
		if (comp.get() == this)
		{
			const std::shared_ptr<CameraComponent> result = std::dynamic_pointer_cast<CameraComponent>(comp);
			std::cout << comp.get() << " " << this;
			Locator::getRendererService()->registerCamera(result);
		}
	}
}
