#include"VBO.h"


void Vbo::init(std::vector<Vertex>& vertices)
{
	glGenBuffers(1, &mId);
	glBindBuffer(GL_ARRAY_BUFFER, mId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void Vbo::init(std::vector<VertexSkeletal>& vertices)
{
	glGenBuffers(1, &mId);
	glBindBuffer(GL_ARRAY_BUFFER, mId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexSkeletal), vertices.data(), GL_STATIC_DRAW);
}

// Binds the VBO
void Vbo::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, mId);
}

// Unbinds the VBO
void Vbo::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void Vbo::Delete()
{
	glDeleteBuffers(1, &mId);
}