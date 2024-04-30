#include "Renderer.h"
#include "Actor.h"
void Renderer::render(const std::shared_ptr<StaticModel> staticModel, glm::mat4 modelMatrix)
{
	mCurrentCamera->getCamera()->updateMatrix(45.0f, 0.1f, 1000.0f, mWindow, mCurrentCamera->mOwner->mTransform);
    auto shader = staticModel->getShader();

	mLights[0]->mLight->sendLightInfoToShader(shader, mLights[0]->mOwner->mTransform);
	mCurrentCamera->getCamera()->sendCameraInfoToGpu(shader, mCurrentCamera->mOwner->mTransform);
	staticModel->draw(modelMatrix);
}

void Renderer::registerCamera(std::shared_ptr<CameraComponent> camera)
{
	mCurrentCamera = std::move(camera);
}

void Renderer::registerLight(std::shared_ptr<LightComponent> light)
{
	mLights.emplace_back(light);
}

void Renderer::registerWindow(std::shared_ptr<Window> window)
{
	mWindow = window;
}
