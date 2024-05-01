#pragma once

#include "Window.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "StaticModelComponent.h"

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
	void registerStaticModel(const std::shared_ptr<StaticModelComponent>& staticModel);
	void registerWindow(std::shared_ptr<Window> window);

	void changeRenderMode(RenderMode renderMode) const;
private:
	RenderMode mRenderMode = FILL;

	std::shared_ptr<CameraComponent> mCurrentCamera = nullptr;
	std::vector<std::shared_ptr<LightComponent>> mLights;
	std::vector<std::shared_ptr<StaticModelComponent>> mStaticModels;
	std::shared_ptr<Window> mWindow;
};

