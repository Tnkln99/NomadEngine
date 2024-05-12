#pragma once
#include "Light.h"
#include "IComponent.h"

class LightComponent : public IComponent
{
public:
	LightComponent();

	// Inherited via IComponent
	void update(float dt) override;
	void beginPlay() override;
	void init() override;

	std::shared_ptr<Light> mLight;
};

