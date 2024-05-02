#pragma once

#include "IModelComponent.h"
#include "SkeletalModel.h"
#include "Animator.h"
#include <memory>

class SkeletalModelComponent : public IModelComponent
{
public:
	SkeletalModelComponent();

	// Inherited via IModelComponent
	virtual void update(float dt) override;
	virtual void init() override;
	virtual bool shouldDraw() override;
	virtual std::shared_ptr<Shader> getShader() override;
	virtual void draw(const glm::mat4 modelMatrix) override;

	std::shared_ptr<SkeletalModel> mSkeletalModel;
	Animator mAnimator{ nullptr };

};

