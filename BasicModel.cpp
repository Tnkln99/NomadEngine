#include "BasicModel.h"

#include <assimp/postprocess.h>

BasicModel::BasicModel() = default;

BasicModel::~BasicModel()
{
    shader.Delete();
}

void BasicModel::loadModel(const std::string& fileName)
{
    mModelMatrix = glm::translate(mModelMatrix, mPosition);
    
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

void BasicModel::draw(Camera& camera, const Light& light)
{
    shader.activate();
    glUniformMatrix4fv(glGetUniformLocation(shader.mId, "model"), 1, GL_FALSE, glm::value_ptr(mModelMatrix));
    glUniform4f(glGetUniformLocation(shader.mId, "lightColor"), light.mLightColor.x, light.mLightColor.y, light.mLightColor.z, light.mLightColor.w);
    glUniform3f(glGetUniformLocation(shader.mId, "lightPos"), light.mLightPos.x, light.mLightPos.y, light.mLightPos.z);
    // Take care of the camera Matrix
    glUniform3f(glGetUniformLocation(shader.mId, "camPos"), camera.mPosition.x, camera.mPosition.y, camera.mPosition.z);
    camera.matrix(shader);
	for(auto & mesh : mMeshes)
	{
		mesh.draw(shader);
	}
}

void BasicModel::initFromScene(const std::string& fileName)
{
    for(unsigned int i = 0; i < mScene->mNumMeshes; i++)
    {
        const aiMesh* paiMesh = mScene->mMeshes[i];
        initSingleMesh(paiMesh, fileName);
    }
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void BasicModel::initSingleMesh(const aiMesh* paiMesh, const std::string& fileName)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
        Vertex vertex{};
        const aiVector3D& pPos = paiMesh->mVertices[i];

        vertex.mPosition = glm::vec3(pPos.x, pPos.y, pPos.z);

        if (paiMesh->mNormals) {
            const aiVector3D& pNormal = paiMesh->mNormals[i];
            vertex.mNormal = glm::vec3(pNormal.x, pNormal.y, pNormal.z);
        }
        else {
            aiVector3D Normal(0.0f, 1.0f, 0.0f);
            vertex.mNormal = glm::vec3(Normal.x, Normal.y, Normal.z);
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
    


    Mesh mesh{ vertices, indices, textures };
    mMeshes.push_back(mesh);
}


