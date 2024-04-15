#pragma once

#include "VAO.h"


#include"EBO.h"
#include"Texture.h"

class Mesh
{
public:
	std::vector <Vertex> mVertices;
	std::vector <GLuint> mIndices;
	std::vector <Texture> mTextures;
	// Store VAO in public so it can be used in the Draw function
	Vao mVao;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	// Draws the mesh
	virtual void draw(std::shared_ptr<Shader> shader);
};
