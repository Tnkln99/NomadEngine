#pragma once

#include<glad/glad.h>

#include"Shader.h"

class Texture
{
public:
	GLuint ID;
	const char* mType;
	GLuint mUnit;

	Texture(const char* image, const char* texType, GLuint slot);
	Texture(int bufferSize, void* buffer, const char* texType, GLuint slot);

	// Assigns a texture unit to a texture
	void texUnit(std::shared_ptr<Shader> shader, const char* uniform, GLuint unit);
	// Binds a texture
	void bind();
	// Unbinds a texture
	void unbind();
	// Deletes a texture
	void Delete() const;
};