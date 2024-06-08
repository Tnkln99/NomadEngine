#pragma once

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



class StaticModel
{
public:
	StaticModel();
	~StaticModel();

	void loadModel(const std::string& fileName);

	void draw(glm::mat4 modelMatrix);
	void draw(glm::mat4 modelMatrix, std::shared_ptr<Shader> shader);

	std::shared_ptr<Shader> getShader() {
		return mShader;
	}
private:
	std::shared_ptr<Shader> mShader{};
	struct TextureLoaded
	{
		Texture mTex;
		std::string mPath;
	};
	
	void initFromScene(const std::string& fileName);
	void initSingleMesh(const aiMesh* paiMesh, const std::string& fileName);
	std::vector<TextureLoaded> mLoadedTextures;
	std::vector<std::unique_ptr<IMesh>> mMeshes;

	Assimp::Importer mImporter;
	const aiScene* mScene{};
};


