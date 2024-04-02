#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include"VBO.h"

class Vao
{
public:
	// ID reference for the Vertex Array Object
	GLuint mId;
	// Constructor that generates a VAO ID
	Vao();

	// Links a VBO Attribute such as a position or color to the VAO
	void linkAttrib(Vbo& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Binds the VAO
	void bind();
	// Unbinds the VAO
	void unbind();
	// Deletes the VAO
	void Delete();
};
#endif