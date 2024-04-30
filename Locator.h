#pragma once

#include "Renderer.h"

class Locator
{
public:
	static void registerRenderer(std::shared_ptr<Renderer> renderer) {
		mRenderer = renderer;
	}

	static std::shared_ptr<Renderer> getRendererService() {
		return mRenderer;
	}
private:
	static std::shared_ptr<Renderer> mRenderer;
};

