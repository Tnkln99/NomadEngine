#ifndef BASICMODEL_CLASS_H
#define BASICMODEL_CLASS_H

#include "Mesh.h"
#include "Light.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

class BasicModel
{
public:
	BasicModel();
	~BasicModel();

	glm::vec3 mPosition{ 0.0f };
	glm::vec3 mScale{ 1.0f };
	glm::vec3 mRotation{ 1.0f };

	glm::mat4 mModelMatrix{ 1.0f };

	void loadModel(const std::string& fileName);

	void draw(Camera& camera, const Light& light);
private:
	Shader shader{ "BasicModel.vert", "BasicModel.frag" };
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

#endif

