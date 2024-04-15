#include "SkeletalMesh.h"

SkeletalMesh::SkeletalMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) : mVertices(vertices), mIndices(indices), mTextures(textures)
{
	mVao.bind();
	// Generates Vertex Buffer Object and links it to vertices
	Vbo VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	Ebo EBO(indices);
	// Links VBO attributes such as coordinates and colors to VAO
	// Positions
	mVao.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	// Normal
	mVao.linkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	// Color 
	mVao.linkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	// Texture
	mVao.linkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// BoneId's
	mVao.linkAttrib(VBO, 4, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, mBoneIDs));
	// Weights
	mVao.linkAttrib(VBO, 5, 4, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, mWeights));
	// Unbind all to prevent accidentally modifying them
	mVao.unbind();
	VBO.unbind();
	EBO.unbind();
}

void SkeletalMesh::draw(std::shared_ptr<Shader> shader)
{
	mVao.bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

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
