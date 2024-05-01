#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H
#include "Shader.h"
#include "VAO.h"
#include "CameraComponent.h"

class Light
{
public:
	Light();
	~Light();
	glm::vec4 mLightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


	void loadLightIndicator();
	Vao mVao;
	std::vector<Vertex> mLightVertices=
	{ //     COORDINATES     //
		Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
		Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
		Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
		Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
	};

	std::vector < GLuint> mLightIndices=
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};
	
	std::shared_ptr<Shader> mLightIndicatorShader{};
	void drawIndicator(const std::shared_ptr<CameraComponent>& cameraComp, const glm::mat4& modelMatrix);

	void sendLightInfoToShader(std::shared_ptr<Shader> shader, Transform transform) const;
};

#endif

