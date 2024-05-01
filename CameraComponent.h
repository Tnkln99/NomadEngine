#pragma once

#include "IComponent.h"
#include "Camera.h"
#include <memory>

class CameraComponent : public IComponent
{
public:
	CameraComponent();
	// Inherited via IComponent
	virtual void update(float dt) override;
	virtual void init() override;

	const std::shared_ptr<Camera> getCamera() {
		return mCamera;
	}
private:
	std::shared_ptr<Camera> mCamera{};
};

