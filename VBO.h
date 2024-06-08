#pragma once


#include<glad/glad.h>

#include<glm/glm.hpp>
#include<vector>




// Structure to standardize the vertices used in the meshes
struct Vertex
{
	glm::vec4 mPosition;
	glm::vec4 mNormal;
	glm::vec4 mColor;
	glm::vec2 mTexUv;
	float mPadding1;
	float mPadding2;
};

constexpr int MAX_BONE_INFLUENCE = 4;


struct VertexSkeletal : Vertex
{
	//bone indexes which will influence this vertex
	int mBoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float mWeights[MAX_BONE_INFLUENCE];
};



class Vbo
{
public:
	GLuint mId;
	Vbo() = default;

	void init(std::vector<Vertex>& vertices);
	void init(std::vector<VertexSkeletal>& vertices);

	// Binds the VBO
	void bind();
	// Unbinds the VBO
	void unbind();
	// Deletes the VBO
	void Delete();
};