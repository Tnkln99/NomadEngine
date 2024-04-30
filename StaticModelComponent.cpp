#include "StaticModelComponent.h"
#include "ResourceManager.h"
#include "Actor.h"
#include "Locator.h"

StaticModelComponent::StaticModelComponent()
{
}

void StaticModelComponent::update()
{
	if (mStaticModel)
		Locator::getRendererService()->render(mStaticModel, mOwner->mTransform.getModelMatrix());
}

void StaticModelComponent::init()
{
}
