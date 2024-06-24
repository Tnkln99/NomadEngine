#pragma once

#include <memory>

#include "Window.h"
#include "Scene.h"

class Engine
{
public:
	Engine(std::shared_ptr<Scene> scene);
	void changeScene(std::shared_ptr<Scene> scene);
	void run();
private:
	std::shared_ptr<Window> mWindow;
	std::shared_ptr<Scene> mCurrentScene;
};

