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
}
