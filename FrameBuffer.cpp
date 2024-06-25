#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(const float width, const float height, const GLint internalFormat, const GLenum texFormat, const GLenum texType, const GLenum attachmentType) :
	mTextureAttachment(width, height, internalFormat, texFormat, texType), mWidth(width), mHeight(height)
{
	glGenFramebuffers(1, &mFbo);
	glBindFramebuffer(GL_FRAMEBUFFER, mFbo);

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, mTextureAttachment.mId, 0);
}

void FrameBuffer::setDrawParameter(const GLenum param)
{
	glDrawBuffer(param);
}

void FrameBuffer::setReadParameter(const GLenum param)
{
	glReadBuffer(param);
}

float FrameBuffer::getWidth() const
{
	return mWidth;
}

float FrameBuffer::getHeight() const
{
	return mHeight;
}

void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
}

void FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
