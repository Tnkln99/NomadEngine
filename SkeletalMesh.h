#pragma once

#include"IMesh.h"


class SkeletalMesh : public IMesh
{
public:
	SkeletalMesh(std::vector <VertexSkeletal>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
	void draw(std::shared_ptr<Shader> shader, glm::mat4 modelMatrix) override;
};
