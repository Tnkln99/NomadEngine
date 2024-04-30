#pragma once

#include "StaticModel.h"
#include "Window.h"
#include <memory>
#include <vector>

class Renderer
{
public:
	void render(const std::shared_ptr<StaticModel> staticModel, glm::mat4 modelMatrix);
	void registerCamera(std::shared_ptr<Camera> camera);
	void registerLight(std::shared_ptr<Light> light);
private:
	std::shared_ptr<Camera> mCurrentCamera = nullptr;
	std::vector<std::shared_ptr<Light>> mLights;
};

