#include "Renderer.h"
#include "Actor.h"


void Renderer::render() const
{
	for(auto& staticModelComp : mStaticModels)
	{
		if(staticModelComp->mStaticModel == nullptr)
		{
			continue;
		}
		mCurrentCamera->getCamera()->updateMatrix(45.0f, 0.1f, 1000.0f, mWindow, mCurrentCamera->mOwner->mTransform);
		const auto shader = staticModelComp->mStaticModel->getShader();
		shader->activate();

		mLights[0]->mLight->sendLightInfoToShader(shader, mLights[0]->mOwner->mTransform);
		mCurrentCamera->getCamera()->sendCameraInfoToGpu(shader, mCurrentCamera->mOwner->mTransform);
		staticModelComp->mStaticModel->draw(staticModelComp->mOwner->mTransform.getModelMatrix());
	}

	mLights[0]->mLight->drawIndicator(mCurrentCamera, mLights[0]->mOwner->mTransform.getModelMatrix());
}

void Renderer::registerCamera(const std::shared_ptr<CameraComponent> camera)
{
	mCurrentCamera = camera;
}

void Renderer::registerLight(const std::shared_ptr<LightComponent>& light)
{
	mLights.push_back(light);
}

void Renderer::registerStaticModel(const std::shared_ptr<StaticModelComponent>& staticModel)
{
	std::cout << staticModel.get() << std::endl;
	mStaticModels.push_back(staticModel);
}

void Renderer::registerWindow(const std::shared_ptr<Window> window)
{
	mWindow = window;
}

void Renderer::changeRenderMode(RenderMode renderMode) const
{
	switch (renderMode)
	{
	case FILL:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case WIREFRAME:
		std::cout << renderMode << std::endl;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case POINT:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	default:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
}
