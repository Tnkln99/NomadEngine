#include "CameraComponent.h"
#include "Locator.h"
#include "Actor.h"

CameraComponent::CameraComponent()
{
	Locator::getRendererService()->registerCamera(std::make_shared<CameraComponent>(*this));
	mCamera = std::make_shared<Camera>();
}

void CameraComponent::update()
{
	
}

void CameraComponent::init()
{
}
