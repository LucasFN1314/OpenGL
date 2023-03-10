#pragma once
#ifndef VBO_H_CLASS
	#define VBO_H_CLASS
	#include<glad/glad.h>

	class VBO {
	public:
		GLuint ID;
		VBO(GLfloat* vertices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
	};
#endif