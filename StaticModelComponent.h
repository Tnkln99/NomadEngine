#pragma once

#include "IComponent.h"
#include "StaticModel.h"
#include <memory>


class StaticModelComponent : public IComponent
{
public:
	StaticModelComponent(Camera& camera, Light& light);
	std::shared_ptr<StaticModel> mStaticModel;
	void update() override;
	void init() override;
private:
	Camera& mCamera;
	Light& mLight;
};

