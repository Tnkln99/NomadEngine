#include "Actor.h"

void Actor::update()
{
	for(const auto & comp : mComponents)
	{
		comp->update();
	}
}
