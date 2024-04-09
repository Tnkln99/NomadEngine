#pragma once


#include<glad/glad.h>
#include<vector>

class Ebo
{
public:
	// ID reference of Elements Buffer Object
	GLuint mId;
	// Constructor that generates a Elements Buffer Object and links it to indices
	explicit Ebo(std::vector<GLuint>& indices);

	// Binds the EBO
	void bind();
	// Unbinds the EBO
	void unbind();
	// Deletes the EBO
	void Delete();
};
