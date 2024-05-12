#include "Actor.h"


void Actor::update(const float dt) const
{
	for(const auto & comp : mComponents)
	{
		comp->update(dt);
	}
}

void Actor::beginPlay() const
{
	for (const auto& comp : mComponents)
	{
		comp->beginPlay();
	}
}
