#pragma once

#include "Renderer.h"

class Locator
{
public:
	static std::shared_ptr<Renderer> getRendererService() {
		if(mRenderer)
		{
			return mRenderer;
		}
		mRenderer = std::make_shared<Renderer>();
		return mRenderer;
	}
private:
	static std::shared_ptr<Renderer> mRenderer;
};

