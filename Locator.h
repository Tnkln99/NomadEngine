#pragma once

#include "Renderer.h"

// singleton and service manager
class Locator
{
public:
	static Renderer& getRendererService() {
		static Renderer renderer;
		return renderer;
	}
private:
	Locator() = default;

	Locator(const Locator&) = delete; // Delete copy constructor
	Locator& operator=(const Locator&) = delete; // Delete copy assignment operator
};

