#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H
#include "Shader.h"
#include "VAO.h"
#include "CameraComponent.h"
#include "Mesh.h"

class Light
{
public:
	Light();
	~Light();
	glm::vec4 mLightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	
	std::shared_ptr<Shader> mLightIndicatorShader{};
	void drawIndicator(const std::shared_ptr<CameraComponent>& cameraComp, const glm::mat4& modelMatrix);
	void sendLightInfoToShader(std::shared_ptr<Shader> shader, Transform transform) const;
private:
	Mesh mIndicatorMesh{ Mesh::CUBE };
};

#endif

