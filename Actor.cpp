#include "Actor.h"


void Actor::update(const float dt)
{
	for(const auto & comp : mComponents)
	{
		comp->update(dt);
	}
}
