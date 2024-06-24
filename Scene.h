#pragma once
#include "Actor.h"
#include <unordered_map>

class Scene
{
public:
	virtual ~Scene() = default;
	virtual void init();
	virtual void beginPlay();
	virtual void sceneUi();
	virtual void update(float dt);
protected:
	std::unordered_map<std::string, Actor> mActors;
};

