#include "IMesh.h"

IMesh::IMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) : mVertices(vertices), mIndices(indices), mTextures(textures)
{
}

IMesh::IMesh(std::vector<VertexSkeletal>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) : mSkeletalVertices(vertices), mIndices(indices), mTextures(textures)
{
}
