#pragma once

#include "Mesh.h"
#include "Light.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class StaticModel
{
public:
	StaticModel() = default;
	~StaticModel();

	glm::vec3 mPosition{ 0.0f };
	glm::vec3 mScale{ 1.0f };
	glm::vec3 mRotation{ 1.0f };

	glm::mat4 mModelMatrix{ 1.0f };

	void loadModel(const std::string& fileName);

	void draw(Camera& camera, const Light& light);
private:
	Shader shader{ "StaticModel.vert", "StaticModel.frag" };
	struct TextureLoaded
	{
		Texture mTex;
		std::string mPath;
	};
	
	void initFromScene(const std::string& fileName);
	void initSingleMesh(const aiMesh* paiMesh, const std::string& fileName);
	std::vector<TextureLoaded> mLoadedTextures;
	std::vector<Mesh> mMeshes;

	Assimp::Importer mImporter;
	const aiScene* mScene{};
};


