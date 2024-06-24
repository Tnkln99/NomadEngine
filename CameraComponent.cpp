#include "CameraComponent.h"
#include "Locator.h"
#include "Actor.h"

CameraComponent::CameraComponent()
{
	mCamera = std::make_shared<Camera>();
}

void CameraComponent::update(float dt)
{
		
}

void CameraComponent::beginPlay()
{
}

void CameraComponent::init()
{
	const std::shared_ptr<CameraComponent> result = std::dynamic_pointer_cast<CameraComponent>(mOwner->mComponents.back());
	Locator::getRendererService().registerCamera(result);
}
