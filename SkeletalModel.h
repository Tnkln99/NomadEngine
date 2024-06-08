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

	std::map<std::string, BoneInfo> mBoneInfoMap; //
	int mBoneCounter = 0;

	auto& getBoneInfoMap() { return mBoneInfoMap; }
	int& getBoneCount() { return mBoneCounter; }

	void loadModel(const std::string& fileName);

	void draw(const glm::mat4& modelMatrix, 
		const std::vector<glm::mat4>& finalBoneMatrices);

	std::shared_ptr<Shader> getShader() {
		return mShader;
	}

private:
	std::shared_ptr<Shader> mShader{};

	struct TextureLoaded
	{
		Texture tex;
		std::string path;
	};

	void initFromScene(const std::string& fileName);
	void initSingleMesh(const aiMesh* paiMesh, const std::string& fileName);
	void setVertexBoneDataToDefault(VertexSkeletal& vertex);
	void extractBoneWeightForVertices(std::vector<VertexSkeletal>& vertices, const aiMesh* mesh);
	void setVertexBoneData(VertexSkeletal& vertex, int boneID, float weight);
	std::vector<TextureLoaded> mLoadedTextures;
	std::vector<std::unique_ptr<IMesh>> mMeshes;

	Assimp::Importer mImporter;
	const aiScene* mScene{};
};
