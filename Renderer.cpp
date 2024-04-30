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

		mLights[0]->mLight->sendLightInfoToShader(shader, mLights[0]->mOwner->mTransform);
		mCurrentCamera->getCamera()->sendCameraInfoToGpu(shader, mCurrentCamera->mOwner->mTransform);
		staticModelComp->mStaticModel->draw(staticModelComp->mOwner->mTransform.getModelMatrix());
	}
}

void Renderer::registerCamera(const std::shared_ptr<CameraComponent> camera)
{
	mCurrentCamera = camera;
	std::cout << " " << camera.get() << " " << mCurrentCamera.get() << std::endl;

}

void Renderer::registerLight(const std::shared_ptr<LightComponent>& light)
{
	mLights.push_back(light);
	std::cout << " " << light.get() << " " << mLights.back().get() << std::endl;

}

void Renderer::registerStaticModel(const std::shared_ptr<StaticModelComponent>& staticModel)
{
	std::cout << " " << staticModel.get() << std::endl;
	mStaticModels.push_back(staticModel);
}

void Renderer::registerWindow(const std::shared_ptr<Window> window)
{
	mWindow = window;
}
