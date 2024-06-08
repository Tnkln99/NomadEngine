#include "ClothMesh.h"
#include "ResourceManager.h"

ClothMesh::ClothMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
    : IMesh(vertices, indices, textures)
{
    mVao.bind();

    // Initialize both buffers
    glGenBuffers(1, &mInBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mInBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &mOutBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mOutBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // Unbind buffer
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    mVbo.init(vertices);

    // Generate Element Buffer Object and link it to indices
    Ebo ebo{};
    ebo.init(indices);

    // Link VBO attributes such as coordinates and colors to VAO
    mVao.linkAttrib(mVbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    mVao.linkAttrib(mVbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    mVao.linkAttrib(mVbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    mVao.linkAttrib(mVbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

    mVao.unbind();
    mVbo.unbind();
    ebo.unbind();
}

void ClothMesh::draw(std::shared_ptr<Shader> shader)
{
    updateCloth();

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

void ClothMesh::updateCloth()
{
    const auto computeProgram = ResourceManager::getLoadedShader("ComputationCloth");
    if (!computeProgram)
    {
        return;
    }

    mVao.bind();

    computeProgram->activate();

    if (mUseInBufferAsInput)
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, mInBuffer);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, mOutBuffer);
    }
    else
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, mOutBuffer);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, mInBuffer);
    }

    GLuint numVertices = mVertices.size();
    GLuint localSizeX = 16; // Must match local_size_x in the compute shader
    GLuint workGroupsX = (numVertices + localSizeX - 1) / localSizeX; // Ensure enough workgroups

    glDispatchCompute(workGroupsX, 1, 1);

    // Memory barrier to ensure all writes are complete before using the buffer
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

    // Swap buffers
    mUseInBufferAsInput = !mUseInBufferAsInput;

    // Update VBO with the latest data for rendering
    glBindBuffer(GL_COPY_READ_BUFFER, mUseInBufferAsInput ? mOutBuffer : mInBuffer);
    glBindBuffer(GL_COPY_WRITE_BUFFER, mVbo.mId);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, sizeof(Vertex) * numVertices);
    glBindBuffer(GL_COPY_READ_BUFFER, 0);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error: " << error << std::endl;
    }
}
