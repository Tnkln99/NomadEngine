#include "Animation.h"

Animation::Animation(const std::string& animationPath, SkeletalModel* model)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate /*aiProcess_FlipUVs*/ | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
    assert(scene && scene->mRootNode);
    auto animation = scene->mAnimations[0];
    mDuration = animation->mDuration;
    mTicksPerSecond = animation->mTicksPerSecond;
    readHeirarchyData(mRootNode, scene->mRootNode);
    readMissingBones(animation, *model);
}

Bone* Animation::findBone(const std::string& name)

{
    auto iter = std::find_if(mBones.begin(), mBones.end(),
        [&](const Bone& Bone)
        {
            return Bone.getBoneName() == name;
        }
    );
    if (iter == mBones.end()) return nullptr;
    else return &(*iter);
}

void Animation::readMissingBones(const aiAnimation* animation, SkeletalModel& model)

{
    int size = animation->mNumChannels;

    auto& boneInfoMap = model.getBoneInfoMap();//getting boneInfoMap from Model class
    int& boneCount = model.getBoneCount(); //getting the m_BoneCounter from Model class

    //reading channels(bones engaged in an animation and their keyframes)
    for (int i = 0; i < size; i++)
    {
        auto channel = animation->mChannels[i];
        std::string boneName = channel->mNodeName.data;

        if (boneInfoMap.find(boneName) == boneInfoMap.end())
        {
            boneInfoMap[boneName].id = boneCount;
            boneCount++;
        }
        mBones.emplace_back(channel->mNodeName.data,
            boneInfoMap[channel->mNodeName.data].id, channel);
    }

    mBoneInfo = boneInfoMap;
}

void Animation::readHeirarchyData(AssimpNodeData& dest, const aiNode* src)
{
    assert(src);

    dest.name = src->mName.data;
    dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
    dest.childrenCount = src->mNumChildren;

    for (int i = 0; i < src->mNumChildren; i++)
    {
        AssimpNodeData newData;
        readHeirarchyData(newData, src->mChildren[i]);
        dest.children.push_back(newData);
    }
}
