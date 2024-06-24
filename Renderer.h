#pragma once

#include "Window.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "StaticModelComponent.h"
#include "SkeletalModelComponent.h"

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
	friend class Engine;
	friend class Locator;

	friend void LightComponent::init();
	friend void StaticModelComponent::init();
	friend void SkeletalModelComponent::init();
	friend void CameraComponent::init();
public:
	void changeRenderMode(RenderMode renderMode) const;
	// in here we will have methodes like draw line, draw debug cube/sphere
	
private:
	Renderer() = default;

	Renderer(const Renderer&) = delete; // Delete copy constructor
	Renderer& operator=(const Renderer&) = delete; // Delete copy assignment operator

	void render() const;
	void loadDefaultShaders();

	void registerWindow(const std::shared_ptr<Window>& window);
	void registerCamera(const std::shared_ptr<CameraComponent>& camera);
	void registerLight(const std::shared_ptr<LightComponent>& light);
	void registerModel(const std::shared_ptr<IModelComponent>& model);

	std::shared_ptr<CameraComponent> mCurrentCamera;
	std::vector<std::shared_ptr<LightComponent>> mLights;
	std::vector<std::shared_ptr<IModelComponent>> mModels;
	std::shared_ptr<Window> mWindow;
};

