#pragma once

#include "AssimpGLMHelpers.h"
#include <vector>
#include <string>
#include <assimp/anim.h>

struct KeyPosition
{
    glm::vec3 position;
    float timeStamp;
};

struct KeyRotation
{
    glm::quat orientation;
    float timeStamp;
};

struct KeyScale
{
    glm::vec3 scale;
    float timeStamp;
};

class Bone
{
public:
    Bone(const std::string& name, int ID, const aiNodeAnim* channel);
    glm::mat4 getLocalTransform() const { return mLocalTransform; }
    std::string getBoneName() const { return mName; }
    int getBoneId() const { return mId; }

    int getPositionIndex(float animationTime);
    int getRotationIndex(float animationTime);
    int getScaleIndex(float animationTime);

    void update(float animationTime);

private:
    std::vector<KeyPosition> mPositions;
    std::vector<KeyRotation> mRotations;
    std::vector<KeyScale> mScales;
    int mNumPositions;
    int mNumRotations;
    int mNumScalings;

    glm::mat4 mLocalTransform;
    std::string mName;
    int mId;

    float getScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);
    glm::mat4 interpolatePosition(float animationTime);
    glm::mat4 interpolateRotation(float animationTime);
    glm::mat4 interpolateScaling(float animationTime);
};

