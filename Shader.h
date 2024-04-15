#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint mId;
	// Constructor that build the Shader Program from 2 different shaders
	Shader() = default;

	void loadShader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void activate();
	// Deletes the Shader Program
	void Delete();
};