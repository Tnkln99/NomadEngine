#include"VAO.h"

// Constructor that generates a VAO ID
Vao::Vao()
{
	glGenVertexArrays(1, &mId);
}

// Links a VBO Attribute such as a position or color to the VAO
void Vao::linkAttrib(Vbo& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	vbo.bind();
	if(type == GL_FLOAT)
	{
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	}
	else if(type == GL_INT)
	{
		glVertexAttribIPointer(layout, numComponents, type, stride, offset);
	}
	glEnableVertexAttribArray(layout);
	vbo.unbind();
}

// Binds the VAO
void Vao::bind()
{
	glBindVertexArray(mId);
}

// Unbinds the VAO
void Vao::unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void Vao::Delete()
{
	glDeleteVertexArrays(1, &mId);
}