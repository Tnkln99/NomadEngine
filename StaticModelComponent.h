#pragma once

#include "IModelComponent.h"
#include "StaticModel.h"
#include <memory>


class StaticModelComponent : public IModelComponent
{
public:
	StaticModelComponent();
	
	// Inherited via IComponent
	void update(float dt) override;
	void init() override;

	// Inherited via IModelComponent
	std::shared_ptr<Shader> getShader() override;
	void draw(const glm::mat4 modelMatrix) override;
	bool shouldDraw() override;

	std::shared_ptr<StaticModel> mStaticModel;
};

