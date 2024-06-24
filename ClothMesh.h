#pragma once

#include "IMesh.h"

class ClothMesh : public IMesh
{
public:
	ClothMesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
	void draw(std::shared_ptr<Shader> shader, glm::mat4 modelMatrix) override;
private:
	void updateCloth(glm::mat4 modelMatrix);

	GLuint mPreviousPositionsBuffer;
	GLuint mNewPositionsBuffer;
	GLuint mNeighborOffsetBuffer;
	GLuint mNeighborDataBuffer;
	Vbo mVbo;
};

