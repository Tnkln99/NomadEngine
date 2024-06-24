#include "Renderer.h"
#include "Actor.h"
#include "ResourceManager.h"


void Renderer::render() const
{
	const Transform cameraTransform = mCurrentCamera->mOwner->mTransform;
	mCurrentCamera->getCamera()->updateMatrix(45.0f, 0.1f, 1000.0f, mWindow, cameraTransform);
	std::shared_ptr<Shader> lastShader;

	for(auto& model : mModels)
	{
		if(!model->shouldDraw())
		{
			continue;
		}

		const auto shader = model->getShader();
		if(shader!=lastShader)
		{
			shader->activate();
			// for now engine support single light
			mLights[0]->mLight->sendLightInfoToShader(shader, mLights[0]->mOwner->mTransform);
			mCurrentCamera->getCamera()->sendCameraInfoToGpu(shader, cameraTransform);
			lastShader = shader;
		}
		
		model->draw(model->mOwner->mTransform.getModelMatrix());
	}

	mLights[0]->mLight->drawIndicator(mCurrentCamera, mLights[0]->mOwner->mTransform.getModelMatrix());
}

void Renderer::loadDefaultShaders()
{
	ResourceManager::loadShader("lightIndicator", "Light.vert", "Light.frag");
	ResourceManager::loadShader("SkeletalModel", "SkeletalModel.vert", "SkeletalModel.frag");
	ResourceManager::loadShader("StaticModel", "StaticModel.vert", "StaticModel.frag");
	ResourceManager::loadShader("ComputationClothFirstPass", "ComputationClothFirstPass.comp");
	ResourceManager::loadShader("ComputationClothSecondPass", "ComputationClothSecondPass.comp");
}

void Renderer::registerCamera(const std::shared_ptr<CameraComponent>& camera)
{
	mCurrentCamera = camera;
}

void Renderer::registerLight(const std::shared_ptr<LightComponent>& light)
{
	mLights.push_back(light);
}

void Renderer::registerModel(const std::shared_ptr<IModelComponent>& model)
{
	mModels.push_back(model);
}

void Renderer::registerWindow(const std::shared_ptr<Window>& window)
{
	mWindow = window;
}

void Renderer::changeRenderMode(const RenderMode renderMode) const
{
	switch (renderMode)
	{
	case FILL:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case WIREFRAME:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case POINT:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	default:  // NOLINT(clang-diagnostic-covered-switch-default)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
}
