#pragma once 

#include "Shader.h"
#include "VAO.h"
#include "CameraComponent.h"
#include "StaticModel.h"

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
	std::shared_ptr<StaticModel> mIndicatorModel;
};


