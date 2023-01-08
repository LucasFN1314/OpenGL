#pragma once
#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<stb/stb_image.h>
#include<glad/glad.h>
#include"shaderClass.h"

class Texture {
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum SLOT, GLenum format, GLenum pixelType);
	
	void textUnit(Shader shader, const char* uniform, GLuint unit);
	void bind();
	void unbind();
	void Delete();

};
#endif