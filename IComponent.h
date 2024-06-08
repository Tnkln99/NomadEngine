#pragma once

#include <memory>

class Actor;

class IComponent
{
public:
	virtual ~IComponent() = default;
	// called on update from owner 
	virtual void update(float dt) = 0;
	// called right after game loop starts
	virtual void beginPlay() = 0;
	// called right after added to an actor 
	virtual void init() = 0;
	Actor* mOwner{};
private:
	
};

