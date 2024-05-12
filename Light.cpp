#include "Light.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Actor.h"
#include "EBO.h"
#include "ResourceManager.h"


Light::Light()
{
	mLightIndicatorShader = ResourceManager::getLoadedShader("lightIndicator");
	mIndicatorModel = ResourceManager::getStaticModel("Sphere");
}

Light::~Light()
{
	mLightIndicatorShader->Delete();
}

void Light::drawIndicator(const std::shared_ptr<CameraComponent>& cameraComp, const glm::mat4& modelMatrix)
{
	mLightIndicatorShader->activate();

	glUniform4f(glGetUniformLocation(mLightIndicatorShader->mId, "lightColor"), mLightColor.x, mLightColor.y, mLightColor.z, mLightColor.w);
	cameraComp->getCamera()->sendCameraInfoToGpu(mLightIndicatorShader, cameraComp->mOwner->mTransform);

	mIndicatorModel->draw(modelMatrix, mLightIndicatorShader);
}

void Light::sendLightInfoToShader(std::shared_ptr<Shader> shader, Transform transform) const
{
	glUniform4f(glGetUniformLocation(shader->mId, "lightColor"), mLightColor.x, mLightColor.y, mLightColor.z, mLightColor.w);
	glUniform3f(glGetUniformLocation(shader->mId, "lightPos"), transform.mPos.x,transform.mPos.y, transform.mPos.z);
}
