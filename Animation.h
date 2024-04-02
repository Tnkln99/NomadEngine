#pragma once

#include "SkeletalModel.h"
#include "Bone.h"

struct AssimpNodeData
{
	glm::mat4 transformation{};
	std::string name;
	int childrenCount{};
	std::vector<AssimpNodeData> children;
};

class Animation
{
public:
	Animation() = default;

	Animation(const std::string& animationPath, SkeletalModel* model);

	~Animation() = default;


	Bone* findBone(const std::string& name);


	float getTicksPerSecond() const { return mTicksPerSecond; }

	float getDuration() const { return mDuration; }

	const AssimpNodeData& getRootNode() { return mRootNode; }

	const std::map<std::string, BoneInfo>& getBoneIdMap()
	{
		return mBoneInfo;
	}

private:
	void readMissingBones(const aiAnimation* animation, SkeletalModel& model);

	void readHeirarchyData(AssimpNodeData& dest, const aiNode* src);
	float mDuration;
	int mTicksPerSecond;
	std::vector<Bone> mBones;
	AssimpNodeData mRootNode;
	std::map<std::string, BoneInfo> mBoneInfo;
};
