#include "StaticModel.h"
#include "ResourceManager.h"
#include "ClothMesh.h"


#include <assimp/postprocess.h>

StaticModel::StaticModel()
{
    mShader = ResourceManager::getLoadedShader("StaticModel");
}

StaticModel::~StaticModel()
{
   
}

void StaticModel::loadModel(const std::string& fileName)
{
	mScene = mImporter.ReadFile(fileName.c_str(), aiProcess_Triangulate /*aiProcess_FlipUVs*/ | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
    
	if(mScene)
	{
		initFromScene(fileName);
	}
	else
	{
		std::cout << " Something went wrong loading model from file: " << fileName << std::endl;
		exit(1);  // NOLINT(concurrency-mt-unsafe)
	}
}

void StaticModel::draw(const glm::mat4 modelMatrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mShader->mId, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	for(auto & mesh : mMeshes)
	{
		mesh->draw(mShader);
	}
}

void StaticModel::draw(const glm::mat4 modelMatrix, std::shared_ptr<Shader> shader)
{
    glUniformMatrix4fv(glGetUniformLocation(mShader->mId, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    for (auto& mesh : mMeshes)
    {
        mesh->draw(shader);
    }
}

void StaticModel::initFromScene(const std::string& fileName)
{
    for(unsigned int i = 0; i < mScene->mNumMeshes; i++)
    {
        const aiMesh* paiMesh = mScene->mMeshes[i];
        initSingleMesh(paiMesh, fileName);
    }
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void StaticModel::initSingleMesh(const aiMesh* paiMesh, const std::string& fileName)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    std::cout << paiMesh->mName.C_Str() << std::endl;

    for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
        Vertex vertex{};
        const aiVector3D& pPos = paiMesh->mVertices[i];

        vertex.mPosition = glm::vec4(pPos.x, pPos.y, pPos.z, 1.0f);

        if (paiMesh->mNormals) {
            const aiVector3D& pNormal = paiMesh->mNormals[i];
            vertex.mNormal = glm::vec4(pNormal.x, pNormal.y, pNormal.z, 1.0f);
        }
        else {
            aiVector3D Normal(0.0f, 1.0f, 0.0f);
            vertex.mNormal = glm::vec4(Normal.x, Normal.y, Normal.z, 1.0f);
        }

        if (paiMesh->HasTextureCoords(0)) {
            vertex.mTexUv = glm::vec2(paiMesh->mTextureCoords[0][i].x, paiMesh->mTextureCoords[0][i].y);
        }
        else
        {
            vertex.mTexUv = glm::vec2{ 0.0f };
        }
       

        vertices.push_back(vertex);
    }

    // Populate the index buffer
    for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
        const aiFace& face = paiMesh->mFaces[i];
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }

    aiMaterial* material = mScene->mMaterials[paiMesh->mMaterialIndex];

    // getting the diffuse texture I only need one diffuse texture per mesh in any cases my shader can process one diffuse texture
    aiString strDiffuse;
    material->GetTexture(aiTextureType_DIFFUSE, 0, &strDiffuse);
    aiString path;
    if (strDiffuse.C_Str() != nullptr && material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
    {
        bool foundDif = false;
        int foundIndexDif = 0;
        for (int i = 0; i < mLoadedTextures.size(); i++)
        {
            if (std::strcmp(mLoadedTextures[i].mPath.data(), strDiffuse.C_Str()) == 0)
            {
                foundDif = true;
                foundIndexDif = i;
                break;
            }
        }

        if (foundDif)
        {
            textures.push_back(mLoadedTextures[foundIndexDif].mTex);
        }
        else
        {
            std::string texturePath = strDiffuse.C_Str();
            std::ifstream file(texturePath);
            if (!file) // Check if the file exists
            {
                std::cout << texturePath  <<" does not exist, using default texture." << std::endl;
                // Set the path to your default texture here
                texturePath = "planks.png";
            }
            else
            {
                std::cout << "Loaded diffuse texture from file " << texturePath << std::endl;
            }

            Texture diffuse{ texturePath.c_str(), "diffuse", 0 };
            textures.push_back(diffuse);
            mLoadedTextures.push_back({ diffuse, texturePath });
        }
    }

    
    // same for speculer
    aiString strSpec;
    material->GetTexture(aiTextureType_SPECULAR, 0, &strSpec);
    if (strSpec.C_Str() != nullptr && material->GetTexture(aiTextureType_SPECULAR, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
    {
        bool foundSpec = false;
        int foundIndexSpec = 0;
        for (int i = 0; i < mLoadedTextures.size(); i++)
        {
            if (std::strcmp(mLoadedTextures[i].mPath.data(), strSpec.C_Str()) == 0)
            {
                foundSpec = true;
                foundIndexSpec = i;
                break;
            }
        }

        if (foundSpec)
        {
            textures.push_back(mLoadedTextures[foundIndexSpec].mTex);
        }
        else
        {
            std::string texturePath = strSpec.C_Str();
            std::ifstream file(texturePath);
            if (!file) // Check if the file exists
            {
                std::cout << texturePath << " does not exist, using default texture." << std::endl;
                // Set the path to your default texture here
                texturePath = "planksSpec.png";
            }
            else
            {
                std::cout << "Loaded speculer texture from file " << texturePath << std::endl;
            }

            Texture speculer{ strSpec.C_Str(), "speculer", 1 };
            textures.push_back(speculer);
            mLoadedTextures.push_back({ speculer, strSpec.C_Str() });
        }
    }
    if(strstr(paiMesh->mName.C_Str(), "ClothSim") != NULL)
    {
        mMeshes.push_back(std::make_unique<ClothMesh>(vertices, indices, textures));
    }
    else
    {
        mMeshes.push_back(std::make_unique<Mesh>(vertices, indices, textures));
    }
}


