#include"EBO.h"

void Ebo::init(std::vector<GLuint>& indices)
{
	glGenBuffers(1, &mId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

// Binds the EBO
void Ebo::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
}

// Unbinds the EBO
void Ebo::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void Ebo::Delete()
{
	glDeleteBuffers(1, &mId);
}