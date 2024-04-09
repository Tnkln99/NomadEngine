#pragma once


#include<glad/glad.h>

#include<glm/glm.hpp>
#include<vector>



constexpr int MAX_BONE_INFLUENCE = 4;

// Structure to standardize the vertices used in the meshes
struct Vertex
{
	glm::vec3 mPosition;
	glm::vec3 mNormal;
	glm::vec3 mColor;
	glm::vec2 mTexUv;

	//bone indexes which will influence this vertex
	int mBoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float mWeights[MAX_BONE_INFLUENCE];
};



class Vbo
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint mId;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	explicit Vbo(std::vector<Vertex>& vertices);

	// Binds the VBO
	void bind();
	// Unbinds the VBO
	void unbind();
	// Deletes the VBO
	void Delete();
};