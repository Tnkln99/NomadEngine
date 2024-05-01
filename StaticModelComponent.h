#pragma once

#include "IComponent.h"
#include "StaticModel.h"
#include <memory>


class StaticModelComponent : public IComponent
{
public:
	StaticModelComponent();
	std::shared_ptr<StaticModel> mStaticModel;
	// Inherited via IComponent
	virtual void update(float dt) override;
	virtual void init() override;
private:
};

