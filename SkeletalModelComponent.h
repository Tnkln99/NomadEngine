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
	void update(float dt) override;
	void init() override;
	bool shouldDraw() override;
	std::shared_ptr<Shader> getShader() override;
	void draw(const glm::mat4 modelMatrix) override;

	std::shared_ptr<SkeletalModel> mSkeletalModel;
	Animator mAnimator{ nullptr };
};

