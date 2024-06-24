#pragma once

#include "IMesh.h"




class Mesh : public IMesh
{
public:
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
	void draw(std::shared_ptr<Shader> shader, glm::mat4 modelMatrix) override;
};
