#include "Texture.h"
#include<iostream>

Texture::Texture(const char* image, GLenum texType, GLenum SLOT, GLenum format, GLenum pixelType)
{
	type = texType;
	int widthImg, heightImg, numColCH;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCH, 0);
	std::cout << image << std::endl;


	GLuint texture;
	glGenTextures(1, &ID);
	glActiveTexture(SLOT);
	glBindTexture(texType, ID);
	
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::textUnit(Shader shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.activate();
	glUniform1i(texUni, unit);
}

void Texture::bind()
{
	glBindTexture(type, ID);
}

void Texture::unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
