#pragma once
#include "Scene.h"

class SandBoxScene : public Scene 
{
public:
	void init() override;
	void beginPlay() override;
	void sceneUi() override;
	void update(float dt) override;
};

