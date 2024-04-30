#pragma once
#include "Light.h"
#include "IComponent.h"

class LightComponent : public IComponent
{
public:
	LightComponent();

	// Inherited via IComponent
	virtual void update() override;
	virtual void init() override;

	std::shared_ptr<Light> mLight;
};

