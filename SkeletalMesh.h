#ifndef SKELATALMESH_CLASS_H
#define SKELATALMESH_CLASS_H

#include"VAO.h"
#include"EBO.h"
#include"Texture.h"


class SkeletalMesh
{
public:
	std::vector <Vertex> mVertices;
	std::vector <GLuint> mIndices;
	std::vector <Texture> mTextures;
	// Store VAO in public so it can be used in the Draw function
	Vao mVao;

	// Initializes the mesh
	SkeletalMesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	// Draws the mesh
	void draw(Shader& shader);
};



#endif

