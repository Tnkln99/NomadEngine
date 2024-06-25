#pragma once

#include "Texture.h"

class FrameBuffer
{
public:
	// after creating the FrameBuffer its users responsibility to unbind it
	FrameBuffer(float width, float height, GLint internalFormat, GLenum texFormat, GLenum texType, GLenum attachmentType);
	void setDrawParameter(GLenum param);
	void setReadParameter(GLenum param);
	[[nodiscard]] float getWidth() const;
	[[nodiscard]] float getHeight() const;
	void bind();
	void unbind();
private:
	unsigned int mFbo;
	Texture mTextureAttachment;
	float mWidth, mHeight;
};

