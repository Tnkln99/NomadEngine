#include "Actor.h"

void Actor::init()
{
	for (const auto& comp : mComponents)
	{
		comp->init();
	}
}

void Actor::update()
{
	for(const auto & comp : mComponents)
	{
		comp->update();
	}
}
