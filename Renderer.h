#pragma once

#include "Window.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "IModelComponent.h"

#include <memory>
#include <vector>


enum RenderMode
{
	WIREFRAME,
	POINT,
	FILL
};

class Renderer
{
public:
	void render() const;
	void registerCamera(std::shared_ptr<CameraComponent> camera);
	void registerLight(const std::shared_ptr<LightComponent>& light);
	void registerModel(const std::shared_ptr<IModelComponent>& model);
	void registerWindow(std::shared_ptr<Window> window);

	void changeRenderMode(RenderMode renderMode) const;
private:
	std::shared_ptr<CameraComponent> mCurrentCamera = nullptr;
	std::vector<std::shared_ptr<LightComponent>> mLights;
	std::vector<std::shared_ptr<IModelComponent>> mModels;
	std::shared_ptr<Window> mWindow;
};

