#include"Shader.h"

#include <iostream>

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

void Shader::loadShader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	checkShaderCompilation(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	checkShaderCompilation(fragmentShader);

	// Create Shader Program Object and get its reference
	mId = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(mId, vertexShader);
	glAttachShader(mId, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(mId);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::loadComputeShader(const char* computeFile)
{
	std::string computeCode = get_file_contents(computeFile);
	const char* computeSource = computeCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(computeShader, 1, &computeSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(computeShader);

	checkShaderCompilation(computeShader);

	// Create Shader Program Object and get its reference
	mId = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(mId, computeShader);

	glLinkProgram(mId);

	glDeleteShader(computeShader);
}

// Activates the Shader Program
void Shader::activate()
{
	glUseProgram(mId);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(mId);
}

void Shader::checkShaderCompilation(GLuint shader)
{
	int params = -1;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
	if (params != GL_TRUE)
	{
		std::cout << "shader id: " << shader << " did not compile." << std::endl;
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}
}
