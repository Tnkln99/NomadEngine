#pragma once

#include <map>

#include "Light.h"
#include "SkeletalMesh.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags


struct BoneInfo
{
	/*id is index in finalBoneMatrices*/
	int id;

	/*offset matrix transforms vertex from model space to bone space*/
	glm::mat4 offset;
};

class SkeletalModel
{
public:
	SkeletalModel();
	~SkeletalModel();

	glm::vec3 mPosition{0.0f};
	glm::vec3 mScale{1.0f};
	glm::vec3 mRotation{0, 90, 0};

	glm::mat4 mModelMatrix{1.0f};

	std::map<std::string, BoneInfo> mBoneInfoMap; //
	int mBoneCounter = 0;

	auto& getBoneInfoMap() { return mBoneInfoMap; }
	int& getBoneCount() { return mBoneCounter; }

	void loadModel(const std::string& fileName);

	void draw(Camera& camera, const Light& light, 
		std::vector<glm::mat4>& finalBoneMatrices, int debugBoneIndex);

private:
	std::shared_ptr<Shader> mShader{};

	struct TextureLoaded
	{
		Texture tex;
		std::string path;
	};

	void initFromScene(const std::string& fileName);
	void initSingleMesh(const aiMesh* paiMesh, const std::string& fileName);
	void setVertexBoneDataToDefault(Vertex& vertex);
	void extractBoneWeightForVertices(std::vector<Vertex>& vertices, const aiMesh* mesh);
	void setVertexBoneData(Vertex& vertex, int boneID, float weight);
	std::vector<TextureLoaded> mLoadedTextures;
	std::vector<SkeletalMesh> mMeshes;

	Assimp::Importer mImporter;
	const aiScene* mScene{};
};
