#pragma once

#include "VAO.h"
#include "EBO.h"
#include "Texture.h"

#define _USE_MATH_DEFINES
#include <math.h>



class IMesh
{
public:
	virtual ~IMesh() = default;
	virtual void draw(std::shared_ptr<Shader> shader) = 0;
protected:
	IMesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
	IMesh(std::vector <VertexSkeletal>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
	std::vector <Vertex> mVertices;
	std::vector <VertexSkeletal> mSkeletalVertices;
	std::vector <GLuint> mIndices;
	std::vector <Texture> mTextures;

	// Store VAO in public so it can be used in the Draw function
	Vao mVao;
};

