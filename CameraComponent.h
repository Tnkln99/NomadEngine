#pragma once

#include "IComponent.h"
#include "Camera.h"
#include <memory>

class CameraComponent : public IComponent
{
	CameraComponent();
	// Inherited via IComponent
	virtual void update() override;
	virtual void init() override;

	bool mIsMain;
private:
	Camera mCamera{};
};

