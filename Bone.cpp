#include "Bone.h"

#include <glm/gtx/quaternion.hpp>

Bone::Bone(const std::string& name, int ID, const aiNodeAnim* channel) :
    mName(name),
    mId(ID),
    mLocalTransform(1.0f)
{
    mNumPositions = channel->mNumPositionKeys;

    for (int positionIndex = 0; positionIndex < mNumPositions; ++positionIndex)
    {
        aiVector3D aiPosition = channel->mPositionKeys[positionIndex].mValue;
        float timeStamp = channel->mPositionKeys[positionIndex].mTime;
        KeyPosition data;
        data.position = AssimpGLMHelpers::GetGLMVec(aiPosition);
        data.timeStamp = timeStamp;
        mPositions.push_back(data);
    }

    mNumRotations = channel->mNumRotationKeys;
    for (int rotationIndex = 0; rotationIndex < mNumRotations; ++rotationIndex)
    {
        aiQuaternion aiOrientation = channel->mRotationKeys[rotationIndex].mValue;
        float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
        KeyRotation data;
        data.orientation = AssimpGLMHelpers::GetGLMQuat(aiOrientation);
        data.timeStamp = timeStamp;
        mRotations.push_back(data);
    }

    mNumScalings = channel->mNumScalingKeys;
    for (int keyIndex = 0; keyIndex < mNumScalings; ++keyIndex)
    {
        aiVector3D scale = channel->mScalingKeys[keyIndex].mValue;
        float timeStamp = channel->mScalingKeys[keyIndex].mTime;
        KeyScale data;
        data.scale = AssimpGLMHelpers::GetGLMVec(scale);
        data.timeStamp = timeStamp;
        mScales.push_back(data);
    }
}

int Bone::getPositionIndex(float animationTime)
{
    for (int index = 0; index < mNumPositions - 1; ++index)
    {
        if (animationTime < mPositions[index + 1].timeStamp)
            return index;
    }
    assert(0);
}

int Bone::getRotationIndex(float animationTime)
{
    for (int index = 0; index < mNumRotations - 1; ++index)
    {
        if (animationTime < mRotations[index + 1].timeStamp)
            return index;
    }
    assert(0);
}

int Bone::getScaleIndex(float animationTime)
{
    for (int index = 0; index < mNumScalings - 1; ++index)
    {
        if (animationTime < mScales[index + 1].timeStamp)
            return index;
    }
    assert(0);
}

void Bone::update(float animationTime)
{
    glm::mat4 translation = interpolatePosition(animationTime);
    glm::mat4 rotation = interpolateRotation(animationTime);
    glm::mat4 scale = interpolateScaling(animationTime);
    mLocalTransform = translation * rotation * scale;
}

float Bone::getScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
    float scaleFactor = 0.0f;
    float midWayLength = animationTime - lastTimeStamp;
    float framesDiff = nextTimeStamp - lastTimeStamp;
    scaleFactor = midWayLength / framesDiff;
    return scaleFactor;
}

glm::mat4 Bone::interpolatePosition(float animationTime)
{
    if (1 == mNumPositions)
        return glm::translate(glm::mat4(1.0f), mPositions[0].position);

    int p0Index = getPositionIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = getScaleFactor(mPositions[p0Index].timeStamp,
        mPositions[p1Index].timeStamp, animationTime);
    glm::vec3 finalPosition = glm::mix(mPositions[p0Index].position,
        mPositions[p1Index].position, scaleFactor);
    return glm::translate(glm::mat4(1.0f), finalPosition);
}

glm::mat4 Bone::interpolateRotation(float animationTime)
{
    if (1 == mNumRotations)
    {
        auto rotation = glm::normalize(mRotations[0].orientation);
        return glm::toMat4(rotation);
    }

    int p0Index = getRotationIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = getScaleFactor(mRotations[p0Index].timeStamp,
        mRotations[p1Index].timeStamp, animationTime);
    glm::quat finalRotation = glm::slerp(mRotations[p0Index].orientation,
        mRotations[p1Index].orientation, scaleFactor);
    finalRotation = glm::normalize(finalRotation);
    return glm::toMat4(finalRotation);
}

glm::mat4 Bone::interpolateScaling(float animationTime)
{
    if (1 == mNumScalings)
        return glm::scale(glm::mat4(1.0f), mScales[0].scale);

    int p0Index = getScaleIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = getScaleFactor(mScales[p0Index].timeStamp,
        mScales[p1Index].timeStamp, animationTime);
    glm::vec3 finalScale = glm::mix(mScales[p0Index].scale, mScales[p1Index].scale
        , scaleFactor);
    return glm::scale(glm::mat4(1.0f), finalScale);
}
