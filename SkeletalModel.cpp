#include "SkeletalModel.h"
#include "AssimpGLMHelpers.h"

#include "ResourceManager.h"

SkeletalModel::SkeletalModel()
{
    mShader = ResourceManager::getLoadedShader("SkeletalModel");
}

SkeletalModel::~SkeletalModel()
{

}

void SkeletalModel::loadModel(const std::string& fileName)
{
	mScene = mImporter.ReadFile(fileName.c_str(), aiProcess_Triangulate /*aiProcess_FlipUVs*/ | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (mScene)
	{
		initFromScene(fileName);
	}
	else
	{
		std::cout << " Something went wrong loading model from file: " << fileName << std::endl;
		exit(1);  // NOLINT(concurrency-mt-unsafe)
	}
}

void SkeletalModel::draw(const glm::mat4& modelMatrix, const std::vector<glm::mat4>& finalBoneMatrices)
{
    glUniformMatrix4fv(glGetUniformLocation(mShader->mId, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    // to show skinning
    glUniform1i(glGetUniformLocation(mShader->mId, "debugOpen"), 0);
    // bone to show the skinning
    glUniform1i(glGetUniformLocation(mShader->mId, "debugBone"), 2);

    for (int i = 0; i < finalBoneMatrices.size(); ++i)
    {
        std::string name = "finalBonesMatrices[" + std::to_string(i) + "]";
        glUniformMatrix4fv(glGetUniformLocation(mShader->mId, name.c_str()), 1, GL_FALSE, glm::value_ptr(finalBoneMatrices[i]));
    }

	for (const auto& mesh : mMeshes)
	{
		mesh->draw(mShader, modelMatrix);
	}
}

void SkeletalModel::initFromScene(const std::string& fileName)
{
	for (unsigned int i = 0; i < mScene->mNumMeshes; i++)
	{
		const aiMesh* paiMesh = mScene->mMeshes[i];
		initSingleMesh(paiMesh, fileName);
	}
}

void SkeletalModel::initSingleMesh(const aiMesh* paiMesh, const std::string& fileName)
{
    std::vector<VertexSkeletal> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
        VertexSkeletal vertex{};
        setVertexBoneDataToDefault(vertex);
        const aiVector3D& pPos = paiMesh->mVertices[i];

        if (paiMesh->HasVertexColors(0))
        {
            aiColor4D color = paiMesh->mColors[0][i]; // Access the first set of vertex colors
            vertex.mColor = { color.r, color.g, color.b, color.a };
        }

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
            if (std::strcmp(mLoadedTextures[i].path.data(), strDiffuse.C_Str()) == 0)
            {
                foundDif = true;
                foundIndexDif = i;
                break;
            }
        }

        if (foundDif)
        {
            textures.push_back(mLoadedTextures[foundIndexDif].tex);
        }
        else
        {
            std::string texturePath = strDiffuse.C_Str();
            std::ifstream file(texturePath);
            if (!file) // Check if the file exists
            {
                std::cout << texturePath << " does not exist, using default texture." << std::endl;
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
            if (std::strcmp(mLoadedTextures[i].path.data(), strSpec.C_Str()) == 0)
            {
                foundSpec = true;
                foundIndexSpec = i;
                break;
            }
        }

        if (foundSpec)
        {
            textures.push_back(mLoadedTextures[foundIndexSpec].tex);
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

    extractBoneWeightForVertices(vertices, paiMesh);

    mMeshes.push_back(std::make_unique<SkeletalMesh>(vertices, indices, textures));
}

void SkeletalModel::setVertexBoneDataToDefault(VertexSkeletal& vertex)

{
    for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
    {
        vertex.mBoneIDs[i] = -1;
        vertex.mWeights[i] = 0.0f;
    }
}

void SkeletalModel::extractBoneWeightForVertices(std::vector<VertexSkeletal>& vertices, const aiMesh* mesh)
{
    for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
    {
        int boneID = -1;
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
        if (mBoneInfoMap.find(boneName) == mBoneInfoMap.end())
        {
            BoneInfo newBoneInfo;
            newBoneInfo.id = mBoneCounter;
            newBoneInfo.offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat(
                mesh->mBones[boneIndex]->mOffsetMatrix);
            mBoneInfoMap[boneName] = newBoneInfo;
            boneID = mBoneCounter;
            mBoneCounter++;
        }
        else
        {
            boneID = mBoneInfoMap[boneName].id;
        }
        assert(boneID != -1);
        const auto weights = mesh->mBones[boneIndex]->mWeights;
        const int numWeights = mesh->mBones[boneIndex]->mNumWeights;

        //std::cout << boneName << " at id " << boneID;

        for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
        {
	        const int vertexId = weights[weightIndex].mVertexId;
	        const float weight = weights[weightIndex].mWeight;
            assert(vertexId <= vertices.size());
            setVertexBoneData(vertices[vertexId], boneID, weight);
        }
        //std::cout<<std::endl;
    }
}

void SkeletalModel::setVertexBoneData(VertexSkeletal& vertex, int boneID, float weight)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
    {
        if (vertex.mBoneIDs[i] < 0)
        {
            vertex.mWeights[i] = weight;
            vertex.mBoneIDs[i] = boneID;
            break;
        }
    }
}
