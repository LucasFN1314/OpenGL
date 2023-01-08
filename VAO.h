#pragma once
#ifndef VAO_H_CLASS
	#define VAO_H_CLASS
	#include <glad/glad.h>
	#include "VBO.h"
	
	class VAO {
	public:
		GLuint ID;
		VAO();

		void LinkVBO(VBO VBO, GLuint layout);
		void LinkAttrib(VBO vbo, GLuint layout, GLuint numComp, GLenum type, GLsizeiptr stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
	};

#endif