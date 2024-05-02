#pragma once

#include "IModelComponent.h"
#include "StaticModel.h"
#include <memory>


class StaticModelComponent : public IModelComponent
{
public:
	StaticModelComponent();
	
	// Inherited via IComponent
	virtual void update(float dt) override;
	virtual void init() override;

	// Inherited via IModelComponent
	virtual std::shared_ptr<Shader> getShader() override;
	virtual void draw(const glm::mat4 modelMatrix) override;
	virtual bool shouldDraw() override;

	std::shared_ptr<StaticModel> mStaticModel;
};

