#pragma once

#include<glad/glad.h>

#include"Shader.h"

class Texture
{
public:
	GLuint mId;
	const char* mType;
	GLuint mUnit;

	// texture from a file
	Texture(const char* image, const char* texType, GLuint slot);
	// texture from a buffer
	Texture(int bufferSize, void* buffer, const char* texType, GLuint slot);
	
	Texture(float width, float height, GLint internalFormat, GLenum texFormat, GLenum texType);

	// Assigns a texture unit to a texture
	void texUnit(std::shared_ptr<Shader> shader, const char* uniform, GLuint unit);
	void activate();
	// Binds a texture
	void bind();
	// Unbinds a texture
	void unbind();
	// Deletes a texture
	void Delete() const;
};