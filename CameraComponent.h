#pragma once

#include "IComponent.h"
#include "Camera.h"
#include <memory>

class CameraComponent : public IComponent
{
public:
	CameraComponent();
	// Inherited via IComponent
	void update(float dt) override;
	void beginPlay() override;
	void init() override;

	const std::shared_ptr<Camera> getCamera() {
		return mCamera;
	}
private:
	std::shared_ptr<Camera> mCamera{};
};

