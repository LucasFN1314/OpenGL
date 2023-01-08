#pragma once
#ifndef EBO_H_CLASS
#define EBO_H_CLASS
#include<glad/glad.h>

class EBO {
public:
	GLuint ID;
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};
#endif