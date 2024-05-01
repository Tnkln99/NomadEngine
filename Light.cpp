#include "Light.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Actor.h"
#include "EBO.h"
#include "ResourceManager.h"


Light::Light()
{
	mLightIndicatorShader = ResourceManager::getLoadedShader("lightIndicator");
}

Light::~Light()
{
	mLightIndicatorShader->Delete();
}

void Light::loadLightIndicator()
{
	mVao.bind();
	// Generates Vertex Buffer Object and links it to vertices
	Vbo VBO(mLightVertices);
	// Generates Element Buffer Object and links it to indices
	Ebo EBO(mLightIndices);
	// Links VBO attributes such as coordinates and colors to VAO
	mVao.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	// Unbind all to prevent accidentally modifying them
	mVao.unbind();
	VBO.unbind();
	EBO.unbind();
}

void Light::drawIndicator(const std::shared_ptr<CameraComponent>& cameraComp, const glm::mat4& modelMatrix)
{
	mLightIndicatorShader->activate();

	glUniformMatrix4fv(glGetUniformLocation(mLightIndicatorShader->mId, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniform4f(glGetUniformLocation(mLightIndicatorShader->mId, "lightColor"), mLightColor.x, mLightColor.y, mLightColor.z, mLightColor.w);
	cameraComp->getCamera()->sendCameraInfoToGpu(mLightIndicatorShader, cameraComp->mOwner->mTransform);

	mVao.bind();

	glDrawElements(GL_TRIANGLES, mLightIndices.size(), GL_UNSIGNED_INT, 0);

	mVao.unbind();
}

void Light::sendLightInfoToShader(std::shared_ptr<Shader> shader, Transform transform) const
{
	glUniform4f(glGetUniformLocation(shader->mId, "lightColor"), mLightColor.x, mLightColor.y, mLightColor.z, mLightColor.w);
	glUniform3f(glGetUniformLocation(shader->mId, "lightPos"), transform.mPos.x,transform.mPos.y, transform.mPos.z);
}
