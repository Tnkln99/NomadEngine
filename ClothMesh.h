#pragma once

#include "IMesh.h"

class ClothMesh : public IMesh
{
public:
	ClothMesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
	void draw(std::shared_ptr<Shader> shader) override;
private:
	void updateCloth();

	Vbo mVbo;
	GLuint mInBuffer, mOutBuffer;
	bool mUseInBufferAsInput = true; // Flag to swap buffers
};

