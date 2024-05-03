#pragma once

#include "IComponent.h"
#include "Shader.h"

#include<glm/glm.hpp>

class IModelComponent : public IComponent
{
public:
	~IModelComponent() override = default;

	virtual bool shouldDraw() = 0;
	virtual std::shared_ptr<Shader> getShader() = 0;
	virtual void draw(const glm::mat4 modelMatrix) = 0;
};

