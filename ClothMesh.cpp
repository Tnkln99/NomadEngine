#include "ClothMesh.h"

#include <random>
#include <unordered_set>

#include "ResourceManager.h"
#include "Timer.h"

ClothMesh::ClothMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
    : IMesh(vertices, indices, textures)
{
    mVao.bind();

    mVbo.init(vertices);

    Ebo ebo{};
    ebo.init(indices);

    mVao.linkAttrib(mVbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, mPosition));
    mVao.linkAttrib(mVbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));
    mVao.linkAttrib(mVbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, mColor));
    mVao.linkAttrib(mVbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, mTexUv));

    mVao.unbind();
    mVbo.unbind();
    ebo.unbind();

    // creating ssbos..

    // Build neighbor relationships
    std::vector<std::unordered_set<uint32_t>> neighbors(vertices.size());

    /*for (size_t i = 0; i < indices.size(); i += 3) {
        uint32_t a = indices[i];
        uint32_t b = indices[i + 1];
        uint32_t c = indices[i + 2];

        // Insert direct neighbors
        neighbors[a].insert(b);
        neighbors[a].insert(c);
        neighbors[b].insert(a);
        neighbors[b].insert(c);
        neighbors[c].insert(a);
        neighbors[c].insert(b);
    }*/

    for(int i = 0; i < vertices.size(); i++)
    {
	    for(int j = 0; j < vertices.size(); j++)
	    {
		    if(i==j)
		    {
                continue;
		    }
            if(glm::distance(vertices[i].mPosition, vertices[j].mPosition) < 1.4f)
            {
                neighbors[i].insert(j);
            }
	    }
    }

    // Flatten the neighbors list for GPU processing
    std::vector<uint32_t> neighborOffsets(vertices.size() + 1);
    std::vector<uint32_t> neighborData;

    std::vector<glm::vec4> prevPositionsTmp;
    prevPositionsTmp.reserve(vertices.size());

    size_t offset = 0;

    for (uint32_t i = 0; i < vertices.size(); ++i) {
        prevPositionsTmp.push_back(vertices[i].mPosition);
        neighborOffsets[i] = offset;
        for (uint32_t neighbor : neighbors[i]) {
            neighborData.push_back(neighbor);
            offset++;
        }
    }
    neighborOffsets[vertices.size()] = offset;
 
    // Upload neighbor data to the GPU
    glGenBuffers(1, &mNeighborOffsetBuffer);
    glGenBuffers(1, &mNeighborDataBuffer);
    glGenBuffers(1, &mPreviousPositionsBuffer);
    glGenBuffers(1, &mNewPositionsBuffer);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mNeighborOffsetBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, neighborOffsets.size() * sizeof(uint32_t), neighborOffsets.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mNeighborDataBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, neighborData.size() * sizeof(uint32_t), neighborData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mPreviousPositionsBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec4) * prevPositionsTmp.size(), prevPositionsTmp.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mNewPositionsBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec4) * vertices.size(), nullptr, GL_STATIC_DRAW);
}

void ClothMesh::draw(std::shared_ptr<Shader> shader, glm::mat4 modelMatrix)
{
    updateCloth(modelMatrix);

    shader->activate();
    mVao.bind();
    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    if (!mTextures.empty())
    {
        glUniform1i(glGetUniformLocation(shader->mId, "haveTextures"), 1);
    }
    else
    {
        glUniform1i(glGetUniformLocation(shader->mId, "haveTextures"), 0);
    }

    for (unsigned int i = 0; i < mTextures.size(); i++)
    {
        std::string num;
        std::string type = mTextures[i].mType;
        if (type == "diffuse")
        {
            num = std::to_string(numDiffuse++);
        }
        else if (type == "specular")
        {
            num = std::to_string(numSpecular++);
        }
        mTextures[i].texUnit(shader, (type + num).c_str(), i);
        mTextures[i].bind();
    }

    // Draw the actual mesh
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    mVao.unbind();
}

void ClothMesh::updateCloth(glm::mat4 modelMatrix)
{
    const auto computeProgramFirstPass = ResourceManager::getLoadedShader("ComputationClothFirstPass");
    const auto computeProgramSecondPass = ResourceManager::getLoadedShader("ComputationClothSecondPass");
    if (!computeProgramFirstPass || !computeProgramSecondPass) {
        return;
    }

    // First pass: Calculate new positions
    computeProgramFirstPass->activate();
    glm::mat4 invModelMatrix = glm::inverse(modelMatrix);

    std::default_random_engine rndEngine((unsigned)time(nullptr));
    std::uniform_real_distribution<float> rd(1.0f, 20.0f);

    float windX = cos(glm::radians(-glfwGetTime() * 360.0f)) * (rd(rndEngine) - rd(rndEngine));
    float windY = sin(glm::radians(glfwGetTime() * 360.0f)) * (rd(rndEngine) - rd(rndEngine));

    glUniform1f(glGetUniformLocation(computeProgramFirstPass->mId, "deltaTime"), Timer::getDeltaTime());
    glUniform4fv(glGetUniformLocation(computeProgramFirstPass->mId, "gravity"), 1, glm::value_ptr(glm::vec4{ windX,-9.8f,windY,0}));
    glUniformMatrix4fv(glGetUniformLocation(computeProgramFirstPass->mId, "invModelMatrix"), 1, GL_FALSE, glm::value_ptr(invModelMatrix));

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, mVbo.mId);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, mPreviousPositionsBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, mNewPositionsBuffer);

    const GLuint numVertices = mVertices.size();
    constexpr GLuint localSizeX = 16; // Must match local_size_x in the compute shader
    const GLuint workGroupsX = (numVertices + localSizeX - 1) / localSizeX; // Ensure enough work-groups

    glDispatchCompute(workGroupsX, 1, 1);

    // Memory barrier to ensure all writes are complete before the second pass
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

    // Second pass: Apply constraints
    computeProgramSecondPass->activate();

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, mVbo.mId);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, mNewPositionsBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, mNeighborOffsetBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, mNeighborDataBuffer);

    glDispatchCompute(workGroupsX, 1, 1);

    // Memory barrier to ensure all writes are complete before using the buffer
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
    }
}
