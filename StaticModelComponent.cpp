#include "StaticModelComponent.h"
#include "ResourceManager.h"

StaticModelComponent::StaticModelComponent(Camera& camera, Light& light) : mCamera{camera}, mLight{light}
{
	
}

void StaticModelComponent::update()
{
	mStaticModel->draw(mCamera, mLight);
}

void StaticModelComponent::init()
{
}
