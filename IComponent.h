#pragma once

#include <memory>

class Actor;

class IComponent
{
public:
	virtual ~IComponent() = default;
	virtual void update() = 0;
	virtual void init() = 0;
	Actor* mOwner{};
private:
	
};

