#include "Renderer.h"

void Renderer::render(const std::shared_ptr<StaticModel> staticModel, glm::mat4 modelMatrix)
{
	mCurrentCamera->updateMatrix(45.0f, 0.1f, 1000.0f);
	staticModel->draw(mCurrentCamera, mLights[0], modelMatrix);
}

void Renderer::registerCamera(std::shared_ptr<Camera> camera)
{
	mCurrentCamera = camera;
}

void Renderer::registerLight(std::shared_ptr<Light> light)
{
	mLights.push_back(light);
}
