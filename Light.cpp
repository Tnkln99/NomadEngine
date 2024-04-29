#include "Light.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	mLightModel = glm::translate(mLightModel, mLightPos);
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

void Light::drawIndicator(Camera& camera)
{
	mLightIndicatorShader->activate();

	glUniformMatrix4fv(glGetUniformLocation(mLightIndicatorShader->mId, "model"), 1, GL_FALSE, glm::value_ptr(mLightModel));
	glUniform4f(glGetUniformLocation(mLightIndicatorShader->mId, "lightColor"), mLightColor.x, mLightColor.y, mLightColor.z, mLightColor.w);
	camera.sendCameraInfoToGpu(mLightIndicatorShader);

	mVao.bind();

	glDrawElements(GL_TRIANGLES, mLightIndices.size(), GL_UNSIGNED_INT, 0);


	mVao.unbind();
}
