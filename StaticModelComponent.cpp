#include "StaticModelComponent.h"
#include "ResourceManager.h"
#include "Actor.h"

StaticModelComponent::StaticModelComponent(Camera& camera, Light& light) : mCamera{camera}, mLight{light}
{
	
}

void StaticModelComponent::update()
{
	if(mStaticModel)
		mStaticModel->draw(mCamera, mLight, mOwner->mTransform.getModelMatrix());
}

void StaticModelComponent::init()
{
}
