#pragma once

#include "StaticModel.h"
#include "Window.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include <memory>
#include <vector>

class Renderer
{
public:
	void render(const std::shared_ptr<StaticModel> staticModel, glm::mat4 modelMatrix);
	void registerCamera(std::shared_ptr<CameraComponent> camera);
	void registerLight(std::shared_ptr<LightComponent> light);
	void registerWindow(std::shared_ptr<Window> window);
private:
	std::shared_ptr<CameraComponent> mCurrentCamera = nullptr;
	std::vector<std::shared_ptr<LightComponent>> mLights;
	std::shared_ptr<Window> mWindow;
};

