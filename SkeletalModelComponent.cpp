#include "SkeletalModelComponent.h"
#include "Locator.h"
#include "Actor.h"

//notes to initiate an anim
//Animation animation("ForgottenWalk.FBX", &skeletalModel);
//Animator animator(&animation);

SkeletalModelComponent::SkeletalModelComponent()
{
	
}

void SkeletalModelComponent::update(float dt)
{
	//mAnimator.updateAnimation(dt);
}

void SkeletalModelComponent::beginPlay()
{
}

void SkeletalModelComponent::init()
{
	const std::shared_ptr<SkeletalModelComponent> result = std::dynamic_pointer_cast<SkeletalModelComponent>(mOwner->mComponents.back());
	Locator::getRendererService().registerModel(result);
}

bool SkeletalModelComponent::shouldDraw()
{
	return mSkeletalModel != nullptr;
}

std::shared_ptr<Shader> SkeletalModelComponent::getShader()
{
	return mSkeletalModel->getShader();
}

void SkeletalModelComponent::draw(const glm::mat4 modelMatrix)
{
	//here animator will its calcuations from given animation resource 
	auto transforms = mAnimator.getFinalBoneMatrices();
	mSkeletalModel->draw(modelMatrix, mAnimator.getFinalBoneMatrices());
}
