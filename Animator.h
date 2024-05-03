#pragma once

#include "Animation.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

class Animator
{
public:
	explicit Animator(Animation* animation);

	void updateAnimation(float dt);

	void playAnimation(Animation* pAnimation);

	void calculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);

	std::vector<glm::mat4> getFinalBoneMatrices();

	void setCurrentAnimation(Animation* currentAnimation);
private:
	std::vector<glm::mat4> mFinalBoneMatrices;
	Animation* mCurrentAnimation;
	float mCurrentTime;
	float mDeltaTime;

};