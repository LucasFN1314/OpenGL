#include "shaderClass.h"
#include <iostream>

std::string get_file_content(const char* filename)
{
	std::ifstream inp(filename, std::ios::binary);
	if (inp) {
		std::string content;
		inp.seekg(0, std::ios::end);
		content.resize(inp.tellg());
		inp.seekg(0, std::ios::beg);
		inp.read(&content[0], content.size());
		inp.close();
		return content;
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_content(vertexFile);
	std::string fragmentCode = get_file_content(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::activate()
{
	glUseProgram(ID);
}

void Shader::deactivate()
{
	glDeleteProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}
